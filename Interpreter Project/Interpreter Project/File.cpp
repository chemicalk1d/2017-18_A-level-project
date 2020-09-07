#include "File.hpp"

#include <fstream>

std::string last_error = "";

//properties
Value File::Get_LastError() {
	return Value(last_error);
}

//methods
Value File::ReadContents(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - File.ReadContents expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - File.ReadContents expects a string as an argument";
		return Value();
	}

	std::ifstream infile;

	infile.open(args[0].Get_String());

	std::string contents;

	infile.seekg(std::ios_base::end);
	contents.resize(infile.tellg());
	infile.seekg(std::ios_base::beg);
	infile.read(&contents[0], contents.size());
	
	infile.close();

	return Value(contents);
}

Value File::WriteContents(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - File.ReadContents expects 2 arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - File.ReadContents expects file name to be a string";
		return Value();
	}

	std::ofstream outfile;

	outfile.open(args[0].Get_String());

	if (!outfile.is_open()) {
		return Value("FAILED");
	}

	std::string str;

	switch (args[1].Get_Type())
	{
	case Value::INT:
		str = std::to_string(args[1].Get_Int());
		outfile.write(str.c_str(), str.size());
		break;
	case Value::FLOAT:
		str = std::to_string(args[1].Get_Float());
		outfile.write(str.c_str(), str.size());
		break;
	case Value::BOOLEAN:
		str = std::to_string(args[1].Get_Bool());
		outfile.write(str.c_str(), str.size());
		break;
	case Value::STRING:
		outfile.write(args[1].Get_String().c_str(), args[1].Get_String().size());
		break;
	default:
		break;
	}

	outfile.close();
	return Value("SUCCESS");
}
