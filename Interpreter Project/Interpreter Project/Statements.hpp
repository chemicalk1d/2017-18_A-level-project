#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include <string>
#include <vector>

#include "Expressions.hpp"


//abstract statement class
class Statement {
protected:
	//line where this statement starts
	int line = -1;

	//file where this statement is
	std::string filename = "";

	//pointer to the next statement - creates a sort of linked list of statements
	//that can be traversed by the interpreter when interpreting the Tree
	//a nullptr means that the interpreter has reached the end of the program
	Statement* next = nullptr;

public:

	//line number get/set
	int GetLineNumber() { return line; }
	void SetLineNumber(int line_number) { line = line_number; }

	//pointer to the next statement get/set
	Statement* GetNext() { return next; }
	void SetNext(Statement* nxt) { next = nxt; }

	//statement file name get/set
	std::string GetStatementFileName() { return filename; }
	void SetStatementFileName(std::string fn) { filename = fn; }

	//pure virtual function that returns a string that represents a statement type
	virtual std::string GetStatementType() = 0;

	//destructor
	virtual ~Statement() {}
	
	//pure virtual function that returns a string that is used in debugging the parser
	virtual std::string Get_Debug_String(int tab = 0) = 0;

	//returns a copy of the object and subobjects
	virtual Statement* Duplicate() = 0;
};





//class to bridge the gap between expressions and statements
class ExpressionStatement :public Statement {
private:
	Expression* expr;
public:
	//get and set the sub expression
	Expression* GetExpression() { return expr; }
	void SetExpression(Expression* e) { expr = e; }

	//overrides pure virtual method in Statement class
	std::string GetStatementType() { return "Expression Statement"; }

	//destructor to make wure we delete the sub expression
	~ExpressionStatement(){
		if (expr != nullptr) {
			delete expr;
		}
	}

	//string representation of this node in the abstract syntax tree
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		str += Tab(tab);
		str += "Expression Statement""\n";
		str += expr->Get_Debug_String(tab + 1);
		return str + "\n\n";
	}

	//returns a copy of the object and subobjects
	Statement* Duplicate() {
		ExpressionStatement* st = new ExpressionStatement;
		st->expr = this->GetExpression()->Duplicate();
		st->filename = this->filename;
		st->line = this->line;
		st->next = this->next;
		return st;
	}
};





class LabelStatement :public Statement {
private:
	std::string name;
public:

	//gets and sets the name of this label
	std::string GetName() { return name; }
	void SetName(std::string n) { name = n; }
	
	//overrides pure virtual method in Statement
	std::string GetStatementType() { return "Label Statement"; }

	//function that returns a string representation of this node in the abstract syntax
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		str += Tab(tab);
		str += "Label Statement""\n";
		str += Tab(tab);
		str += "Label Name = " + name + "\n";
		return str + "\n\n";
	}

	//returns a copy of the object and subobjects
	Statement* Duplicate() {
		LabelStatement* st = new LabelStatement;
		st->name = this->name;
		st->filename = this->filename;
		st->line = this->line;
		st->next = this->next;
		return st;
	}

};





//class to represent a goto command
class GotoStatement :public Statement {
private:
	std::string labelname;
public:

	//get and set the name of the label we are going to goto
	std::string GetName() { return labelname; }
	void SetName(std::string n) { labelname = n; }
	
	//overrides pure virtual method 
	std::string GetStatementType() { return "Goto Statement"; }

	//function that returns a string representation of this 
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		str += Tab(tab);
		str += "Goto Statement""\n";
		str += Tab(tab);
		str += "Goto label = " + labelname + "\n";
		return str + "\n\n";
	}

	//returns a copy of the object and subobjects
	Statement* Duplicate() {
		GotoStatement* st = new GotoStatement;
		st->labelname = this->labelname;
		st->filename = this->filename;
		st->line = this->line;
		st->next = this->next;
		return st;
	}
};





//class to represent an if statement
//contains sub classes that are used to represent else if and else clauses
class IfStatement :public Statement {
public:


	//class to represent an else if clause
	class ElseIfClause {
	private:
		Expression* condition;
		std::vector<Statement*> subcode;
		int line_number = -1;
	public:
		//get and set the condition to test for the branch
		void SetCondition(Expression* c) { condition = c; }
		Expression* GetCondition() { return condition; }
		
