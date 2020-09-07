#include "Program.hpp"

#include "Interpreter.hpp"

#include <chrono>
#include <thread>

//Methods
Value Program::Delay(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Program.Delay Expected 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() == Value::INT) {
		std::this_thread::sleep_for(std::chrono::milliseconds(args[0].Get_Int()));
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		std::this_thread::sleep_for(std::chrono::milliseconds((int64_t)args[0].Get_Float()));
		return Value();
	}
	else {
		error = true;
		error_message = "Program Error - Program.Delay Type mismatch with arguments";
		return Value();
	}
}

Value Program::End(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 0) {
		error = true;
		error_message = "Program Error - Program.End Expected no arguments but was passed " + std::to_string(args.size());
		return Value();

	}
	Interpreter::GetInterpreter()->Stop();
	return Value();
}
