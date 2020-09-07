#include "Stack.hpp"

namespace Stack {
	namespace Internal {
		std::map<std::string, std::stack<Value>> stacks;
	}
}

Value Stack::PushValue(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - Stack.PushValue expected to be passed 2 arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Stack.PushValue type mismatch with arguments";
		return Value();
	}

	Internal::stacks[args[0].Get_String()].push(args[1]);
}

Value Stack::GetCount(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Stack.GetCount expected to be passed 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Stack.PushValue type mismatch with arguments";
		return Value();
	}

	int count = Internal::stacks[args[0].Get_String()].size();
	return Value((int64_t)count);
}

Value Stack::PopValue(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Stack.PopValue expected to be passed 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Stack.PushValue type mismatch with arguments";
		return Value();
	}
	Value v = Internal::stacks[args[0].Get_String()].top();
	Internal::stacks[args[0].Get_String()].pop();
	return v;
}
