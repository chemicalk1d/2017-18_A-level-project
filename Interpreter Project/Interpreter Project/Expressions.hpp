#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include <string>
#include <vector>

//used in the debugging string to add 4 spaces to spread the
//debugging notes out so they can be understood better
inline std::string Tab(int tab) {
	std::string str = "";
	for (int x = 0; x < tab; x++) {
		str += "    ";
	}
	return str;
}

//abstract expression class
class Expression {
protected:
	int line = -1;

	std::string filename = "";
public:

	//getter and setter for the line number
	int GetLineNumber() { return line; }
	void SetLineNumber(int line_number) { line = line_number; }

	//getter and setter for the line number
	std::string GetFileName() { return filename; }
	void SetFileName(std::string fn) { filename = fn; }

	//pure virtual function that is used to distinguish between different expression types
	//when passing around Expression* variables
	virtual std::string GetExpressionType() = 0;

	//destructor
	virtual ~Expression() {}

	//used in debugging
	virtual std::string Get_Debug_String(int tab = 0) = 0;

	//returns a duplicate copy of the object
	virtual Expression* Duplicate() = 0;
};

//simple wrapper over the expression to represent brackets
//the way this is parsed means that the rules of BIDMAS are followed
class BracketExpression :public Expression {
private:
	//the expression inside the brackets
	Expression* expr = nullptr;
public:

	//get and set the sub expression
	Expression* Get_Expression() { return expr; }
	void Set_Expression(Expression* e) { expr = e; }

	//implementation of the pure virtual function in the expression class
	std::string GetExpressionType() { return "Bracket Expression"; }

	//debugging function to output the string that represents this node in the tree
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		str += Tab(tab);
		str += "Bracket Expression""\n";
		str += expr->Get_Debug_String(tab+1);
		return str;
	}

	//when we deallocate this object make sure that if there is a sub expression that we deallocate that
	~BracketExpression() {
		if (expr) {
			delete expr;
		}
	}

	//return a copy of this object and all sub objects
	Expression* Duplicate() {
		BracketExpression* be = new BracketExpression(*this);
		be->expr = this->expr->Duplicate();
		return be;
	}
};


//class to represent a mathmatical operation such as a + b
class BinaryExpression :public Expression{
private:
	Expression* lhs = nullptr;//left hand side of the operator
	Expression* rhs = nullptr;//right hand side of the operator
	std::string op = "";//operator
public:
	//get and set the lhs sub expression of this binary expression
	Expression* Get_LHS() { return lhs; }
	void Set_LHS(Expression* LHS) { lhs = LHS; }

	//get and set the rhs sub expression of the binary expression
	Expression* Get_RHS() { return rhs; }
	void Set_RHS(Expression* RHS) { rhs = RHS; }

	//get and set the operator of this binary expression
	std::string Get_Operator() { return op; }
	void Set_Operator(std::string Operator) { op = Operator; }

	//function that overrides the pure virtual function in the expression class
	std::string GetExpressionType(){ return "Binary Expression"; }

	//destructor
	~BinaryExpression() {
		//check if there is a lhs expression - if so delete it
		if (lhs != nullptr) {
			delete lhs;
		}
		//check if there is a rhs expression - if so delete it
		if (rhs != nullptr) {
			delete rhs;
		}
	}

	//function used to output a string that represents this node and all sub nodes in the AST
	std::string Get_Debug_String(int tab = 0) {
		std::string str = "";
		str += Tab(tab);
		str += "Binary Expression""\n";
		str += Tab(tab);
		str += "Operator: " + op + "\n";
		str += lhs->Get_Debug_String(tab+1);
		str += rhs->Get_Debug_String(tab+1);
		return str;
	}

	//function to duplicate this node and all subnodes of the tree
	Expression* Duplicate() {
		BinaryExpression* be = new BinaryExpression(*this);
		be->lhs = this->lhs->Duplicate();
		be->rhs = this->rhs->Duplicate();
		return be;
	}
};

//Expression to represent operations such as -a
class UnaryExpression :public Expression {
private:
	Expression* expr = nullptr;//sub expression
	std::string op = "";//operator
public:
	//get and set the sub expression
	Expression* Get_Expression() { return expr; }
	void Set_Expression(Expression* Expr) { expr = Expr; }

	//get and set the operator
	std::string Get_Operator() { return op; }
	void Set_Operator(std::string Operator) { op = Operator; }

	//override of the pure virtual function in the expression class
	std::string GetExpressionType(){ return "Unary Expression"; }

	//destructor
	~UnaryExpression() {
		//check if there is a sub expression - if so delete it
		if (expr != nullptr) {
			delete expr;
		}
	}

	//function that return a string that represents this node in the abstract syntax tree
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		str += Tab(tab);
		str += "Unary Expression""\n";
		str += Tab(tab);
		str += "Operator: " + op + "\n";
		str += expr->Get_Debug_String(tab+1);
		return str;
	}

	//returns a copy of this node and all sub nodes
	Expression* Duplicate() {
		UnaryExpression* ue = new UnaryExpression(*this);
		ue->expr = this->expr->Duplicate();
		return ue;
	}
};

//Expression to represent string value
class StringExpression :public Expression {
private:
	std::string str = "";
public:
	//get and set the string value
	std::string Get_String() { return str; }
	void Set_String(std::string string) { str = string; }

	//override of pure virtual function in expression class
	std::string GetExpressionType(){ return "String Expression"; }

