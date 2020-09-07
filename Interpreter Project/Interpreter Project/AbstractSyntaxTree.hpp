#ifndef ABSTRACTSYNTAXTREE_HPP
#define ABSTRACTSYNTAXTREE_HPP

#include <vector>

#include "Statements.hpp"

//top level class in the tree all statements/expressions are a smaller part of this tree
class AbstractSyntaxTree {
private:
	std::vector<Statement*> statements;
public:
	std::vector<Statement*> GetStatements() { return statements; }

	//add a statement onto the vector of statements
	void AddStatement(Statement* st) { 
		if (!statements.empty()) {
			statements.back()->SetNext(st);
		}
		statements.push_back(st);
	}
	
	//add another abstract syntax at the start of this abstract syntax tree
	void CombineFront(AbstractSyntaxTree& other) {
		statements.insert(statements.begin(), other.statements.begin(), other.statements.end());
	}

	//returns a string representation of the AST used for debugging
	std::string Get_Debug_String() {
		std::string str;
		for (auto st : statements) {
			str += st->Get_Debug_String();
		}
		return str;
	}

	
	//used to avoid memory leaks
	void DeleteStatements() {
		for (auto st : statements) {
			delete st;
		}
	}

};

#endif
