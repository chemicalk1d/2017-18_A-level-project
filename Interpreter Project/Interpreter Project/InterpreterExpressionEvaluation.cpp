#include "Interpreter.hpp"

#include "Object.hpp"
#include "Methods.hpp"

#include <iostream>

//this function finds out what type of expression expr is and then calls the appropriate function
//with the appropriate type of pointer
Value Interpreter::EvaluateExpression(Expression* expr) {
	if (expr->GetExpressionType() == "Binary Expression") {
		return EvaluateBinaryExpression((BinaryExpression*)expr);
	}
	else if (expr->GetExpressionType() == "Bracket Expression") {
		return EvaluateExpression(((BracketExpression*)expr)->Get_Expression());
	}
	else if (expr->GetExpressionType() == "Unary Expression") {
		return EvaluateUnaryExpression((UnaryExpression*)expr);
	}
	else if (expr->GetExpressionType() == "Function Expression") {
		return EvaluateFunctionCallExpression((FunctionExpression*)expr);
	}
	else if (expr->GetExpressionType() == "Variable Expression") {
		return EvaluateVariableExpression((VariableExpression*)expr);
	}
	else if (expr->GetExpressionType() == "Int Expression") {
		return EvaluateIntExpression((IntExpression*)expr);
	}
	else if (expr->GetExpressionType() == "Boolean Expression") {
		return EvaluateBoolExpression((BooleanExpression*)expr);
	}
	else if (expr->GetExpressionType() == "Decimal Expression") {
		return EvaluateDecimalExpression((DecimalExpression*)expr);
	}
	else if (expr->GetExpressionType() == "String Expression") {
		return EvaluateStringExpression((StringExpression*)expr);
	}
	else if (expr->GetExpressionType() == "Dot Expression") {
		return EvaluateDotExpression((DotExpression*)expr);
	}
	else {
		runtime_error = true;
		error_message += "Program error at line " + std::to_string(expr->GetLineNumber()) + "\n";
		error_message += "Unknown Expression";
	}
}

Value Interpreter::EvaluateBinaryExpression(BinaryExpression* expr) {

	if (expr->Get_Operator() == "+") {
		return BinaryExpression_Addition(expr);
	}

	else if (expr->Get_Operator() == "-") {
		return BinaryExpression_Subtraction(expr);
	}

	else if (expr->Get_Operator() == "*") {
		return BinaryExpression_Multiplication(expr);
	}

	else if (expr->Get_Operator() == "/") {
		return BinaryExpression_Division(expr);
	}

	else if (expr->Get_Operator() == "=" && !inside_evaluation_expression) {
		return BinaryExpression_Assignment(expr);
	}

	else if (expr->Get_Operator() == "=" && inside_evaluation_expression) {
		return BinaryExpression_EqualTo(expr);
	}

	else if (expr->Get_Operator() == "<>") {
		return BinaryExpression_NotEqualTo(expr);
	}

	else if (expr->Get_Operator() == "<") {
		return BinaryExpression_LessThan(expr);
	}

	else if (expr->Get_Operator() == ">") {
		return BinaryExpression_GreaterThan(expr);
	}

	else if (expr->Get_Operator() == "<=") {
		return BinaryExpression_LessThanOrEqualTo(expr);
	}

	else if (expr->Get_Operator() == ">=") {
		return BinaryExpression_GreaterThanOrEqualTo(expr);
	}

	else if (expr->Get_Operator() == "And") {
		return BinaryExpression_And(expr);
	}

	else if (expr->Get_Operator() == "Or") {
		return BinaryExpression_Or(expr);
	}

	else {
		//this should never happen
		assert(false);
	}

}

