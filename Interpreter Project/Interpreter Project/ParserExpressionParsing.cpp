#include "Parser.hpp"

#include "Utils.hpp"

#include <cassert>

//goes through each possible expression and tries to parse the next
//piece of code as each possible expression until it finds one that works
Expression* Parser::ParseExpression(bool skip_binary_expression) {

	int tp = 0;
	Expression* expr;

	tp = Get_Token_Ptr();

	//parse binary expression - this is skipped if we are already parsing the left hand
	//side of a binary expression in order to avoid an infinite loop
	if (!skip_binary_expression) {
		expr = ParseBinaryExpression();
		if (expr != nullptr) {
			expr->SetFileName(filename);
			return expr;
		}
		else if (error) {
			return nullptr;
		}
		Set_Token_Ptr(tp);
	}

	expr = ParseDotExpression();
	if (expr != nullptr) {
		expr->SetFileName(filename);
		return expr;
	}
	else if (error) {
		return nullptr;
	}
	Set_Token_Ptr(tp);


	expr = ParseBracketExpression();
	if (expr != nullptr) {
		expr->SetFileName(filename);
		return expr;
	}
	else if (error) {
		return nullptr;
	}
	Set_Token_Ptr(tp);

	expr = ParseUnaryExpression();
	if (expr != nullptr) {
		expr->SetFileName(filename);
		return expr;
	}
	else if (error) {
		return nullptr;
	}
	Set_Token_Ptr(tp);

	expr = ParseFunctionCallExpression();
	if (expr != nullptr) {
		expr->SetFileName(filename);
		return expr;
	}
	Set_Token_Ptr(tp);

	expr = ParseIntExpression();
	if (expr != nullptr) {
		expr->SetFileName(filename);
		return expr;
	}
	else if (error) {
		return nullptr;
	}
	Set_Token_Ptr(tp);

	expr = ParseStringExpression();
	if (expr != nullptr) {
		expr->SetFileName(filename);
		return expr;
	}
	else if (error) {
		return nullptr;
	}
	Set_Token_Ptr(tp);

	expr = ParseDecimalExpression();
	if (expr != nullptr) {
		expr->SetFileName(filename);
		return expr;
	}
	else if (error) {
		return nullptr;
	}
	Set_Token_Ptr(tp);

	expr = ParseBoolExpression();
	if (expr != nullptr) {
		expr->SetFileName(filename);
		return expr;
	}
	else if (error) {
		return nullptr;
	}
	Set_Token_Ptr(tp);

	expr = ParseVariableExpression();
	if (expr != nullptr) {
		expr->SetFileName(filename);
		return expr;
	}
	else if (error) {
		return nullptr;
	}
	Set_Token_Ptr(tp);

	return nullptr;
}

Expression* Parser::ParseBracketExpression() {

	Token t;
	t = GetToken();

	//opening brackets
	if (t.GetTokenString() != "(") {
		return nullptr;
	}
	//else

	//internal expression
	Expression* expr = ParseExpression();
	if (error) {
		return nullptr;
	}

	if (expr == nullptr) {
		//error
		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Expected expression after opening bracket";
		return nullptr;
	}

	//closing bracket
	t = GetToken();
	if (t.GetTokenString() != ")") {
		error = true;
		error_message += "Syntax error at line " + std::to_string(expr->GetLineNumber()) + "\n";
		error_message += "Expected closing bracket after expression";
		delete expr;
		return nullptr;
	}

	BracketExpression* be = new BracketExpression;
	be->Set_Expression(expr);

	return be;
}

