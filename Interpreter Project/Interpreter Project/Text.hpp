#ifndef TEXT_HPP
#define TEXT_HPP

#include "Value.hpp"

#include <vector>

namespace Text {
	//properties

	//Methods
	Value Append(std::vector<Value> args, bool& error, std::string& error_message);
	Value GetLength(std::vector<Value> args, bool& error, std::string& error_message);
	Value IsSubText(std::vector<Value> args, bool& error, std::string& error_message);
	Value EndsWith(std::vector<Value> args, bool& error, std::string& error_message);
	Value StartsWith(std::vector<Value> args, bool& error, std::string& error_message);
	Value GetSubText(std::vector<Value> args, bool& error, std::string& error_message);
	Value GetSubTextToEnd(std::vector<Value> args, bool& error, std::string& error_message);
	Value GetIndexOf(std::vector<Value> args, bool& error, std::string& error_message);
	Value ConvertToLowerCase(std::vector<Value> args, bool& error, std::string& error_message);
	Value ConvertToUpperCase(std::vector<Value> args, bool& error, std::string& error_message);
	Value GetCharacter(std::vector<Value> args, bool& error, std::string& error_message);
	Value GetCharacterCode(std::vector<Value> args, bool& error, std::string& error_message);

}

#endif