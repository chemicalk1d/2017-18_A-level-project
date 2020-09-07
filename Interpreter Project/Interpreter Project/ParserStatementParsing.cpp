#include "Parser.hpp"

#include "Utils.hpp"

#include <cassert>

//overall function for parsing statements
Statement* Parser::ParseStatement() {

	Statement* st = nullptr;
	int tp;
	tp = Get_Token_Ptr();

	st = ParseLabel();
	if (error) {
		return nullptr;
	}
	if (st != nullptr) {
		st->SetStatementFileName(filename);
		return st;
	}
	Set_Token_Ptr(tp);

	st = ParseGoto();
	if (error) {
		return nullptr;
	}
	if (st != nullptr) {
		st->SetStatementFileName(filename);
		return st;
	}
	Set_Token_Ptr(tp);

	st = ParseIfStatement();
	if (error) {
		return nullptr;
	}
	if (st != nullptr) {
		st->SetStatementFileName(filename);
		return st;
	}
	Set_Token_Ptr(tp);

	st = ParseWhileLoop();
	if (error) {
		return nullptr;
	}
	if (st != nullptr) {
		st->SetStatementFileName(filename);
		return st;
	}
	Set_Token_Ptr(tp);

	st = ParseForLoop();
	if (error) {
		return nullptr;
	}
	if (st != nullptr) {
		st->SetStatementFileName(filename);
		return st;
	}
	Set_Token_Ptr(tp);

	st = ParseSubroutine();
	if (error) {
		return nullptr;
	}
	if (st != nullptr) {
		st->SetStatementFileName(filename);
		return st;
	}
	Set_Token_Ptr(tp);

	st = ParseBreakStatement();
	if (error) {
		return nullptr;
	}
	if (st != nullptr) {
		st->SetStatementFileName(filename);
		return st;
	}
	Set_Token_Ptr(tp);

	st = ParseContinueStatement();
	if (error) {
		return nullptr;
	}
	if (st != nullptr) {
		st->SetStatementFileName(filename);
		return st;
	}
	Set_Token_Ptr(tp);

	st = ParseImportStatement();
	if (error) {
		return nullptr;
	}
	if (st != nullptr) {
		st->SetStatementFileName(filename);
		return st;
	}
	Set_Token_Ptr(tp);

	st = ParseExpressionStatement();
	if (error) {
		return nullptr;
	}
	if (st != nullptr) {
		st->SetStatementFileName(filename);
		return st;
	}
	Set_Token_Ptr(tp);


	return nullptr;
}

//tries to parse an expression as a statement
Statement* Parser::ParseExpressionStatement() {
	Expression* expr = ParseExpression();
	if (error) {
		return nullptr;
	}
	if (expr == nullptr) {
		return nullptr;
	}
	ExpressionStatement* exprSt = new ExpressionStatement;
	exprSt->SetExpression(expr);
	exprSt->SetLineNumber(expr->GetLineNumber());
	return exprSt;
}


Statement* Parser::ParseLabel() {

	Token t;

	t = GetToken();

	if (t.GetTokenType() != Token::LITERAL || is_keyword(t.GetTokenString())) {
		return nullptr;
	}
	//else

	std::string name = t.GetTokenString();

	t = GetToken();

	if (t.GetTokenString() != ":") {
		return nullptr;
	}

	LabelStatement* ls = new LabelStatement;

	ls->SetLineNumber(t.GetLineNumber());
	ls->SetName(name);
	return ls;
}

Statement* Parser::ParseGoto() {

	Token t;

	t = GetToken();

	if (t.GetTokenString() != "Goto") {
		return nullptr;
	}
	//else

	int line_number = t.GetLineNumber();

	t = GetToken();

	if (t.GetTokenType() != Token::LITERAL || is_keyword(t.GetTokenString())) {
		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no literal after goto keyword";
		return nullptr;
	}

	GotoStatement* gs = new GotoStatement;

	gs->SetLineNumber(line_number);
	gs->SetName(t.GetTokenString());

	return gs;
}

