#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <fstream>
#include <iostream>

//returns a numerical number representitive of the order of operations
//returns -1 if the value passed to the function is not a known operator
inline int OperatorPrecedence(std::string Op) {
	if (Op == "+") {//addition
		return 5;
	}
	else if (Op == "-") {//subtraction
		return 5;
	}
	else if (Op == "*") {//multiplication
		return 4;
	}
	else if (Op == "/") {//division
		return 4;
	}
	else if (Op == "=") {//assigment and equal to
		return 6;
	}
	else if (Op == "<") {//less than comparison
		return 6;
	}
	else if (Op == ">") {//greater than comparison
		return 6;
	}
	else if (Op == "<=") {//less than or equal to
		return 6;
	}
	else if (Op == ">=") {//greater than or equal to
		return 6;
	}
	else if (Op == "<>") {//not equal to
		return 6;
	}
	else if (Op == "And") {
		return 7;
	}
	else if (Op == "Or") {
		return 7;
	}
	else {
		return -1;
	}
}

//function to open a file and read the file into a string before closing the file and returning the string
inline std::string ReadFile(const std::string& filename) {
	std::string contents;

	//open file
	std::ifstream infile(filename);

	if (!infile.is_open()) {
		//file cannot be opened, show an error and then close

		std::cout << "Cannot Open File: " << filename << std::endl;
		std::cerr << strerror(errno) << std::endl;
		system("pause");
		exit(0);
	}

	//read each character from the file until we get to the end of the file
	while (infile.peek() != EOF) {
		contents += infile.get();
	}

	//close the file
	infile.close();

	return contents;
}

#endif