#include "Lexer.hpp"


//function retrieves the next character from the string without
//incrementing the index, repeating this function will give you the same
char Lexer::PeekChar() {
	if (charPtr >= filecontents.size()) {
		return EOF;
	}
	else {
		return filecontents[charPtr];
	}
}

//the function retrieves the next character from the string and does
//increment the index, repeating this function iterates through the list
//also increase the line number everytime there is a new line
char Lexer::GetChar() {
	if (charPtr >= filecontents.size()) {
		return EOF;
	}
	else {

		if (filecontents[charPtr] == '\n') {
			line_number++;
		}

		return filecontents[charPtr++];
	}
}

//keeps reading digits until it cannot read any further
//it also reads in decimal numbers and checks to see if the decimal number
//has more than one decimal place
void Lexer::Lex_Number() {
	std::string number;

	int decimalPoints = 0;

	while (isdigit(PeekChar()) || PeekChar() == '.') {
		if (PeekChar() == '.') {
			decimalPoints++;
		}
		number += GetChar();
	}

	//error checking to check if their is more than one decimal point in the string
	//if there is more than one decimal point in the string then that is an error
	if (decimalPoints > 1) {
		Token t;
		t.SetTokenString("More than 1 Decimal Point in number");
		t.SetTokenType(Token::ERROR);
		t.SetLineNumber(line_number);
		t.SetFileName(filename);
		tokens.push_back(t);
		error = true;
		return;
	}

	Token t;
	t.SetTokenString(number);
	t.SetLineNumber(line_number);
	t.SetFileName(filename);
	if (decimalPoints == 0) {
		t.SetTokenType(Token::INTEGER);
	}
	else {
		t.SetTokenType(Token::DECIMAL);
	}
	tokens.push_back(t);
}

//keeps reading characters in from a speech mark enclosed string
//if it gets to either the end of the line or the end of the file
//then it creates and error that the string has not been properly ended
void Lexer::Lex_String() {
	std::string string = "";

	while (PeekChar() != '\"') {

		if (PeekChar() == EOF || PeekChar() == '\n') {
			//error
			Token t;
			t.SetTokenString("No closing speech mark for string");
			t.SetTokenType(Token::ERROR);
			t.SetLineNumber(line_number);
			t.SetFileName(filename);
			tokens.push_back(t);
			error = true;
			return;
		}



		if (PeekChar() != '\\') {
			string += GetChar();
		}
		else {
			//escape character

			GetChar();

			char c2 = GetChar();

			switch (c2)
			{
			case 'n':
				string += "\n";
				break;
			case 'v':
				string += "\v";
				break;
			case '\\':
				string += "\\";
				break;
			case 't':
				string += "\t";
				break;
			case 'r':
				string += "\r";
				break;
			case 'f':
				string += "\f";
				break;
			case '\"':
				string += "\"";
				break;
			default:
				//error
				Token t;
				t.SetTokenString("Unknown String Escape Sequence");
				t.SetTokenType(Token::ERROR);
				error = true;
				return;
			}
		}
	}

	//remove ending speech marks
	GetChar();

	//create string token and add to list of tokens
	Token t;
	t.SetTokenString(string);
	t.SetTokenType(Token::STRING);
	t.SetLineNumber(line_number);
	t.SetFileName(filename);
	tokens.push_back(t);
}

//lexes and identifier such as the word print
void Lexer::Lex_Literal() {
	std::string lit = "";

	//loop through the characters until we find a 
	//character that is not part of the word
	while (isalnum(PeekChar()) || PeekChar() =='_') {
		lit += GetChar();
	}
	
	//create token and add to end of token list
	Token t;
	t.SetTokenString(lit);
	t.SetTokenType(Token::LITERAL);
	t.SetLineNumber(line_number);
	t.SetFileName(filename);
	tokens.push_back(t);
}


void Lexer::Lex_Symbol(char c) {
	Token t;
	t.SetTokenType(Token::SYMBOL);

	char c2 = '\0';

	switch (c)
	{
	case '+':
		t.SetTokenString("+");
		break;
	case '-':
		t.SetTokenString("-");
		break;
	case '*':
		t.SetTokenString("*");
		break;
	case '/':
		t.SetTokenString("/");
		break;
	case '=':
		t.SetTokenString("=");
		break;
	case '(':
		t.SetTokenString("(");
		break;
	case ')':
		t.SetTokenString(")");
		break;
	case ',':
		t.SetTokenString(",");
		break;
	case '<':
		GetChar();
		c2 = PeekChar();

		switch (c2)
		{
		case '=':
			GetChar();
			t.SetTokenString("<=");
			break;
		case '>':
			GetChar();
			t.SetTokenString("<>");
			break;
		default:
			t.SetTokenString("<");
			break;
		}

		break;
	case '>':
		GetChar();
		c2 = PeekChar();

		switch (c2)
		{
		case '=':
			GetChar();
			t.SetTokenString(">=");
			break;
		default:
			t.SetTokenString(">");
			break;
		}
		break;
	case '.':
		t.SetTokenString(".");
		break;
	case ':':
		t.SetTokenString(":");
		break;
	case '[':
		t.SetTokenString("[");
		break;
	case ']':
		t.SetTokenString("]");
		break;
	default:
		//error
		t.SetTokenString("Unknown Character");
		t.SetTokenType(Token::ERROR);
		error = true;
		break;
	}
	GetChar();
	t.SetLineNumber(line_number);
	t.SetFileName(filename);
	tokens.push_back(t);
}

//keep removing characters from the list until while they are whitespace characters
void Lexer::Skip_whitespace() {
	while (isspace(PeekChar())) {
		GetChar();
	}
}

//keeps going until it reaches the end of the line
void Lexer::Skip_comment() {
	char c;
	do {
		c = GetChar();
	} while (c != '\n' && c != '\r' && c != EOF);
}

//overall lex function
//it checks the characeter it has just looked at and then calls the appropriate function
//based on what the character is, it also lexes individual symbols such as addition and subtraction
void Lexer::Lex(const std::string& fileContents, std::string file_name) {
	filecontents = fileContents;

	filename = file_name;

	char c = PeekChar();

	//keep looping until we get to the end of the file or there is and error
	while (c != EOF && !error) {
		if (isalpha(c) || c == '_') {
			Lex_Literal();
		}
		else if (c == '\"') {
			GetChar();
			Lex_String();
		}
		else if (c == '\'') {
			Skip_comment();
		}
		else if (isdigit(c)) {
			Lex_Number();
		}
		else if (isspace(c)) {
			Skip_whitespace();
		}
		else {
			Lex_Symbol(c);
		}
		c = PeekChar();
	}

	//add an end of file token at the end of the list of tokens
	Token t;
	t.SetTokenType(Token::END_OF_FILE);
	t.SetTokenString("{EOF}");
	t.SetLineNumber(-1);
	t.SetFileName(filename);
	tokens.push_back(t);
}

//returns the list of tokens created by this lexer
std::vector<Token> Lexer::GetTokens() {
	return tokens;
}

//returns whether this lexer encountered an error while lexing
bool Lexer::Error() {
	return error;
}

//checks the string against the given keywords and returns true if 
//the string is one of the keywords
bool Lexer::is_keyword(std::string str) {
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
	else if (str == "Break") {
		return true;
	}
	else if (str == "Continue") {
		return true;
	}
	else if (str == "Import") {
		return true;
	}
	else if (str == "True") {
		return true;
	}
	else if (str == "False") {
		return true;
	}
	else {
		return false;
	}
}