Statement* Parser::ParseIfStatement() {
	Token t = GetToken();

	if (t.GetTokenString() != "If") {
		return nullptr;
	}
	//else

	//save the line number for later
	int line_number = t.GetLineNumber();

	//try to parse the condition for the if statement
	Expression* expr = ParseExpression();
	if (expr == nullptr) {
		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no expression to evaluate in If statement";
		return nullptr;
	}

	//get token for what should be the then keyword
	t = GetToken();

	if (t.GetTokenString() != "Then") {
		//error
		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no then keyword in If statement";
		return nullptr;
	}

	//create if statement and set line number and condition expression
	IfStatement* ifst = new IfStatement;
	ifst->SetLineNumber(line_number);
	ifst->SetCondition(expr);


	int tp = Get_Token_Ptr();

	//loop adding the statements inside the if clause
	Statement* st = ParseStatement();
	while (st != nullptr) {
		tp = Get_Token_Ptr();
		ifst->AddStatement(st);
		st = ParseStatement();
	}

	Set_Token_Ptr(tp);

	//loop adding all the possible else if clauses if there are any
	IfStatement::ElseIfClause* el_if_cl = ParseElseIf();
	while (el_if_cl != nullptr) {
		tp = Get_Token_Ptr();
		ifst->AddElseIfClause(el_if_cl);
		el_if_cl = ParseElseIf();
	}

	Set_Token_Ptr(tp);

	//add an else clause if there is one
	IfStatement::ElseClause* el_cl = ParseElse();
	if (el_cl != nullptr) {
		ifst->SetElseClause(el_cl);
	}
	else {
		Set_Token_Ptr(tp);
	}

	//Get the EndIf keyword
	t = GetToken();
	if (t.GetTokenString() != "EndIf") {
		//error

		delete ifst;

		error = true;
		error_message += "Syntax error at line " + std::to_string(line_number) + "\n";
		error_message += "Error EndIf to end If statement block";
		return nullptr;
	}

	return ifst;
}

IfStatement::ElseIfClause* Parser::ParseElseIf() {

	Token t = GetToken();
	if (t.GetTokenString() != "ElseIf") {
		return nullptr;
	}
	//else

	int line_number = t.GetLineNumber();

	//try to parse the condition for the ElseIf statement
	Expression* expr = ParseExpression();
	if (expr == nullptr) {
		//error
		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no expression to evaluate in ElseIf statement";
		return nullptr;
	}

	IfStatement::ElseIfClause* el_if_cl = new IfStatement::ElseIfClause;
	el_if_cl->SetCondition(expr);
	el_if_cl->Set_Line_Number(line_number);

	t = GetToken();

	if (t.GetTokenString() != "Then") {
		//error
		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no then keyword to evaluate in ElseIf statement";
		return nullptr;
	}
	//else

	Statement* st = ParseStatement();

	while (st != nullptr) {
		el_if_cl->AddStatement(st);
		st = ParseStatement();
	}

	return el_if_cl;
}

IfStatement::ElseClause* Parser::ParseElse() {

	Token t = GetToken();
	if (t.GetTokenString() != "Else") {
		return nullptr;
	}
	//else

	IfStatement::ElseClause* el_cl = new IfStatement::ElseClause;
	el_cl->Set_Line_Number(t.GetLineNumber());

	Statement* st = ParseStatement();
	while (st != nullptr) {
		el_cl->AddStatement(st);
		st = ParseStatement();
	}
	return el_cl;
}

Statement* Parser::ParseForLoop() {
	Token t;

	t = GetToken();

	if (t.GetTokenString() != "For") {
		return nullptr;
	}
	//else

	int line_number = t.GetLineNumber();

	//first parse the variable
	//then the equals sign
	//after that it is the start expression
	//then it is the "To" keyword
	//then it is the end expression
	//if there is the keyword "Step" then there is also the step expression

	VariableExpression* var = (VariableExpression*)ParseVariableExpression();
	if (var == nullptr) {
		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no variable to evaluate in For Loop";
		return nullptr;
	}
	//else

	t = GetToken();
	if (t.GetTokenString() != "=") {

		delete var;

		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no equals sign to evaluate in For Loop";
		return nullptr;
	}
	//else

	Expression* start = ParseExpression();
	if (start == nullptr) {

		delete var;

		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no start expression to evaluate in For Loop";
		return nullptr;
	}
	//else

	t = GetToken();
	if (t.GetTokenString() != "To") {

		delete var, start;

		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no To keyword to evaluate in for loop";
		return nullptr;
	}
	//else

	Expression* end = ParseExpression();
	if (end == nullptr) {

		delete var, start;

		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no end expression to evaluate in For Loop";
		return nullptr;
	}
	//else

	Expression* step = nullptr;
	int tp = Get_Token_Ptr();
	t = GetToken();
	if (t.GetTokenString() == "Step") {
		//handle step expression
		step = ParseExpression();
		if (step == nullptr) {

			delete var, start, end;

			error = true;
			error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
			error_message += "Error no Step expression to evaluate in For Loop despite Step keyword";
			return nullptr;
		}
	}
	else {
		Set_Token_Ptr(tp);
	}
	ForLoop* forLoop = new ForLoop;

	forLoop->SetVariable(var);
	forLoop->SetStart(start);
	forLoop->SetEnd(end);
	forLoop->SetStep(step);

	tp = Get_Token_Ptr();

	//loop to parse the sub statements
	Statement* st = ParseStatement();
	while (st != nullptr) {
		forLoop->AddStatement(st);
		tp = Get_Token_Ptr();
		st = ParseStatement();
	}

	Set_Token_Ptr(tp);

	//get the endfor keyword
	t = GetToken();
	if (t.GetTokenString() != "EndFor") {

		delete forLoop;

		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no EndFor to end the For loop block";
		return nullptr;
	}

	return forLoop;
}

