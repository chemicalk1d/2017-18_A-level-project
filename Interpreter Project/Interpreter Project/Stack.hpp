#ifndef STACK_HPP
#define STACK_HPP

#include "Value.hpp"

#include <vector>
#include <string>
#include <map>
#include <stack>

namespace Stack {
	//properties

	//Methods
	Value PushValue(std::vector<Value> args, bool& error, std::string& error_message);
	Value GetCount(std::vector<Value> args, bool& error, std::string& error_message);
	Value PopValue(std::vector<Value> args, bool& error, std::string& error_message);

}

#endif