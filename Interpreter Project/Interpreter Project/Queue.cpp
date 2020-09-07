#include "Queue.hpp"

#include <map>
#include <queue>

namespace Queue {
	namespace Internal {
		std::map<std::string, std::queue<Value>> queues;
	}
}

Value Queue::PushValue(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - Queue.PushValue expected to be passed 2 arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Queue.PushValue type mismatch with arguments";
		return Value();
	}

	Internal::queues[args[0].Get_String()].push(args[1]);
}

Value Queue::GetCount(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Queue.GetCount expected to be passed 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Queue.PushValue type mismatch with arguments";
		return Value();
	}

	int count = Internal::queues[args[0].Get_String()].size();
	return Value((int64_t)count);
}

Value Queue::PopValue(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Queue.PopValue expected to be passed 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Queue.PushValue type mismatch with arguments";
		return Value();
	}
	Value v = Internal::queues[args[0].Get_String()].front();
	Internal::queues[args[0].Get_String()].pop();
	return v;
}