		//get and set the line number
		void Set_Line_Number(int ln) { line_number = ln; }
		int Get_Line_Number() { return line_number; }

		//get the code inside this Clause and add to the code inside this clause
		std::vector<Statement*> GetSubcode() { return subcode; }
		void AddStatement(Statement* st) { 
			subcode.push_back(st);
		}

		//get string representation of this Node in the abstract syntax tree
		std::string Get_Debug_String(int tab = 0) {
			std::string str;
			str += Tab(tab);
			str += "Else If Clause""\n";
			str += condition->Get_Debug_String(tab) + "\n";
			
			for (auto st : subcode) {
				str += st->Get_Debug_String(tab + 1);
			}

			return str;
		}

		//returns a copy of the object and subobjects
		ElseIfClause* Duplicate() {
			ElseIfClause* st = new ElseIfClause;
			st->condition = this->GetCondition()->Duplicate();
			st->line_number = this->line_number;
			for (auto st2 : this->subcode) {
				st->subcode.push_back(st2->Duplicate());
			}
			return st;
		}
	};





	//class to represent an else clause
	class ElseClause {
	private:
		std::vector<Statement*> subcode;
		int line_number = -1;
	public:

		//get and add to the code inside this else clause
		std::vector<Statement*> GetSubcode() { return subcode; }
		void AddStatement(Statement* st) {
			subcode.push_back(st);
		}

		//get a string representation
		std::string Get_Debug_String(int tab = 0) {
			std::string str;

			str += Tab(tab);
			str += "Else Clause""\n";
			for (auto st : subcode) {
				str += st->Get_Debug_String(tab + 1);
			}
			return str;
		}

		//get and set the line number of the start of this clause
		void Set_Line_Number(int ln) { line_number = ln; }
		int Get_Line_Number() { return line_number; }

		//returns a copy of the object and subobjects
		ElseClause* Duplicate() {
			ElseClause* st;
			st->line_number = this->line_number;
			for (auto st2 : this->subcode) {
				st->subcode.push_back(st2->Duplicate());
			}
			return st;
		}
	};


private:

	Expression* condition;

	std::vector<Statement*> subcode;

	std::vector<ElseIfClause*> elseifClauses;
	ElseClause* elseClause = nullptr;

public:

	//get and set the condition to test of this if statement
	Expression* GetCondition() { return condition; }
	void SetCondition(Expression* c) { condition = c; }

	//get subcode inside this if statement and add to the subcode in this ifstatement
	std::vector<Statement*> GetStatements() { return subcode; }
	void AddStatement(Statement* st) {
		subcode.push_back(st);
	}

	//return the else if clauses and add another else if clause
	std::vector<ElseIfClause*> GetElseIfClauses() { return elseifClauses; }
	void AddElseIfClause(ElseIfClause* eic) { 
		elseifClauses.push_back(eic);
	}

	//get the else clause and set the else clause
	ElseClause* GetElseClause() { return elseClause; }
	void SetElseClause(ElseClause* ec) { elseClause = ec; }

	//override of pure virtual method in Statement class
	std::string GetStatementType() { return "If Statement"; }

	//returns a string representation of this node in the abstract syntax tree
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		
		str += Tab(tab);
		str += "If Statement""\n";
		str += condition->Get_Debug_String(tab) + "\n\n";

		for (auto st : subcode) {
			str += st->Get_Debug_String(tab + 1);
		}

		for (auto el_if_cl : elseifClauses) {
			str += el_if_cl->Get_Debug_String(tab + 1);
		}

		if (elseClause != nullptr) {
			str += elseClause->Get_Debug_String(tab + 1);
		}
		return str;
	}

	//returns a copy of the object and subobjects
	Statement* Duplicate() {
		IfStatement* st = new IfStatement;
		st->condition = this->GetCondition()->Duplicate();
		st->filename = this->filename;
		st->line = this->line;
		st->next = this->next;
		
		for (auto st2 : this->subcode) {
			st->subcode.push_back(st2->Duplicate());
		}

		for (auto el_if_cl : this->elseifClauses) {
			st->elseifClauses.push_back(el_if_cl->Duplicate());
		}

		if (this->GetElseClause() != nullptr) {
			st->SetElseClause(this->elseClause->Duplicate());
		}

		return st;
	}
};




