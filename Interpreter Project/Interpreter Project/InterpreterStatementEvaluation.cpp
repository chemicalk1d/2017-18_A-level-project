#include "Interpreter.hpp"

#include "Object.hpp"
#include "Methods.hpp"

#include <iostream>

//this function finds what type of statement it is and then calls the appropriate function
void Interpreter::EvaluateStatement(Statement* st) {
	if (st->GetStatementType() == "Expression Statement") {
		EvaluateExpressionStatement((ExpressionStatement*)st);
	}
	else if (st->GetStatementType() == "Label Statement") {
		EvaluateLabelStatement((LabelStatement*)st);
	}
	else if (st->GetStatementType() == "Goto Statement") {
		EvaluateGotoStatement((GotoStatement*)st);
	}
	else if (st->GetStatementType() == "If Statement") {
		EvaluateIfStatement((IfStatement*)st);
	}
	else if (st->GetStatementType() == "While Loop") {
		EvaluateWhileLoop((WhileLoop*)st);
	}
	else if (st->GetStatementType() == "For Loop") {
		EvaluateForLoop((ForLoop*)st);
	}
	else if (st->GetStatementType() == "Subroutine") {
		EvaluateSubroutine((Subroutine*)st);
	}
	else if (st->GetStatementType() == "EndSub") {
		EvaluateEndSub((EndSub*)st);
	}
	else if (st->GetStatementType() == "Break Statement") {
		EvaluateBreakStatement((BreakStatement*)st);
	}
	else if (st->GetStatementType() == "Continue Statement") {
		EvaluateContinueStatement((ContinueStatement*)st);
	}
	else if (st->GetStatementType() == "Import Statement") {
		EvaluateImportStatement((ImportStatement*)st);
	}
	else if (st->GetStatementType() == "Void Statement") {
		nextStatement = st->GetNext();
	}
	else {
		runtime_error = true;
		error_message += "Program error at line " + std::to_string(st->GetLineNumber()) + " in file " + st->GetStatementFileName() + "\n";
		error_message += "Unknown statement type";
		return;
	}
}

//this evaluates an expression statement
void Interpreter::EvaluateExpressionStatement(ExpressionStatement* st) {

	//move forward to the next statement
	//set the next statement first so that the function expression evaluation can overwrite it if it needs to
	nextStatement = st->GetNext();

	EvaluateExpression(st->GetExpression());
}

//this evaluates a label by simply moving forward to the next statement
void Interpreter::EvaluateLabelStatement(LabelStatement* ls) {
	//move forward to the next statement
	nextStatement = ls->GetNext();
}

//this evaluates goto statement by moving forward
//this effectively executes the goto statement and jumps as a result of the direction pass
void Interpreter::EvaluateGotoStatement(GotoStatement* gs) {
	nextStatement = gs->GetNext();
}

//this evaluates an if statement by evaluating and checking the condition before
//going to the next piece of code appropriate based on the result
void Interpreter::EvaluateIfStatement(IfStatement* ifst) {

	inside_evaluation_expression = true;
	Value v = EvaluateExpression(ifst->GetCondition());
	inside_evaluation_expression = false;

	if (v.Get_Type() != Value::BOOLEAN)
	{
		//error
		runtime_error = true;
		error_message = "Program error - The condition for an if statement must be a boolean expression";
		return;
	}
	else if (v.Get_Bool() == true) {
		nextStatement = ifst->GetStatements()[0];
		return;
	}
	//else (v.Get_Bool() == false)

	for (auto el_if : ifst->GetElseIfClauses()) {
		bool condition = EvaluateElseIfStatement(el_if);

		if (condition) {
			return;
		}
		else if (runtime_error) {
			return;
		}
	}

	if (ifst->GetElseClause()) {
		nextStatement = ifst->GetElseClause()->GetSubcode()[0];
		return;
	}
	//else

	nextStatement = ifst->GetNext();
}

//this evaluates ElseIf statements and returns whether the value is true or false
bool Interpreter::EvaluateElseIfStatement(IfStatement::ElseIfClause* if_el_st) {

	inside_evaluation_expression = true;
	Value v = EvaluateExpression(if_el_st->GetCondition());
	inside_evaluation_expression = false;

	if (v.Get_Type() != Value::BOOLEAN)
	{
		//error
		runtime_error = true;
		error_message = "Program error - The condition for an else if statement must be a boolean";
		return false;
	}
	else if (v.Get_Bool() == true) {
		nextStatement = if_el_st->GetSubcode()[0];
		return true;
	}
	//else (v.Get_Bool() == false)
	return false;
}

//this evaluates while loops by evaluating the condition and then moving forward
//the looping comes from setting the statement at the end of the subcode of the while loop
//to the while loop itself
void Interpreter::EvaluateWhileLoop(WhileLoop* wh_lp) {

	inside_evaluation_expression = true;
	Value v = EvaluateExpression(wh_lp->GetCondition());
	inside_evaluation_expression = false;

	if (v.Get_Type() != Value::BOOLEAN)
	{
		//error
		runtime_error = true;
		error_message = "Program error - The condition for a while loop must be a boolean";
		return;
	}
	else if (v.Get_Bool() == true) {
		nextStatement = wh_lp->GetStatements()[0];
		return;
	}
	//else (v.Get_Bool() == false)
	nextStatement = wh_lp->GetNext();
}