//tries to the parse the code as an 2 operand one operator expression
//e.g. a + b
Expression* Parser::ParseBinaryExpression() {

	Expression* lhs = ParseExpression(true);
	if (error) {
		return nullptr;
	}

	if (lhs == nullptr) {
		return nullptr;
	}

	int line_number = lhs->GetLineNumber();

	Token t = GetToken();

	if (!IsBinaryOperator(t.GetTokenString())) {
		delete lhs;
		return nullptr;
	}

	std::string op = t.GetTokenString();

	Expression* rhs = ParseExpression();
	if (error) {
		return nullptr;
	}

	if (rhs == nullptr) {
		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Expected expression after operator";
		delete lhs;
		return nullptr;
	}

	BinaryExpression* be = new BinaryExpression;

	be->Set_LHS(lhs);
	be->Set_RHS(rhs);
	be->SetLineNumber(line_number);
	be->Set_Operator(op);


	if (rhs->GetExpressionType() == "Binary Expression") {
		CheckBinaryExpressionOrder(be);
	}

	return be;
}


//parses it as a one operator, one operand expression
//e.g. -a, Not "true"
Expression* Parser::ParseUnaryExpression() {
	Token t = GetToken();

	if (!IsUnaryOperator(t.GetTokenString())) {
		return nullptr;
	}

	int line_number = t.GetLineNumber();

	Expression* expr = ParseExpression();
	if (error) {
		return nullptr;
	}

	if (expr == nullptr) {
		return nullptr;
	}

	UnaryExpression* ue = new UnaryExpression;
	ue->SetLineNumber(line_number);
	ue->Set_Expression(expr);
	ue->Set_Operator(t.GetTokenString());

	return ue;
}

//tries to pass the next the next piece of code as a function/subroutine call
//WriteLine("Hello World")
Expression* Parser::ParseFunctionCallExpression() {

	Token t;

	t = GetToken();

	if (t.GetTokenType() != Token::LITERAL || is_keyword(t.GetTokenString())) {
		return nullptr;
	}


	std::string name = t.GetTokenString();
	int line_number = t.GetLineNumber();

	t = GetToken();

	if (t.GetTokenString() != "(") {
		return nullptr;
	}

	std::vector<Expression*> args;

	int tp = Get_Token_Ptr();
	t = GetToken();
	if (t.GetTokenString() != ")") {

		Set_Token_Ptr(tp);

		//function argument parsing
		while (true) {
			Expression* arg = ParseExpression();
			if (error) {
				return nullptr;
			}

			if (arg == nullptr) {
				//error

				for (auto argument : args) {
					delete argument;
				}

				error = true;
				error_message += "Syntax error at line " + std::to_string(line_number) + "\n";
				error_message += "Error expected argument for function call";

				return nullptr;
			}

			args.push_back(arg);

			t = GetToken();
			if (t.GetTokenString() == ")") {
				break;
			}//if
			else if (t.GetTokenString() == ",") {
				continue;
			}//else if
			else {
				//error

				error = true;
				error_message += "Syntax error at line " + std::to_string(line_number) + "\n";
				error_message += "Error expected either closing bracket or comma for function call";


				for (auto argument : args) {
					delete argument;
				}//for

				return nullptr;
			}//else


		}//while
	}//if

	FunctionExpression* fe = new FunctionExpression;

	fe->SetLineNumber(line_number);
	fe->Set_Arguments(args);
	fe->Set_Name(name);

	return fe;
}

//tries to parse the next piece of code as a string
Expression* Parser::ParseStringExpression() {
	Token t = GetToken();

	if (t.GetTokenType() != Token::STRING) {
		return nullptr;
	}
	//else

	StringExpression* se = new StringExpression;

	se->SetLineNumber(t.GetLineNumber());
	se->Set_String(t.GetTokenString());
	return se;
}

//tries to parse the next piece of code as a whole number
Expression* Parser::ParseIntExpression() {
	Token t = GetToken();

	if (t.GetTokenType() != Token::INTEGER) {
		return nullptr;
	}
	//else

	IntExpression* ie = new IntExpression;

	ie->SetLineNumber(t.GetLineNumber());
	ie->Set_Integer(std::stoll(t.GetTokenString()));
	return ie;
}

//tries to parse the next piece of code as a real number
Expression* Parser::ParseDecimalExpression() {
	Token t = GetToken();

	if (t.GetTokenType() != Token::DECIMAL) {
		return nullptr;
	}
	//else

	DecimalExpression* de = new DecimalExpression;

	de->SetLineNumber(t.GetLineNumber());
	de->Set_Decimal(std::stod(t.GetTokenString()));
	return de;
}

