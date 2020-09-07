#include "Text.hpp"

#include <string>
#include <algorithm>

Value Text::Append(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - Text.Append expects 2 arguments but was given " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() == Value::INT && args[1].Get_Type() == Value::INT) {
		return Value(std::to_string(args[0].Get_Int()) + std::to_string(args[1].Get_Int()));
	}
	else if (args[0].Get_Type() == Value::INT && args[1].Get_Type() == Value::FLOAT) {
		return Value(std::to_string(args[0].Get_Int()) + std::to_string(args[1].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT && args[1].Get_Type() == Value::STRING) {
		return Value(std::to_string(args[0].Get_Int()) + args[1].Get_String());
	}
	else if (args[0].Get_Type() == Value::INT && args[1].Get_Type() == Value::BOOLEAN) {
		return Value(std::to_string(args[0].Get_Int()) + std::to_string(args[1].Get_Bool()));
	}
	else if (args[0].Get_Type() == Value::FLOAT && args[1].Get_Type() == Value::INT) {
		return Value(std::to_string(args[0].Get_Float()) + std::to_string(args[1].Get_Int()));
	}
	else if (args[0].Get_Type() == Value::FLOAT && args[1].Get_Type() == Value::FLOAT) {
		return Value(std::to_string(args[0].Get_Float()) + std::to_string(args[1].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::FLOAT && args[1].Get_Type() == Value::STRING) {
		return Value(std::to_string(args[0].Get_Float()) + args[1].Get_String());
	}
	else if (args[0].Get_Type() == Value::FLOAT && args[1].Get_Type() == Value::BOOLEAN) {
		return Value(std::to_string(args[0].Get_Int()) + std::to_string(args[1].Get_Bool()));
	}
	else if (args[0].Get_Type() == Value::STRING && args[1].Get_Type() == Value::INT) {
		return Value(args[0].Get_String() + std::to_string(args[1].Get_Int()));
	}
	else if (args[0].Get_Type() == Value::STRING && args[1].Get_Type() == Value::FLOAT) {
		return Value(args[0].Get_String() + std::to_string(args[1].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::STRING && args[1].Get_Type() == Value::STRING) {
		return Value(args[0].Get_String() + args[1].Get_String());
	}
	else if (args[0].Get_Type() == Value::STRING && args[1].Get_Type() == Value::BOOLEAN) {
		return Value(args[0].Get_String() + std::to_string(args[1].Get_Bool()));
	}
	else if (args[0].Get_Type() == Value::BOOLEAN && args[1].Get_Type() == Value::INT) {
		return Value(std::to_string(args[0].Get_Bool()) + std::to_string(args[1].Get_Int()));
	}
	else if (args[0].Get_Type() == Value::BOOLEAN && args[1].Get_Type() == Value::FLOAT) {
		return Value(std::to_string(args[0].Get_Bool()) + std::to_string(args[1].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::BOOLEAN && args[1].Get_Type() == Value::STRING) {
		return Value(std::to_string(args[0].Get_Bool()) + args[1].Get_String());
	}
	else if (args[0].Get_Type() == Value::BOOLEAN && args[1].Get_Type() == Value::BOOLEAN) {
		return Value(std::to_string(args[0].Get_Bool()) + std::to_string(args[1].Get_Bool()));
	}
	else if (args[0].Get_Type() == Value::NONE) {
		return args[0];
	}
	else if (args[1].Get_Type() == Value::NONE) {
		return args[1];
	}
}

Value Text::GetLength(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Text.GetLength expects 1 argument yet was given " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() == Value::INT) {
		return Value((int64_t)std::to_string(args[0].Get_Int()).size());
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value((int64_t)std::to_string(args[0].Get_Float()).size());
	}
	else if (args[0].Get_Type() == Value::BOOLEAN) {
		return Value((int64_t)std::to_string(args[0].Get_Bool()).size());
	}
	else if (args[0].Get_Type() == Value::STRING) {
		return Value((int64_t)args[0].Get_String().size());
	}
	else {
		return Value((int64_t)0);
	}
}

Value Text::IsSubText(std::vector<Value> args, bool& error, std::string& error_message) {

	if (args.size() != 3) {
		error = true;
		error_message = "Program Error - Text.IsSubText Expects 3 Arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	//else

	//arg1 string to search
	//arg2 start search from
	//arg3 subtext search for

	if (args[0].Get_Type() != Value::STRING || args[1].Get_Type() != Value::INT || args[2].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Text.IsSubText Type mismatch with arguments";
		return Value();
	}
	//else
	
	std::string text1 = args[0].Get_String();
	std::string text2 = args[2].Get_String();
	
	int64_t pos = text1.find(text2, args[1].Get_Int()-1);
	return Value(pos != std::string::npos);
}

Value Text::EndsWith(std::vector<Value> args, bool& error, std::string& error_message) {
	//arg1 text 1
	//arg2 subtext

	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - Text.EndsWith Expects 2 Arguments but was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() != Value::STRING || args[1].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Text.EndsWith Type mismatch with arguments";
		return Value();
	}

	if (args[1].Get_String().size() > args[0].Get_String().size()) {
		return Value(false);
	}

	//TODO test this for loop
	for (int i = args[1].Get_String().size()-1; i > 0; i--) {
		if (args[1].Get_String()[i] != args[0].Get_String()[i]) {
			return Value(false);
		}
	}
	return Value(true);
}

Value Text::StartsWith(std::vector<Value> args, bool& error, std::string& error_message) {
	//arg1 text 1
	//arg2 subtext

	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - Text.StartsWith Expects 2 Arguments but was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() != Value::STRING || args[1].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Text.StartsWith Type mismatch with arguments";
		return Value();
	}

	if (args[1].Get_String().size() > args[0].Get_String().size()) {
		return Value(false);
	}

	for (int i = 0; i < args[1].Get_String().size(); i++) {
		if (args[1].Get_String()[i] != args[0].Get_String()[i]) {
			return Value(false);
		}
	}
	return Value(true);
}

Value Text::GetSubText(std::vector<Value> args, bool& error, std::string& error_message) {
	//arg1 text - string
	//arg2 start - int
	//arg3 length - int

	if (args.size() != 3) {
		error = true;
		error_message = "Program Error - Text.GetSubText Expects 3 arguments yet it was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() != Value::STRING || args[1].Get_Type() != Value::INT || args[2].Get_Type() != Value::INT) {
		error = true;
		error_message = "Program Error - Text.IsSubText Type mismatch with arguments";
		return Value();
	}
	//else

	std::string str = args[0].Get_String();

	//TODO off by one error
	return Value(str.substr(args[1].Get_Int()-1, args[2].Get_Int()));
}

Value Text::GetSubTextToEnd(std::vector<Value> args, bool& error, std::string& error_message) {
	//arg1 text - string
	//arg2 start - int

	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - Text.GetSubText Expects 3 arguments yet it was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() != Value::STRING || args[1].Get_Type() != Value::INT) {
		error = true;
		error_message = "Program Error - Text.IsSubText Type mismatch with arguments";
		return Value();
	}
	//else

	std::string str = args[0].Get_String();

	//TODO check that this line is correct
	return Value(str.substr(args[1].Get_Int(), str.size() - args[1].Get_Int()));
}

Value Text::GetIndexOf(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 3) {
		error = true;
		error_message = "Program Error - Text.IsSubText Expects 3 Arguments but was passed " + std::to_string(args.size());
		return Value();
	}
	//else

	//arg1 string to search
	//arg2 start search from
	//arg3 subtext search for

	if (args[0].Get_Type() != Value::STRING || args[1].Get_Type() != Value::INT || args[2].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Text.IsSubText Type mismatch with arguments";
		return Value();
	}
	//else

	std::string text1 = args[0].Get_String();
	std::string text2 = args[2].Get_String();

	int64_t pos = text1.find(text2, args[1].Get_Int()-1);
	return Value(pos);
}

Value Text::ConvertToLowerCase(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Text.ConvertToLowerCase Expects one argument but was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() == Value::INT) {
		std::string str = std::to_string(args[0].Get_Int());
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		return Value(str);
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		std::string str = std::to_string(args[0].Get_Float());
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		return Value(str);
	}
	else if (args[0].Get_Type() == Value::BOOLEAN) {
		std::string str = std::to_string(args[0].Get_Bool());
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		return Value(str);
	}
	else if (args[0].Get_Type() == Value::STRING) {
		std::string str = args[0].Get_String();
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		return Value(str);
	}
	else {
		return Value();
	}
}

Value Text::ConvertToUpperCase(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Text.ConvertToLowerCase Expects one argument but was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() == Value::INT) {
		std::string str = std::to_string(args[0].Get_Int());
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return Value(str);
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		std::string str = std::to_string(args[0].Get_Float());
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return Value(str);
	}
	else if (args[0].Get_Type() == Value::BOOLEAN) {
		std::string str = std::to_string(args[0].Get_Bool());
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return Value(str);
	}
	else if (args[0].Get_Type() == Value::STRING) {
		std::string str = args[0].Get_String();
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return Value(str);
	}
	else {
		return Value();
	}
}

Value Text::GetCharacter(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Text.GetCharacter expects 1 argument yet it was passed " + std::to_string(args.size());
		return Value();
	}
	
	if (args[0].Get_Type() != Value::INT) {
		error = true;
		error_message = "Program Error - Text.GetCharacter type mismatch with argument";
		return Value();
	}

	//string of length 1
	std::string str;
	str.resize(1);

	str[0] = args[0].Get_Int();
	return str;
}

Value Text::GetCharacterCode(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Text.GetCharacter expects 1 argument yet it was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() != Value::STRING) {
		error = true;
		error_message = "Program Error - Text.GetCharacter type mismatch with argument";
		return Value();
	}
	return Value((int64_t)args[0].Get_String()[0]);
}

