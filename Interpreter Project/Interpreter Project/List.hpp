#ifndef LIST_HPP
#define LIST_HPP

#include <string>
#include <vector>

#include "Value.hpp"

//append - add to end
//insert - insert into list
//remove - remove first value equal to that value
//delete - remove a particular index
//get - get the value at that index
//size - get size of the list

namespace List {
	//properties

	//Methods
	Value Append(std::vector<Value> args, bool& error, std::string& error_message);
	Value Insert(std::vector<Value> args, bool& error, std::string& error_message);
	Value Remove(std::vector<Value> args, bool& error, std::string& error_message);
	Value Delete(std::vector<Value> args, bool& error, std::string& error_message);
	Value Get(std::vector<Value> args, bool& error, std::string& error_message);
	Value Size(std::vector<Value> args, bool& error, std::string& error_message);
	Value Clear(std::vector<Value> args, bool& error, std::string& error_message);
}

#endif