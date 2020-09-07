#include "List.hpp"

#include "Value.hpp"

#include <vector>
#include <string>
#include <map>

namespace List {
	namespace Internal {
		std::map<std::string, std::vector<Value>> lists;
	}
}

//arg 0 - list name
//arg 1 - item to append
Value List::Append(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - List.Append expected to be passed 2 arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - List.Append type mismatch with arguments";
		return Value();
	}

	Internal::lists[args[0].Get_String()].push_back(args[1]);
}

//arg 0 - list name
//arg 1 - item to insert
//arg 2 - where to insert the item
Value List::Insert(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 3) {
		error = true;
		error_message = "Program Error - List.Insert expected to be passed 3 arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING || args[2].Get_Type() != Value::INT) {
		error = true;
		error_message = "Program Error - List.Insert type mismatch with arguments";
		return Value();
	}

	int size_of_list = Internal::lists[args[0].Get_String()].size();

	int index = args[2].Get_Int();

	if (index > size_of_list) {
		//just append it to the end of the list
		Internal::lists[args[0].Get_String()].push_back(args[1]);
	}
	else if(index < 0) {
		//error
		error = true;
		error_message = "Program Error - List.Insert with invalid index";
		return Value();
	}
	else {
		//insert it into the vector
		Internal::lists[args[0].Get_String()].insert(Internal::lists[args[0].Get_String()].begin() + args[2].Get_Int(), args[1]);
	}

	return Value();
}

//arg 0 - list name
//arg 1 - item to remove
Value List::Remove(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - List.Remove expected to be passed 2 arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - List.Remove type mismatch with arguments";
		return Value();
	}

	//start iterating through the list from the front
	for (std::vector<Value>::iterator it = Internal::lists[args[0].Get_String()].begin(); it != Internal::lists[args[0].Get_String()].end(); ++it) {
		if (*it == args[1]) {
			Internal::lists[args[0].Get_String()].erase(it);
			break;
		}
	}

	return Value();
}

//arg 0 - list name
//arg 1 - list index
Value List::Delete(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - List.Delete expected to be passed 2 arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING || args[1].Get_Type() != Value::INT) {
		error = true;
		error_message = "Program Error - List.Delete type mismatch with arguments";
		return Value();
	}

	int size_of_list = Internal::lists[args[0].Get_String()].size();

	int index = args[2].Get_Int();

	if (index > size_of_list) {
		//just remove the last item of the list
		Internal::lists[args[0].Get_String()].pop_back();
	}
	else if (index < 0) {
		//error
		error = true;
		error_message = "Program Error - List.Delete with invalid index";
		return Value();
	}
	else {
		//remove the item with the given index
		Internal::lists[args[0].Get_String()].erase(Internal::lists[args[0].Get_String()].begin() + args[1].Get_Int());
	}

	return Value();
}

//arg 0 - list name
//arg 1 - list index
Value List::Get(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - List.Get expected to be passed 2 arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING || args[1].Get_Type() != Value::INT) {
		error = true;
		error_message = "Program Error - List.Get type mismatch with arguments";
		return Value();
	}

	int size_of_list = Internal::lists[args[0].Get_String()].size();

	int index = args[1].Get_Int();

	Value v;

	if (index > size_of_list || index < 0) {
		//error
		error = true;
		error_message = "Program Error - List.Get with invalid index";
		return Value();
	}
	else {
		//get the item with the given index
		v = Internal::lists[args[0].Get_String()][args[1].Get_Int()];
	}

	return v;
}

//arg 0 - list name
Value List::Size(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - List.Size expected to be passed 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - List.Size type mismatch with arguments";
		return Value();
	}

	return Value((int64_t)Internal::lists[args[0].Get_String()].size());
}

Value List::Clear(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1){
		error = true;
		error_message = "Program Error - List.Clear expected to be passed 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - List.Clear type mismatch with arguments";
		return Value();
	}

	Internal::lists[args[0].Get_String()].clear();

	return Value();
}