Statement* Parser::ParseWhileLoop() {
	Token t;

	t = GetToken();

	if (t.GetTokenString() != "While") {
		return nullptr;
	}
	//else

	int line_number = t.GetLineNumber();

	//try to parse the condition for the while loop
	Expression* expr = ParseExpression();
	if (expr == nullptr) {
		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no expression to evaluate in while loop";
		return nullptr;
	}

	//create object and set values
	WhileLoop* wh_lp = new WhileLoop;
	wh_lp->SetLineNumber(line_number);
	wh_lp->SetCondition(expr);

	int tp = Get_Token_Ptr();

	//loop to parse the sub statements
	Statement* st = ParseStatement();
	while (st != nullptr) {
		wh_lp->AddStatement(st);
		tp = Get_Token_Ptr();
		st = ParseStatement();
	}

	Set_Token_Ptr(tp);

	//get the endwhile keyword
	t = GetToken();
	if (t.GetTokenString() != "EndWhile") {

		delete wh_lp;

		error = true;
		error_message += "Syntax error at line " + std::to_string(line_number) + "\n";
		error_message += "Error no EndWhile to end the While loop block";
		return nullptr;
	}

	return wh_lp;
}

Statement* Parser::ParseSubroutine() {

	Token t = GetToken();
	if (t.GetTokenString() != "Sub") {
		return nullptr;
	}
	//else

	int line_number = t.GetLineNumber();

	t = GetToken();

	if (t.GetTokenType() != Token::LITERAL || is_keyword(t.GetTokenString())) {
		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no subroutine name to evaluate in If statement";
		return nullptr;
	}
	//else

	std::string name = t.GetTokenString();

	Subroutine* sub = new Subroutine;
	sub->SetLineNumber(line_number);
	sub->SetName(name);

	int tp = Get_Token_Ptr();

	//loop to parse the sub statements
	Statement* st = ParseStatement();
	while (st != nullptr) {
		sub->AddStatement(st);
		tp = Get_Token_Ptr();
		st = ParseStatement();
	}

	Set_Token_Ptr(tp);

	t = GetToken();
	if (t.GetTokenString() != "EndSub") {

		delete sub;

		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no EndSub to end the Subroutine block";
		return nullptr;
	}

	return sub;
}

Statement* Parser::ParseBreakStatement() {
	Token t;
	t = GetToken();

	if (t.GetTokenString() != "Break") {
		return nullptr;
	}

	BreakStatement* bs = new BreakStatement;
	bs->SetLineNumber(t.GetLineNumber());
	return bs;
}

Statement* Parser::ParseContinueStatement() {
	Token t;
	t = GetToken();

	if (t.GetTokenString() != "Continue") {
		return nullptr;
	}

	ContinueStatement* cs = new ContinueStatement;
	cs->SetLineNumber(t.GetLineNumber());
	return cs;
}

Statement* Parser::ParseImportStatement() {
	Token t;
	t = GetToken();

	if (t.GetTokenString() != "Import") {
		return nullptr;
	}

	int line_number = t.GetLineNumber();

	t = GetToken();

	if (t.GetTokenType() != Token::STRING) {
		error = true;
		error_message += "Syntax error at line " + std::to_string(t.GetLineNumber()) + "\n";
		error_message += "Error no String to evaluate in import statement";
		return nullptr;
	}

	ImportStatement* is = new ImportStatement;
	is->SetFilePath(t.GetTokenString());
	is->SetLineNumber(line_number);
	return is;
}