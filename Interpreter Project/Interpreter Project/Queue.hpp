#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <string>
#include <vector>

#include "Value.hpp"

namespace Queue {

	//Methods
	Value PushValue(std::vector<Value> args, bool& error, std::string& error_message);
	Value GetCount(std::vector<Value> args, bool& error, std::string& error_message);
	Value PopValue(std::vector<Value> args, bool& error, std::string& error_message);

}

#endif