	//function that returns a string that represents this node in the tree
	std::string Get_Debug_String(int tab = 0) {
		std::string Str;
		Str += Tab(tab);
		Str += "String Expression""\n";
		Str += Tab(tab);
		Str += "STR: \"" + str + "\"\n";
		return Str;
	}

	//returns a copy of this expression
	Expression* Duplicate() {
		return new StringExpression(*this);
	}
};

//Expression to represent integer value
class IntExpression :public Expression {
private:
	int integer = 0;
public:
	//get and set integer values
	int Get_Integer() { return integer; }
	void Set_Integer(int Integer) { integer = Integer; }

	//overrides pure virtual function in the Expression class
	std::string GetExpressionType()override { return "Int Expression"; }

	//returns a string that represents this node in the abstract syntax tree
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		str += Tab(tab);
		str += "Int Expression""\n";
		str += Tab(tab);
		str += "Int: " + std::to_string(integer) + "\n";
		return str;
	}

	//returns a copy of this node
	Expression* Duplicate() {
		return new IntExpression(*this);
	}
};

//experssion to represent decimal value
class DecimalExpression :public Expression {
private:
	double decimal = 0.0;
public:
	//get and set decimal value
	double Get_Decimal() { return decimal; }
	void Set_Decimal(double Decimal) { decimal = Decimal; }

	//override of the pure virtual function in the Expression class
	std::string GetExpressionType(){ return "Decimal Expression"; }

	//returns a string that represents this node in the abstract syntax tree
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		str += Tab(tab);
		str += "Decimal Expression""\n";
		str += Tab(tab);
		str += "Decimal: " + std::to_string(decimal) + "\n";
		return str;
	}

	//returns a carbon copy of this node
	Expression* Duplicate() {
		return new DecimalExpression(*this);
	}

};

//expression to represent variable
class VariableExpression :public Expression {
private:
	std::string variableName = "";
public:
	//get and set the variable name
	std::string Get_Name() { return variableName; }
	void Set_Name(std::string name) { variableName = name; }

	//override of the pure virtual function in the expression class
	std::string GetExpressionType(){ return "Variable Expression"; }

	//returns a string that represents this node in the abstract synrax tree
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		str += Tab(tab);
		str += "Variable Expression""\n";
		str += Tab(tab);
		str += "Variable: " + variableName + "\n";
		return str;
	}

	//returns a copy of this node
	Expression* Duplicate() {
		return new VariableExpression(*this);
	}
};

//expression to represent function call
class FunctionExpression :public Expression {
private:
	std::string functionName = "";
	std::vector<Expression*> args = {};
public:
	//get and set the function name
	std::string Get_Name() { return functionName; }
	void Set_Name(std::string name) { functionName = name; }

	//get and set the list of arguments
	std::vector<Expression*> Get_Arguments() { return args; }
	void Set_Arguments(std::vector<Expression*> Args) { args = Args; }

	//override of pure virtual function in the expression class
	std::string GetExpressionType(){ return "Function Expression"; }

	//destructor
	~FunctionExpression() {
		//go through each argument and check if it is valid, if it is then delete it and free the memory
		for (auto arg : args) {
			if (arg != nullptr) {
				delete arg;
			}
		}
	}

	//returns a string representation of this node in the abstract syntax tree
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		str += Tab(tab);
		str += "Function Expression""\n";
		str += Tab(tab);
		str += "Function Name: " + functionName + "\n";
		for (auto arg : args) {
			str += arg->Get_Debug_String(tab + 1);
		}
		return str;
	}

	//returns a copy of this node and all sub nodes
	Expression* Duplicate() {
		FunctionExpression* fe = new FunctionExpression(*this);
		fe->args.clear();
		for (auto arg : this->args) {
			fe->args.push_back(arg->Duplicate());
		}
		return fe;
	}
};

class BooleanExpression :public Expression {
private:
	bool booleanValue;
public:
	//get and set the boolean value
	bool GetValue() { return booleanValue; }
	void SetValue(bool b) { booleanValue = b; }

	//returns a string representation of the node in the abstract syntax tree
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		str += Tab(tab);
		str += "Boolean Expression""\n";
		str += Tab(tab);
		if (booleanValue) {
			str += "true";
		}
		else {
			str += "false";
		}
		return str + "\n";
	}

	//override of pure virtual function in the Expression class
	std::string GetExpressionType() {
		return "Boolean Expression";
	}

	//return a cop of this node
	Expression* Duplicate() {
		return new BooleanExpression(*this);
	}
};

//an expression to represent an "object.property" or an "object.method()" expression
class DotExpression :public Expression {
private:
	VariableExpression* lhs;
	Expression* rhs;
public:
	//get and set the lhs expression
	VariableExpression* Get_LHS() { return lhs; }
	void Set_LHS(VariableExpression* LHS) { lhs = LHS; }

	//get and set the rhs expression
	Expression* Get_RHS() { return rhs; }
	void Set_RHS(Expression* RHS) { rhs = RHS; }

	//override of pure virtual function in the expression class
	std::string GetExpressionType() {
		return "Dot Expression";
	}

	//returns a string representation of the node in the tree
	std::string Get_Debug_String(int tab = 0) {
		std::string str;
		str += Tab(tab);
		str += "Dot Expression""\n";
		str += lhs->Get_Debug_String(tab + 1);
		str += rhs->Get_Debug_String(tab + 1);
		return str;
	}

	//returns a copy of this node and all sub nodes
	Expression* Duplicate() {
		DotExpression* de = new DotExpression(*this);
		de->lhs = (VariableExpression*)this->lhs->Duplicate();
		de->rhs = this->rhs->Duplicate();
		return de;
	}
};


#endif