#include "Parser.hpp"

#include "Utils.hpp"

#include <cassert>

//main function to pass all the tokens
void Parser::Parse(std::vector<Token> Tokens, std::string file_name) {
	
	filename = file_name;

	tokens = Tokens;

	//keep looping until we reach the end of the file
	while (tokens[token_ptr].GetTokenType() != Token::END_OF_FILE) {
		Statement* st = ParseStatement();

		if (st != nullptr) {
			AST.AddStatement(st);
		}

		if (error) {
			break;
		}

	}

}

//given an string returns true if that string is a valid binary
//operator, else it returns false
bool Parser::IsBinaryOperator(const std::string& str) {
	if (str == "+") {
		return true;
	}
	else if (str == "-") {
		return true;
	}
	else if (str == "*") {
		return true;
	}
	else if (str == "/") {
		return true;
	}
	else if (str == "=") {
		return true;
	}
	else if (str == "<>") {
		return true;
	}
	else if (str == "<") {
		return true;
	}
	else if (str == ">") {
		return true;
	}
	else if (str == "<=") {
		return true;
	}
	else if (str == ">=") {
		return true;
	}
	else if (str == "And") {
		return true;
	}
	else if (str == "Or") {
		return true;
	}
	return false;
}

//returns true if string is a valid unary operator
bool Parser::IsUnaryOperator(const std::string& str) {
	if (str == "-") {
		return true;
	}
	else if (str == "Not") {
		return true;
	}
	else {
		return false;
	}
}

bool Parser::is_keyword(std::string str) {
	if (str == "If") {
		return true;
	}
	else if (str == "ElseIf") {
		return true;
	}
	else if (str == "Else") {
		return true;
	}
	else if (str == "EndIf") {
		return true;
	}
	else if (str == "Then") {
		return true;
	}
	else if (str == "And") {
		return true;
	}
	else if (str == "For") {
		return true;
	}
	else if (str == "EndFor") {
		return true;
	}
	else if (str == "EndSub") {
		return true;
	}
	else if (str == "EndWhile") {
		return true;
	}
	else if (str == "Goto") {
		return true;
	}
	else if (str == "Or") {
		return true;
	}
	else if (str == "Step") {
		return true;
	}
	else if (str == "Sub") {
		return true;
	}
	else if (str == "To") {
		return true;
	}
	else if (str == "While") {
		return true;
	}
	else {
		return false;
	}
}
