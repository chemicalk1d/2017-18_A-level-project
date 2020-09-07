#ifndef LEXER_HPP
#define LEXER_HPP

#include "Token.hpp"

#include <string>
#include <vector>

class Lexer
{
private:
	//the list of tokens that the new tokens are being added to
	std::vector<Token> tokens;
	
	//the code to lex
	std::string filecontents;

	//integer representing the next characeter in the file contents string
	int charPtr = 0;

	//counter that increments every time a newline is encountered
	int line_number = 1;

	//the file that we are lexing
	std::string filename = "";

	//variable set to true if an error is encounted
	bool error = false;

	//used to look/get the next character
	char PeekChar();
	char GetChar();

	//functions to lex and produce a particular type of token
	void Lex_Number();
	void Lex_String();
	void Lex_Literal();
	void Lex_Symbol(char c);
	void Skip_whitespace();
	void Skip_comment();

	//used to tell if a literal is a specific keyword
	bool is_keyword(std::string str);
public:

	//main lexer function
	void Lex(const std::string& fileContents, std::string file_name);

	std::vector<Token> GetTokens();

	//returns whether or not an error has occurred
	bool Error();
};

#endif