//class to represent a while loop in the code
class WhileLoop :public Statement {
private:
	Expression* condition;
	std::vector<Statement*> subcode;
public:
	//get and set the condition to test in the while loop
	Expression* GetCondition() { return condition; }
	void SetCondition(Expression* c) { condition = c; }

	//get the code inside this while loop 
	std::vector<Statement*> GetStatements() {
		return subcode;
	}

	//add a statement to the code inside this while loop
	void AddStatement(Statement* st) {
		if (!subcode.empty()) {
			subcode.back()->SetNext(st);
		}
		subcode.push_back(st);
	}

	//overrides pure virtual function in Statement class
	std::string GetStatementType() {
		return "While Loop";
	}

	//return string representation of this node in the abstract syntax tree
	std::string Get_Debug_String(int tab = 0){
		std::string str;
		str += Tab(tab);
		str += "While Loop""\n";
		str += condition->Get_Debug_String(tab);
		for (auto st : subcode) {
			str += st->Get_Debug_String(tab + 1);
		}
		return str;
	}

	//returns a copy of the object and subobjects
	Statement* Duplicate() {
		WhileLoop* st = new WhileLoop;
		st->condition = this->condition->Duplicate();
		st->filename = this->filename;
		st->line = this->line;
		for (auto st2 : this->subcode) {
			st->subcode.push_back(st2->Duplicate());
		}
		return st;
	}
};





//e.g For i = 1 To 24
//or For i = 1 To 24 Step 2
class ForLoop :public Statement {
private:
	VariableExpression* variable = nullptr;//variable
	Expression* start;//start
	Expression* end;//end
	Expression* step;//step

	std::vector<Statement*> subcode;

	//used by the interpreter to decide whether to set the variable or not
	bool loop_flag = false;

public:

	//used by the interpreter
	bool Get_loop_flag() { return loop_flag; }
	void Set_loop_flag(bool lf) { loop_flag = lf; }

	//retrieve the code inside the for loop
	std::vector<Statement*> GetStatements() {
		return subcode;
	}

	//add statement to the code inside the for loop
	void AddStatement(Statement* st) {
		if (!subcode.empty()) {
			subcode.back()->SetNext(st);
		}
		subcode.push_back(st);
	}
	
	//overrides pure virtual function inside Statement class
	std::string GetStatementType() {
		return "For Loop";
	}

	//returns a string representation of this node in the abstract syntax
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		str += Tab(tab);
		str += "For Loop""\n";
		
		if (variable != nullptr) {
			str += variable->Get_Debug_String(tab);
		}
		if (start != nullptr) {
			str += start->Get_Debug_String(tab);
		}
		if (end != nullptr) {
			str += end->Get_Debug_String(tab);
		}
		if (step != nullptr) {
			str += step->Get_Debug_String(tab);
		}
		str += "\n\n";

		for (auto st : subcode) {
			str += st->Get_Debug_String(tab + 1);
		}
		return str + "\n\n";
	}

	//get and set the variable part of the for loop
	VariableExpression* GetVariable() {
		return variable;
	}
	void SetVariable(VariableExpression* var) {
		variable = var;
	}

	//get and set the starting value expression of the for loop
	Expression* GetStart() {
		return start;
	}
	void SetStart(Expression* st) {
		start = st;
	}
	
	//get and set the end expression of the for loop
	Expression* GetEnd() {
		return end;
	}
	void SetEnd(Expression* e) {
		end = e;
	}

	//get and set the step expression of the for loop
	Expression* GetStep() {
		return step;
	}
	void SetStep(Expression* st) {
		step = st;
	}

	//returns a copy of the object and subobjects
	Statement* Duplicate() {
		ForLoop* st = new ForLoop;
		st->variable = (VariableExpression*)this->variable->Duplicate();
		st->start = this->start->Duplicate();
		st->end = this->end->Duplicate();
		
		st->line = this->line;
		st->filename = this->filename;
		st->next = this->next;

		if (this->step != nullptr) {
			st->step = this->step->Duplicate();
		}

		for (auto st2 : this->subcode) {
			st->subcode.push_back(st2->Duplicate());
		}

		return st;
	}

};