//TODO break this function up into smaller functions
//evaluates a for loop
void Interpreter::EvaluateForLoop(ForLoop* f_lp) {

	if (f_lp->Get_loop_flag() == false) {
		//we need to set the variable which is used for this for loop
		SetVariable(f_lp->GetVariable()->Get_Name(), EvaluateExpression(f_lp->GetStart()));
		f_lp->Set_loop_flag(true);
	}
	else {

		//create a temporary binary expression so we can evaluate the for loop
		//give it copies of the variable and step expressions such that when the tmp object
		//goes away it doesn't delete the original versions of the expressions
		BinaryExpression tmp;
		tmp.Set_Operator("+");
		tmp.Set_LHS(f_lp->GetVariable()->Duplicate());
		tmp.Set_RHS(f_lp->GetStep()->Duplicate());

		//perform the step and increment the variable
		Value v = EvaluateBinaryExpression(&tmp);
		SetVariable(f_lp->GetVariable()->Get_Name(), v);
	}

	Value v;

	v = EvaluateExpression(f_lp->GetStep());

	//guarenteed to be either an integer or a float
	if (v.Get_Type() == Value::INT) {
		if (v.Get_Int() > 0) {

			//create a temporary binary expression so we can evaluate the for loop
			//give it copies of the variable and end expressions such that when the tmp object
			//goes away it doesn't delete the original versions of the expressions
			BinaryExpression tmp;
			tmp.Set_Operator("<=");
			tmp.Set_LHS(f_lp->GetVariable()->Duplicate());
			tmp.Set_RHS(f_lp->GetEnd()->Duplicate());

			//v2 will be a boolean because that is the only type the less than operator can result in
			Value v2 = EvaluateBinaryExpression(&tmp);

			if (v2.Get_Bool() == false) {
				//end of loop
				nextStatement = f_lp->GetNext();
			}
			else {
				//loop carries on
				nextStatement = f_lp->GetStatements()[0];
			}

		}
		else {

			//create a temporary binary expression so we can evaluate the for loop
			//give it copies of the variable and end expressions such that when the tmp object
			//goes away it doesn't delete the original versions of the expressions
			BinaryExpression tmp;
			tmp.Set_Operator(">=");
			tmp.Set_LHS(f_lp->GetVariable()->Duplicate());
			tmp.Set_RHS(f_lp->GetEnd()->Duplicate());

			//v2 will be a boolean because that is the only type the greater than operator can result in
			Value v2 = EvaluateBinaryExpression(&tmp);

			if (v2.Get_Bool() == false) {
				//end of loop
				nextStatement = f_lp->GetNext();
			}
			else {
				//loop carries on
				nextStatement = f_lp->GetStatements()[0];
			}
		}
	}
	else {
		if (v.Get_Float() > 0.0) {
			//create a temporary binary expression so we can evaluate the for loop
			//give it copies of the variable and end expressions such that when the tmp object
			//goes away it doesn't delete the original versions of the expressions
			BinaryExpression tmp;
			tmp.Set_Operator("<=");
			tmp.Set_LHS(f_lp->GetVariable()->Duplicate());
			tmp.Set_RHS(f_lp->GetEnd()->Duplicate());

			//v2 will be a boolean because that is the only type the less than operator can result in
			Value v2 = EvaluateBinaryExpression(&tmp);

			if (v2.Get_Bool() == false) {
				//end of loop
				nextStatement = f_lp->GetNext();
			}
			else {
				//loop carries on
				nextStatement = f_lp->GetStatements()[0];
			}
		}
		else {
			//create a temporary binary expression so we can evaluate the for loop
			//give it copies of the variable and end expressions such that when the tmp object
			//goes away it doesn't delete the original versions of the expressions
			BinaryExpression tmp;
			tmp.Set_Operator(">=");
			tmp.Set_LHS(f_lp->GetVariable()->Duplicate());
			tmp.Set_RHS(f_lp->GetEnd()->Duplicate());

			//v2 will be a boolean because that is the only type the less than operator can result in
			Value v2 = EvaluateBinaryExpression(&tmp);

			if (v2.Get_Bool() == false) {
				//end of loop
				nextStatement = f_lp->GetNext();
			}
			else {
				//loop carries on
				nextStatement = f_lp->GetStatements()[0];
			}
		}
	}

}

void Interpreter::EvaluateSubroutine(Subroutine* sub) {
	//everything has already been done in the label pass and direction pass functions
	//therefore the only thing we need to do here is to set the nextStatement pointer
	nextStatement = sub->GetNext();
}

void Interpreter::EvaluateEndSub(EndSub* eSub) {

	//pop the return point of the return values of the stack
	Statement* st = call_stack.top();
	call_stack.pop();

	nextStatement = st;
}

void Interpreter::EvaluateBreakStatement(BreakStatement* bs) {
	nextStatement = bs->GetNext();
}

void Interpreter::EvaluateContinueStatement(ContinueStatement* cs) {
	nextStatement = cs->GetNext();
}

void Interpreter::EvaluateImportStatement(ImportStatement* is) {
	nextStatement = is->GetNext();
}