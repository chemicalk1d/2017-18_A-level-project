#ifndef FILE_HPP
#define FILE_HPP

#include "Value.hpp"

#include <vector>

namespace File {

	//properties
	Value Get_LastError();

	//methods
	Value ReadContents(std::vector<Value> args, bool& error, std::string& error_message);
	Value WriteContents(std::vector<Value> args, bool& error, std::string& error_message);
	
}

#endif