Value Interpreter::BinaryExpression_Addition(BinaryExpression* expr) {

	//evaluate left hand side
	Value lhs = EvaluateExpression(expr->Get_LHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate right hand side
	Value rhs = EvaluateExpression(expr->Get_RHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate this expression by checking the types of the lhs and the rhs
	//and then performing the correct operation on the correct types
	if (lhs.Get_Type() == Value::INT && rhs.Get_Type() == Value::INT) {
		return Value(lhs.Get_Int() + rhs.Get_Int());
	}
	else if (lhs.Get_Type() == Value::INT && rhs.Get_Type() == Value::FLOAT) {
		return Value((float)lhs.Get_Int() + rhs.Get_Float());
	}
	else if (lhs.Get_Type() == Value::FLOAT && rhs.Get_Type() == Value::INT) {
		return Value(lhs.Get_Float() + rhs.Get_Int());
	}
	else if (lhs.Get_Type() == Value::FLOAT && rhs.Get_Type() == Value::FLOAT) {
		return Value(lhs.Get_Float() + rhs.Get_Float());
	}
	else if (lhs.Get_Type() == Value::STRING && rhs.Get_Type() == Value::STRING) {
		return Value(lhs.Get_String() + rhs.Get_String());
	}
	else if (lhs.Get_Type() == Value::STRING && rhs.Get_Type() == Value::INT) {
		return Value(lhs.Get_String() + std::to_string(rhs.Get_Int()));
	}
	else if (lhs.Get_Type() == Value::STRING && rhs.Get_Type() == Value::FLOAT) {
		return Value(lhs.Get_String() + std::to_string(rhs.Get_Float()));
	}
	else if (lhs.Get_Type() == Value::STRING && rhs.Get_Type() == Value::BOOLEAN) {
		return Value(lhs.Get_String() + std::to_string(rhs.Get_Float()));
	}
	else if (lhs.Get_Type() == Value::INT && rhs.Get_Type() == Value::STRING) {
		return Value(std::to_string(lhs.Get_Int()) + rhs.Get_String());
	}
	else if (lhs.Get_Type() == Value::FLOAT && rhs.Get_Type() == Value::STRING) {
		return Value(std::to_string(lhs.Get_Float()) + rhs.Get_String());
	}
	else if (lhs.Get_Type() == Value::BOOLEAN && rhs.Get_Type() == Value::STRING) {
		return Value(std::to_string(lhs.Get_Bool()) + rhs.Get_String());
	}
	else if (rhs.Get_Type() == Value::NONE) {
		return lhs;
	}
	else if (lhs.Get_Type() == Value::NONE) {
		return rhs;
	}
	else {
		error_message = "Error in program at line " + std::to_string(expr->GetLineNumber()) + "\n";
		error_message = "Type mismatch with the addition operator";
		runtime_error = true;
		return Value();
	}
}

Value Interpreter::BinaryExpression_Subtraction(BinaryExpression* expr) {
	
	//evaluate lhs
	Value lhs = EvaluateExpression(expr->Get_LHS());
	if (runtime_error) {
		return Value();
	}
	
	//evaluate rhs
	Value rhs = EvaluateExpression(expr->Get_RHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate this expression by checking the types of the lhs and the rhs
	//and then performing the correct operation on the correct types
	if (lhs.Get_Type() == Value::INT && rhs.Get_Type() == Value::INT) {
		return Value(lhs.Get_Int() - rhs.Get_Int());
	}
	else if (lhs.Get_Type() == Value::INT && rhs.Get_Type() == Value::FLOAT) {
		return Value((float)lhs.Get_Int() - rhs.Get_Float());
	}
	else if (lhs.Get_Type() == Value::FLOAT && rhs.Get_Type() == Value::INT) {
		return Value(lhs.Get_Float() - rhs.Get_Int());
	}
	else if (lhs.Get_Type() == Value::FLOAT && rhs.Get_Type() == Value::FLOAT) {
		return Value(lhs.Get_Float() - rhs.Get_Float());
	}
	else if (lhs.Get_Type() == Value::NONE && (rhs.Get_Type() == Value::INT || rhs.Get_Type() == Value::FLOAT)) {
		return lhs;
	}
	else if ((lhs.Get_Type() == Value::INT || lhs.Get_Type() == Value::FLOAT) && rhs.Get_Type() == Value::NONE) {
		return rhs;
	}
	else {
		error_message = "Error in program at line " + std::to_string(expr->GetLineNumber()) + "\n";
		error_message = "The subtraction operator can only be used with numeric data";
		runtime_error = true;
		return Value();
	}

}

Value Interpreter::BinaryExpression_Multiplication(BinaryExpression* expr) {
	
	//evaluate lhs
	Value lhs = EvaluateExpression(expr->Get_LHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate rhs
	Value rhs = EvaluateExpression(expr->Get_RHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate this expression by checking the types of the lhs and the rhs
	//and then performing the correct operation on the correct types
	if (lhs.Get_Type() == Value::INT && rhs.Get_Type() == Value::INT) {
		return Value(lhs.Get_Int() * rhs.Get_Int());
	}
	else if (lhs.Get_Type() == Value::INT && rhs.Get_Type() == Value::FLOAT) {
		return Value((float)lhs.Get_Int() * rhs.Get_Float());
	}
	else if (lhs.Get_Type() == Value::FLOAT && rhs.Get_Type() == Value::INT) {
		return Value(lhs.Get_Float() * rhs.Get_Int());
	}
	else if (lhs.Get_Type() == Value::FLOAT && rhs.Get_Type() == Value::FLOAT) {
		return Value(lhs.Get_Float() * rhs.Get_Float());
	}
	else if (lhs.Get_Type() == Value::NONE && (rhs.Get_Type() == Value::INT || rhs.Get_Type() == Value::FLOAT)) {
		if (rhs.Get_Type() == Value::INT) {
			return Value((int64_t)0);
		}
		else {
			return Value(0.0);
		}
	}
	else if ((lhs.Get_Type() == Value::INT || lhs.Get_Type() == Value::FLOAT) && rhs.Get_Type() == Value::NONE) {
		if (rhs.Get_Type() == Value::INT) {
			return Value((int64_t)0);
		}
		else {
			return Value(0.0);
		}
	}
	else {
		error_message = "Error in program at line " + std::to_string(expr->GetLineNumber()) + "\n";
		error_message = "The multiplication operator can only be used with numeric data";
		runtime_error = true;
		return Value();
	}
}

Value Interpreter::BinaryExpression_Division(BinaryExpression* expr) {
	
	//evaluate lhs
	Value lhs = EvaluateExpression(expr->Get_LHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate rhs
	Value rhs = EvaluateExpression(expr->Get_RHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate this expression by checking the types of the lhs and the rhs
	//and then performing the correct operation on the correct types
	if (lhs.Get_Type() == Value::INT && rhs.Get_Type() == Value::INT) {
		return Value(lhs.Get_Int() / rhs.Get_Int());
	}
	else if (lhs.Get_Type() == Value::INT && rhs.Get_Type() == Value::FLOAT) {
		return Value((float)lhs.Get_Int() / rhs.Get_Float());
	}
	else if (lhs.Get_Type() == Value::FLOAT && rhs.Get_Type() == Value::INT) {
		return Value(lhs.Get_Float() / rhs.Get_Int());
	}
	else if (lhs.Get_Type() == Value::FLOAT && rhs.Get_Type() == Value::FLOAT) {
		return Value(lhs.Get_Float() / rhs.Get_Float());
	}
	else if (lhs.Get_Type() == Value::NONE && (rhs.Get_Type() == Value::INT || rhs.Get_Type() == Value::FLOAT)) {
		if (rhs.Get_Type() == Value::INT) {
			return Value((int64_t)0);
		}
		else {
			return Value(0.0);
		}
	}
	else if ((lhs.Get_Type() == Value::INT || lhs.Get_Type() == Value::FLOAT) && rhs.Get_Type() == Value::NONE) {
		if (rhs.Get_Type() == Value::INT) {
			return Value((int64_t)0);
		}
		else {
			return Value(0.0);
		}
	}
	else {
		error_message = "Error in program at line " + std::to_string(expr->GetLineNumber()) + "\n";
		error_message = "The division operator can only be used with numeric data";
		runtime_error = true;
		return Value();
	}
}

Value Interpreter::BinaryExpression_Assignment(BinaryExpression* expr) {
	//assignment


	if (expr->Get_LHS()->GetExpressionType() != "Variable Expression" && expr->Get_LHS()->GetExpressionType() != "Dot Expression") {
		error_message += "Error in program at line " + std::to_string(expr->Get_LHS()->GetLineNumber()) + "\n";
		error_message += "The left hand side of an assignment expression must be a variable";
		runtime_error = true;
		return Value();
	}
	else if (expr->Get_LHS()->GetExpressionType() == "Variable Expression") {
		SetVariable(((VariableExpression*)expr->Get_LHS())->Get_Name(), EvaluateExpression(expr->Get_RHS()));
	}
	else if (expr->Get_LHS()->GetExpressionType() == "Dot Expression") {
		DotExpression* dexpr = (DotExpression*)expr->Get_LHS();
		if (dexpr->Get_RHS()->GetExpressionType() == "Variable Expression") {
			//set object property

			std::string object = dexpr->Get_LHS()->Get_Name();
			std::string prop = ((VariableExpression*)dexpr->Get_RHS())->Get_Name();

			return Set_Property(object, prop, EvaluateExpression(expr->Get_RHS()));
		}
		else {
			runtime_error = true;
			error_message = "Program Error - trying to set a dot expression method which is not allowed";
			return Value();
		}
	}
	else {
		runtime_error = true;
		error_message = "Program Error - to use the assignment operator the left hand side must be either a variable or property of an object which can be set";
		return Value();
	}

}

Value Interpreter::BinaryExpression_EqualTo(BinaryExpression* expr) {
	//equal to comparison

	//evaluate lhs
	Value lhs = EvaluateExpression(expr->Get_LHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate rhs
	Value rhs = EvaluateExpression(expr->Get_RHS());
	if (runtime_error) {
		return Value();
	}

	//compare
	return Value(lhs == rhs);
}

Value Interpreter::BinaryExpression_NotEqualTo(BinaryExpression* expr) {

	//evaluate lhs
	Value lhs = EvaluateExpression(expr->Get_LHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate rhs
	Value rhs = EvaluateExpression(expr->Get_RHS());
	if (runtime_error) {
		return Value();
	}

	//compare
	return Value(lhs != rhs);
}

Value Interpreter::BinaryExpression_LessThan(BinaryExpression* expr) {

	//evaluate lhs
	Value lhs = EvaluateExpression(expr->Get_LHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate rhs
	Value rhs = EvaluateExpression(expr->Get_RHS());
	if (runtime_error) {
		return Value();
	}

	//compare
	return Value(lhs < rhs);
}

Value Interpreter::BinaryExpression_LessThanOrEqualTo(BinaryExpression* expr) {
	
	//evaluate lhs
	Value lhs = EvaluateExpression(expr->Get_LHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate rhs
	Value rhs = EvaluateExpression(expr->Get_RHS());
	if (runtime_error) {
		return Value();
	}

	//compare
	return Value(lhs <= rhs);
}

Value Interpreter::BinaryExpression_GreaterThan(BinaryExpression* expr) {

	//evaluate lhs
	Value lhs = EvaluateExpression(expr->Get_LHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate rhs
	Value rhs = EvaluateExpression(expr->Get_RHS());
	if (runtime_error) {
		return Value();
	}

	//compare
	return Value(lhs > rhs);
}

Value Interpreter::BinaryExpression_GreaterThanOrEqualTo(BinaryExpression* expr) {

	//evaluate lhs
	Value lhs = EvaluateExpression(expr->Get_LHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate rhs
	Value rhs = EvaluateExpression(expr->Get_RHS());
	if (runtime_error) {
		return Value();
	}

	//compare
	return Value(lhs >= rhs);
}

Value Interpreter::BinaryExpression_And(BinaryExpression* expr) {
	
	//evaluate lhs
	Value lhs = EvaluateExpression(expr->Get_LHS());
	if (runtime_error) {
		return Value();
	}

	//evalute rhs
	Value rhs = EvaluateExpression(expr->Get_RHS());
	if (runtime_error) {
		return Value();
	}

	//check that both types are boolean types and set an error if they are not
	if (lhs.Get_Type() != Value::BOOLEAN || rhs.Get_Type() != Value::BOOLEAN) {
		error_message += "Error in program at line " + std::to_string(expr->GetLineNumber()) + "\n";
		error_message += "The \'And\' operator must be used with 2 booleans";
		runtime_error = true;
		return Value();
	}

	//'And' together the booleans
	return Value(lhs.Get_Bool() && rhs.Get_Bool());
}

Value Interpreter::BinaryExpression_Or(BinaryExpression* expr) {
	
	//evaluate lhs
	Value lhs = EvaluateExpression(expr->Get_LHS());
	if (runtime_error) {
		return Value();
	}

	//evaluate rhs
	Value rhs = EvaluateExpression(expr->Get_RHS());
	if (runtime_error) {
		return Value();
	}

	//check that both types are boolean and if not set an error
	if (lhs.Get_Type() != Value::BOOLEAN || rhs.Get_Type() != Value::BOOLEAN) {
		error_message += "Error in program at line " + std::to_string(expr->GetLineNumber()) + "\n";
		error_message += "The \'Or\' operator must be used with 2 booleans";
		runtime_error = true;
		return Value();
	}

	//'or' together the 2 booleans
	return Value(lhs.Get_Bool() || rhs.Get_Bool());
}


//this function is there to evaluate expressions with only one operator and one operand
Value Interpreter::EvaluateUnaryExpression(UnaryExpression* expr) {
	Value v = EvaluateExpression(expr->Get_Expression());
	if (runtime_error) {
		return Value();
	}

	if (expr->Get_Operator() == "-") {

		//check that the type that the value is is an int or a float which we can negate
		//if it is not set an error and return
		if (v.Get_Type() != Value::INT && v.Get_Type() != Value::FLOAT) {
			error_message += "Error in program at line " + std::to_string(expr->GetLineNumber()) + "\n";
			error_message += "The Operator \'Not\' can only be used with integers or floats";
			runtime_error = true;
			return Value();
		}
		//else

		if (v.Get_Type() == Value::INT) {
			//int
			return Value(-v.Get_Int());
		}
		else {
			//float
			return Value(-v.Get_Float());
		}

	}
	else if (expr->Get_Operator() == "Not") {

		
		//check that the type of the value is a boolean which we can not
		//if it is not then set an error and return
		if (v.Get_Type() != Value::BOOLEAN) {
			error_message += "Error in program at line " + std::to_string(expr->GetLineNumber()) + "\n";
			error_message += "The Operator \'Not\' can only be used with booleans";
			runtime_error = true;
			return Value();
		}
		//else

		return Value(!v.Get_Bool());
	}
}

//evaluates a call to a function or a subroutine
Value Interpreter::EvaluateFunctionCallExpression(FunctionExpression* expr) {
	if (expr->Get_Arguments().size() > 0) {
		error_message += "Error in program at line " + std::to_string(expr->GetLineNumber()) + "\n";
		error_message += "Functions not implemented";
		runtime_error = true;
		return Value();
	}

	std::string name = expr->Get_Name();

	auto ptr = subroutines.find(name);
	if (ptr != subroutines.end()) {
		
		//add the statement after the current statement to the stack
		call_stack.push(nextStatement);

		//set the first statement of the subroutine as the next statement
		nextStatement = subroutines[name]->GetStatements()[0];

		//subroutines don't return values
		return Value();
	}
	else {
		error_message += "Error in program at line " + std::to_string(expr->GetLineNumber()) + "\n";
		error_message += "Trying to call a subroutine that does not exist";
		runtime_error = true;
		return Value();
	}
}

//evaluates a variable expression by getting the value of the variable from the map
//if the variable does not exist then one will be automatically created with a null value
Value Interpreter::EvaluateVariableExpression(VariableExpression* expr) {
	//return variable from map, if the variable doesn't exist a new one will be created
	return GetVariable(expr->Get_Name());
}

//returns an integer value of the expression
Value Interpreter::EvaluateIntExpression(IntExpression* expr) {
	return Value((int64_t)expr->Get_Integer());
}

Value Interpreter::EvaluateBoolExpression(BooleanExpression* expr) {
	return Value(expr->GetValue());
}

//returns a decimal value of the expression
Value Interpreter::EvaluateDecimalExpression(DecimalExpression* expr) {
	return Value(expr->Get_Decimal());
}

//returns a string value of the expression
Value Interpreter::EvaluateStringExpression(StringExpression* expr) {
	return Value(expr->Get_String());
}


//evaluates an a.b expression
Value Interpreter::EvaluateDotExpression(DotExpression* expr) {
	if (expr->Get_RHS()->GetExpressionType() == "Variable Expression") {
		return DotExpression_DataProperty(expr);
	}
	else {
		return DotExpression_DataMethod(expr);
	}
}

//e.g. object.property
Value Interpreter::DotExpression_DataProperty(DotExpression* expr) {
	//object/property expression

	std::string objectName = expr->Get_LHS()->Get_Name();
	std::string propertyName = ((VariableExpression*)expr->Get_RHS())->Get_Name();

	Value v = Get_Property(objectName, propertyName);
	return v;
}

//e.g. object.method()
Value Interpreter::DotExpression_DataMethod(DotExpression* expr) {
	//object/method expression

	std::string objectName = expr->Get_LHS()->Get_Name();
	std::string methodName = ((FunctionExpression*)expr->Get_RHS())->Get_Name();

	auto ptr = objects.find(objectName);
	if (ptr == objects.end()) {
		error_message += "Program error at line " + std::to_string(expr->GetLineNumber()) + "\n";
		error_message += "Unknown Object Name";
		runtime_error = true;
		return Value();
	}
	//else

	Object object = objects[objectName];

	if (!object.MethodExists(methodName)) {
		error_message += "Program error at line " + std::to_string(expr->GetLineNumber()) + "\n";
		error_message += "Unknown Method Name";
		runtime_error = true;
		return Value();
	}
	//else

	Method method = object.GetMethod(methodName);

	FunctionExpression* fe = (FunctionExpression*)expr->Get_RHS();

	std::vector<Value> args;

	for (auto arg : fe->Get_Arguments()) {
		args.push_back(EvaluateExpression(arg));
	}

	Value retval = method(args, runtime_error, error_message);

	return retval;
}
