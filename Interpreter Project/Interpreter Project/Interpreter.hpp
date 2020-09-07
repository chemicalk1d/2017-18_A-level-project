#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "Value.hpp"
#include "AbstractSyntaxTree.hpp"
#include "InterpreterUtils.hpp"
#include "Object.hpp"

#include <map>
#include <stack>

//The interpreter is a singleton object used to interpret the abstract syntax tree
class Interpreter
{
private:
	//the abstract syntax tree to interpret
	AbstractSyntaxTree ast;

	//map of variables and their names
	std::map<std::string, Value> variables;

	//map of objects and their names
	std::map<std::string, Object> objects;

	//boolean to say whether the interpreter is running
	bool running = true;
	
	//used in error handling
	bool runtime_error = false;
	std::string error_message = "";

	//pointer to the next statement to be evaluated
	Statement* nextStatement;

	//contains all the labels in the program
	std::map<std::string, Statement*> labels;

	//conatins the parent subroutine object in all the programs
	std::map<std::string, Subroutine*> subroutines;

	//used to allow multiple subroutine calls or recursive subroutines.
	//these are the return points at the end of a subroutine
	std::stack<Statement*> call_stack;

	//singleton object
	static Interpreter* global_object;

	//used to distinguish an equals sign in a binary expression from comparison and assignment
	bool inside_evaluation_expression = false;


	//statement evaluation
	void EvaluateStatement(Statement* st);
	void EvaluateExpressionStatement(ExpressionStatement* st);
	void EvaluateLabelStatement(LabelStatement* ls);
	void EvaluateGotoStatement(GotoStatement* gs);
	void EvaluateIfStatement(IfStatement* ifst);
	bool EvaluateElseIfStatement(IfStatement::ElseIfClause* if_el_st);
	void EvaluateWhileLoop(WhileLoop* wh_lp);
	void EvaluateForLoop(ForLoop* f_lp);
	void EvaluateSubroutine(Subroutine* sub);
	void EvaluateEndSub(EndSub* eSub);
	void EvaluateBreakStatement(BreakStatement* bs);
	void EvaluateContinueStatement(ContinueStatement* cs);
	void EvaluateImportStatement(ImportStatement* is);

	//expression evaluation
	Value EvaluateExpression(Expression* expr);
	Value EvaluateBinaryExpression(BinaryExpression* expr);
	Value EvaluateUnaryExpression(UnaryExpression* expr);
	Value EvaluateFunctionCallExpression(FunctionExpression* expr);
	Value EvaluateVariableExpression(VariableExpression* expr);
	Value EvaluateIntExpression(IntExpression* expr);
	Value EvaluateBoolExpression(BooleanExpression* expr);
	Value EvaluateDecimalExpression(DecimalExpression* expr);
	Value EvaluateStringExpression(StringExpression* expr);
	Value EvaluateDotExpression(DotExpression* expr);

	//Binary Expression Evaluation for each different type of operator
	Value BinaryExpression_Addition(BinaryExpression* expr);
	Value BinaryExpression_Subtraction(BinaryExpression* expr);
	Value BinaryExpression_Multiplication(BinaryExpression* expr);
	Value BinaryExpression_Division(BinaryExpression* expr);
	Value BinaryExpression_Assignment(BinaryExpression* expr);
	Value BinaryExpression_EqualTo(BinaryExpression* expr);
	Value BinaryExpression_NotEqualTo(BinaryExpression* expr);
	Value BinaryExpression_LessThan(BinaryExpression* expr);
	Value BinaryExpression_LessThanOrEqualTo(BinaryExpression* expr);
	Value BinaryExpression_GreaterThan(BinaryExpression* expr);
	Value BinaryExpression_GreaterThanOrEqualTo(BinaryExpression* expr);
	Value BinaryExpression_And(BinaryExpression* expr);
	Value BinaryExpression_Or(BinaryExpression* expr);

	//Dot Expression Evaluation for both types of dot expressions
	Value DotExpression_DataProperty(DotExpression* expr);
	Value DotExpression_DataMethod(DotExpression* expr);

	//variable helper functions
	void SetVariable(std::string name, Value v);
	Value GetVariable(std::string name);

	//property help functions
	Value Set_Property(std::string object, std::string prop, Value v);
	Value Get_Property(std::string object, std::string prop);

	//used to setup objects such as the TextWindow object
	void SetupObjects();

	//main interpreter function
	void Loop();

	//goes through each statement and finds the labels and adds them to the map of labels
	void LabelPass(Statement* st);

	//label pass for different types of statements that requires specilization
	void LabelPassLabelStatement(LabelStatement* st);
	void LabelPassIfStatement(IfStatement* st);
	void LabelPassWhileLoop(WhileLoop* st);
	void LabelPassForLoop(ForLoop* st);
	void LabelPassSubroutine(Subroutine* st);

	//goes through each statement and sets the statement next pointers
	//so that the interpreter can follow them when interpreting
	void DirectionPass(std::vector<Statement*> stv, Statement* current_loop = nullptr);

	//direction pass function for each different for type 
	void DirectionPassExpressionStatement(std::vector<Statement*> stv, int i, Statement* current_loop = nullptr);
	void DirectionPassLabelStatement(std::vector<Statement*> stv, int i, Statement* current_loop = nullptr);
	void DirectionPassGotoStatement(std::vector<Statement*> stv, int i, Statement* current_loop = nullptr);
	void DirectionPassIfStatement(std::vector<Statement*> stv, int i, Statement* current_loop = nullptr);
	void DirectionPassWhileLoop(std::vector<Statement*> stv, int i, Statement* current_loop = nullptr);
	void DirectionPassForLoop(std::vector<Statement*> stv, int i, Statement* current_loop = nullptr);
	void DirectionPassSubroutine(std::vector<Statement*> stv, int i, Statement* current_loop = nullptr);
	void DirectionPassEndSub(std::vector<Statement*> stv, int i, Statement* current_loop = nullptr);
	void DirectionPassBreakStatement(std::vector<Statement*> stv, int i, Statement* current_loop = nullptr);
	void DirectionPassContinueStatement(std::vector<Statement*> stv, int i, Statement* current_loop = nullptr);
	void DirectionPassImportStatement(std::vector<Statement*> stv, int i, Statement* current_loop = nullptr);

	//make the constructor private to force there to be only one object
	Interpreter() {}

public:
	//the function that is used to interpret a piece of code
	//the argument it takes is the code to interpret
	void Run(AbstractSyntaxTree ast);

	//can be called to stop the interpreter running
	void Stop() {
		running = false;
	}

	//static function that retrieves the singleton object
	static Interpreter* GetInterpreter() {
		if (global_object != nullptr) {
			return global_object;
		}
		else {
			global_object = new Interpreter;
			return global_object;
		}
	}

	//static function that deletes the singleton object
	static void DeleteInterpreter() {
		if (global_object != nullptr) {
			delete global_object;
		}
	}
};

#endif