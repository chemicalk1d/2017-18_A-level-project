#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "Value.hpp"

#include <vector>

namespace Program {
	
	//Methods
	Value Delay(std::vector<Value> args, bool& error, std::string& error_message);
	Value End(std::vector<Value> args, bool& error, std::string& error_message);
}

#endif