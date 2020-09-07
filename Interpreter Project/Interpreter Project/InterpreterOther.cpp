#include "Interpreter.hpp"

#include "Object.hpp"
#include "Methods.hpp"

#include <iostream>

Interpreter* Interpreter::global_object = nullptr;


//variable helper functions
void Interpreter::SetVariable(std::string name, Value v) {
	//automatically creates a variable 
	variables[name] = v;
}

Value Interpreter::GetVariable(std::string name) {
	//automatically creates and returns a null Value if it is not in the map
	return variables[name];
}

Value Interpreter::Set_Property(std::string object, std::string prop, Value v) {
	Object obj = objects[object];
	Object::Property p = obj.GetProperty(prop);
	return p.setter(v, runtime_error, error_message);
}

Value Interpreter::Get_Property(std::string object, std::string prop) {
	Object obj = objects[object];
	Object::Property p = obj.GetProperty(prop);
	return p.getter();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


void Interpreter::Loop() {

		EvaluateStatement(nextStatement);
		if (runtime_error) {
			return;
		}
}

void Interpreter::Run(AbstractSyntaxTree AST) {
	
	ast = AST;

	nextStatement = ast.GetStatements()[0];

	SetupObjects();

	for (auto st : AST.GetStatements()) {
		LabelPass(st);
	}

	DirectionPass(ast.GetStatements());
	
	while (running) {
		Loop();

		if (runtime_error) {
			std::cout << "\n\n" << error_message << std::endl;
			running = false;
		}
		else if (nextStatement == nullptr) {
			running = false;
		}
	}
}