//tries to parse the next piece of code as a variable
Expression* Parser::ParseVariableExpression() {
	Token t = GetToken();

	if (t.GetTokenType() != Token::LITERAL || is_keyword(t.GetTokenString())) {
		return nullptr;
	}
	//else

	VariableExpression* ve = new VariableExpression;

	ve->SetLineNumber(t.GetLineNumber());
	ve->Set_Name(t.GetTokenString());
	return ve;
}

Expression* Parser::ParseDotExpression() {

	Expression* lhs = nullptr;

	lhs = ParseVariableExpression();
	if (error) {
		return nullptr;
	}

	if (!lhs) {
		return nullptr;
	}
	//else

	Token t = GetToken();

	if (t.GetTokenString() != ".") {
		delete lhs;
		return nullptr;
	}
	//else

	Expression* rhs = nullptr;

	int tp = Get_Token_Ptr();
	rhs = ParseFunctionCallExpression();
	if (error) {
		return nullptr;
	}

	if (rhs == nullptr) {

		Set_Token_Ptr(tp);

		rhs = ParseVariableExpression();
		if (error) {
			return nullptr;
		}

		if (rhs == nullptr) {
			//error

			error = true;
			error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
			error_message += "Error expression for rhs of dot";
			delete lhs;
			return nullptr;
		}
	}

	//rhs is now either a -
	//Variable Expression - where this whole subsection represents an object and a piece of data 
	//Function Expression - where this whole subsection represents an object and a method

	DotExpression* dexpr = new DotExpression;

	dexpr->Set_LHS((VariableExpression*)lhs);
	dexpr->Set_RHS(rhs);
	dexpr->SetLineNumber(lhs->GetLineNumber());

	return dexpr;
}

Expression* Parser::ParseBoolExpression() {
	Token t = GetToken();

	if (t.GetTokenString() == "True") {
		BooleanExpression* be = new BooleanExpression;
		be->SetLineNumber(t.GetLineNumber());
		be->SetValue(true);
		return be;
	}
	else if (t.GetTokenString() == "False") {
		BooleanExpression* be = new BooleanExpression;
		be->SetLineNumber(t.GetLineNumber());
		be->SetValue(false);
		return be;
	}
	else {
		return nullptr;
	}
}

void Parser::CheckBinaryExpressionOrder(BinaryExpression* be) {
	/*
	the upper node is current one being parsed
	the lower node is the rhs node of the upper node
	we know both nodes are binary expression nodes
	now we compare the precedence of each operator
	if they are in the wrong order we perform the next 4 steps

	1.) exchange operator
	2.) exchange upper lhs with lower rhs
	3.) exchange lower lhs with lower rhs
	4.) exchange upper lhs with upper rhs
	*/

	BinaryExpression* rhs = (BinaryExpression*)be->Get_RHS();

	int lower_operator_precedence = OperatorPrecedence(rhs->Get_Operator());
	int upper_operator_precedence = OperatorPrecedence(be->Get_Operator());

	if (upper_operator_precedence < lower_operator_precedence) {
		//we need to perform the exchanges

		//step 1
		std::string tmp_operator = be->Get_Operator();
		be->Set_Operator(rhs->Get_Operator());
		((BinaryExpression*)rhs)->Set_Operator(tmp_operator);

		//step 2
		Expression* tmp_expr = be->Get_LHS();
		be->Set_LHS(rhs->Get_RHS());
		rhs->Set_RHS(tmp_expr);

		//step 3
		tmp_expr = (rhs)->Get_LHS();
		rhs->Set_LHS(rhs->Get_RHS());
		rhs->Set_RHS(tmp_expr);

		//step 4
		tmp_expr = be->Get_LHS();
		be->Set_LHS(be->Get_RHS());
		be->Set_RHS(tmp_expr);
	}

}
