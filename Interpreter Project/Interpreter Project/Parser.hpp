#ifndef PARSER_HPP
#define PARSER_HPP

#include "AbstractSyntaxTree.hpp"
#include "Expressions.hpp"
#include "Statements.hpp"
#include "Token.hpp"

#include <vector>

class Parser
{
private:
	//the current Abstract Syntax Tree that is being created
	AbstractSyntaxTree AST;

	//the list of tokens that has been given to the parser
	std::vector<Token> tokens;

	//pointer to the next token to be read
	int token_ptr = 0;

	//helper functions
	int Get_Token_Ptr() { return token_ptr; }
	void Set_Token_Ptr(int tp) { token_ptr = tp; }
	Token GetToken() {return tokens[token_ptr++];}
	bool IsBinaryOperator(const std::string& str);
	bool IsUnaryOperator(const std::string& str);

	//used to tell if a literal is a specific keyword
	bool is_keyword(std::string str);

	//parsing expressions
	Expression* ParseExpression(bool skip_binary_expression = false);
	Expression* ParseBracketExpression();
	Expression* ParseBinaryExpression();
	Expression* ParseUnaryExpression();
	Expression* ParseFunctionCallExpression();
	Expression* ParseStringExpression();
	Expression* ParseIntExpression();
	Expression* ParseBoolExpression();
	Expression* ParseDecimalExpression();
	Expression* ParseVariableExpression();
	Expression* ParseDotExpression();

	//function used for handling binary expressions and order of operations
	void CheckBinaryExpressionOrder(BinaryExpression* be);

	//parsing statements
	Statement* ParseStatement();
	Statement* ParseExpressionStatement();
	Statement* ParseLabel();
	Statement* ParseGoto();
	Statement* ParseIfStatement();
	IfStatement::ElseIfClause* ParseElseIf();
	IfStatement::ElseClause* ParseElse();
	Statement* ParseForLoop();
	Statement* ParseWhileLoop();
	Statement* ParseSubroutine();
	Statement* ParseBreakStatement();
	Statement* ParseContinueStatement();
	Statement* ParseImportStatement();

	//used for error handling
	bool error = false;
	std::string error_message = "";

	std::string filename;

public:
	//main parsing function
	void Parse(std::vector<Token> tokens, std::string file_name);

	//returns the created Abstract Syntax Tree
	AbstractSyntaxTree Get_AST() { return AST; }

	//used for error handling
	bool Error_occured() { return error; }
	std::string GetErrorMessage() { return error_message; }
};

#endif