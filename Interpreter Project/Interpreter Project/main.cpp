#include <iostream>
#include <fstream>
#include <string>

#include "Interpreter.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Utils.hpp"
#include "ImportHandling.hpp"

//simple function to take a string and output it to a file
void WriteToFile(std::string filename, std::string data) {
	std::ofstream output;

	output.open(filename);

	//check if the file is open and close with an error message if it is not
	if (!output.is_open()) {
		std::cerr << "Can't open file" << std::endl;
		system("pause");
		exit(0);
	}
	
	//write data to file
	output << data;

	output.close();
}

//simple function that takes a string and adds it to the end of the file
void AppendToFile(std::string filename, std::string data) {
	std::ofstream output;

	output.open(filename, std::ios_base::app | std::ios_base::out);

	//check if the file is open and close with an error message if it is not
	if (!output.is_open()) {
		std::cerr << "Can't open file" << std::endl;
		system("pause");
		exit(0);
	}

	//write data to file
	output << data;

	output.close();
}

void TokensToFile(std::vector<Token> tokens) {
	std::string token_data = "";

	for (auto t : tokens) {
		token_data += "Token Type: " + TokenString[t.GetTokenType()] + "\n";
		token_data += "Token Data: " + t.GetTokenString() + "\n";
		token_data += "Token Line: " + std::to_string(t.GetLineNumber()) + "\n";
		token_data += "Token File: " + t.GetFileName() + "\n\n";
	}

	//used for debugging the lexer
	WriteToFile("LexerOutput.log", token_data);
}

//function that retrieves the directory of a file given the full file path
std::string GetDirectory(std::string filepath) {

	int end = filepath.size() - 1;

	for (std::string::reverse_iterator i = filepath.rbegin(); i != filepath.rend(); ++i) {

		if (*i == '\\') {
			return filepath.substr(0, end) + "\\";
		}
		else if (*i == '/') {
			return filepath.substr(0, end) + "/";
		}

		end--;
	}

	return "";
}

//program entry point
int main(int argc, char** argv) {

	if (argc < 2) {
		//no filename passed as cmdline argument
		std::cout << "Error - No filename passed as command line argument" << std::endl;
		system("pause");
		return 0;
	}
	
	//convert the commandline arguments into a single string
	std::string filename = argv[1];
	for (int i = 2; i < argc; i++) {
		filename += std::string(" ") + std::string(argv[i]);
	}


	//open the file of the first cmd line argument
	std::string filecontents = ReadFile(filename);





	//lex the file
	Lexer l;
	l.Lex(filecontents, filename);

	//retrieve the list of tokens from the file
	std::vector<Token> tokens = l.GetTokens();


	//output the tokens to a file so we can look at them during debugging
	TokensToFile(tokens);

	
	for (auto t : tokens) {
		if (t.GetTokenType() == Token::ERROR) {
			std::cout << t.GetTokenString() << std::endl;
			system("pause");
			exit(0);
		}
	}



	//parser
	Parser parser;
	parser.Parse(tokens, filename);

	//retrieve the abstract syntax tree from the parser object
	AbstractSyntaxTree ast = parser.Get_AST();

	//output the ast to a file so that we can look at it during debugging
	WriteToFile("AST.log", ast.Get_Debug_String());


	//check if there was an error while parsing the code
	if (parser.Error_occured()) {
		std::cout << parser.GetErrorMessage() << std::endl;
		system("pause");
		return 0;
	}
	
	//retrieve the parent directory so that we can pass it to the function that handles import statements
	std::string dir = GetDirectory(filename);

	//goes through the tree and looks at and adds the imports
	HandleImports(ast, dir);

	//adds to the ast log the new modified tree
	AppendToFile("AST.log",	"--------------------------------------------------------------------------------------------------------\n--------------------------------------------------------------------------------------------------------\nAfter Imports\n\n");
	AppendToFile("AST.log", ast.Get_Debug_String());







	//get the single interpreter object and run the interpreter on the full ast including the imports
	Interpreter* interpreter = Interpreter::GetInterpreter();
	interpreter->Run(ast);





	//pause after the program finishes running
	system("pause");

	//free the interpreter and its memory
	Interpreter::DeleteInterpreter();

	//free the abstract syntax tree and its memory
	ast.DeleteStatements();




	return 0;
}