class Subroutine :public Statement {
private:
	std::string name;
	std::vector<Statement*> subcode;
public:
	//get and set the subroutine name
	std::string GetName() { return name; }
	void SetName(std::string n) { name = n; }

	//add statement to the code inside the subroutine
	void AddStatement(Statement* st) {
		if (!subcode.empty()) {
			subcode.back()->SetNext(st);
		}
		subcode.push_back(st);
	}

	//get the code inside the subroutine
	std::vector<Statement*> GetStatements() {
		return subcode;
	}

	//overrides pure virtual function inside Statement class
	std::string GetStatementType(){
		return "Subroutine";
	}

	//returns a string representation of this code inside 
	std::string Get_Debug_String(int tab = 0) {
		std::string str = "";
		str += Tab(tab);
		str += "Subroutine""\n";
		str += Tab(tab);
		str += name + "\n\n";
		for (auto st : subcode) {
			str += st->Get_Debug_String(tab + 1);
		}
		return str;
	}

	//returns a copy of the object and subobjects
	Statement* Duplicate() {
		Subroutine* st = new Subroutine;
		st->filename = this->filename;
		st->line = this->line;
		st->name = this->name;
		st->next = this->next;

		for (auto st2 : this->subcode) {
			st->subcode.push_back(st2->Duplicate());
		}
		return st;
	}
};





//a dummy statement that is put at the end of a subroutine
//so that the interpreter knows when to return from the subroutine
class EndSub :public Statement {
private:
public:

	std::string GetStatementType() {
		return "EndSub";
	}

	std::string Get_Debug_String(int tab = 0) {
		std::string str = "";
		str += Tab(tab);
		str += "End Of Subrountine""\n";
		return str + "\n";
	}

	//returns a copy of the object and subobjects
	Statement* Duplicate() {
		EndSub* st = new EndSub;
		st->line = this->line;
		st->filename = this->filename;
		st->next = this->next;
		return st;
	}
};




//statement for the break keyword that is used to break out of loops
class BreakStatement :public Statement {
private:
public:
	std::string GetStatementType() {
		return "Break Statement";
	}

	std::string Get_Debug_String(int tab = 0) {
		std::string str = "";
		str += Tab(tab);
		str += "Break Statement""\n";
		return str + "\n";
	}

	//returns a copy of the object and subobjects
	Statement* Duplicate() {
		BreakStatement* st = new BreakStatement;
		st->line = this->line;
		st->filename = this->filename;
		st->next = this->next;
		return st;
	}
};




//statement for the continue keyword that is used to go to the start of loops
class ContinueStatement :public Statement {
private:
public:
	std::string GetStatementType() {
		return "Continue Statement";
	}

	std::string Get_Debug_String(int tab = 0) {
		std::string str = "";
		str += Tab(tab);
		str += "Continue Statement""\n";
		return str + "\n";
	}	

	//returns a copy of the object and subobjects
	Statement* Duplicate() {
		ContinueStatement* st = new ContinueStatement;
		st->line = this->line;
		st->filename = this->filename;
		st->next = this->next;
		return st;
	}
};




//import statement that is used for using multiple files in one program
class ImportStatement :public Statement {
private:
	std::string filepath;
public:
	std::string GetStatementType() {
		return "Import Statement";
	}

	std::string Get_Debug_String(int tab = 0) {
		std::string str = "";
		str += Tab(tab);
		str += "Import Statement""\n";
		str += Tab(tab);
		str += filepath + "\n";
		return str + "\n";
	}

	std::string GetFilePath() {
		return filepath;
	}

	void SetFilePath(std::string str) {
		filepath = str;
	}

	//returns a copy of the object and subobjects
	Statement* Duplicate() {
		ImportStatement* st = new ImportStatement;
		st->line = this->line;
		st->filename = this->filename;
		st->next = this->next;

		st->filepath = this->filepath;
		return st;
	}
};



//blank statement used as filler
class VoidStatement :public Statement {
private:
	//has no members because it represents nothing
public:
	std::string GetStatementType() {
		return "Void Statement";
	}

	std::string Get_Debug_String(int tab = 0) {
		std::string str = "";
		str += Tab(tab);
		str += "Void Statement""\n";
		return str + "\n";
	}

	Statement* Duplicate() {
		return new VoidStatement;
	}
};

#endif