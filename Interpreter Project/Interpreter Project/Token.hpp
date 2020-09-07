#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token
{
public:
	//an enumeration used to differentiate between different types of tokens
	enum TokenType {
		STRING = 0,
		LITERAL = 1,
		KEYWORD = 2,
		DECIMAL = 3,
		INTEGER = 4,
		SYMBOL = 5,
		ERROR = 6,
		END_OF_FILE = 7,
	};

private:
	std::string tokenString; // string representing the data of the token
	TokenType type;//enumeration representing the type of token this is
	int line_number;//the line where this token occurs
	std::string file_name;//the file where this token occurs
public:

	//get/set the token type of the token
	TokenType GetTokenType()const{ return type; }
	void SetTokenType(TokenType Type) { type = Type; }

	//get/set the data of the token
	std::string GetTokenString()const{ return tokenString; }
	void SetTokenString(const std::string& string) { tokenString = string; }

	//get/set the line number of the token
	int GetLineNumber() { return line_number; }
	void SetLineNumber(int ln) { line_number = ln; }

	std::string GetFileName() { return file_name; }
	void SetFileName(std::string fn) { file_name = fn; }
};

//used to convert TokenType enum to string
static const std::string TokenString[] = {
	"STRING",
	"LITERAL",
	"KEYWORD",
	"DECIMAL",
	"INTEGER",
	"SYMBOL",
	"ERROR",
	"END_OF_FILE",
};

#endif