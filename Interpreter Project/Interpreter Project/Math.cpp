#include "Math.hpp"

#include <cmath>
#include <random>

const float PI = 3.141592;

//properties
Value Math::Get_Pi() {
	return Value(PI);
}

//Methods
Value Math::Abs(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.Abs expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(abs(args[0].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value(abs(args[0].Get_Int()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.Abs expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::Ceiling(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.Ceiling expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(ceil(args[0].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value(ceil(args[0].Get_Int()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.Ceiling expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::Floor(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.Abs expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(floor(args[0].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value(floor(args[0].Get_Int()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.Floor expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::NaturalLog(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.NaturalLog expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(log(args[0].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value(log(args[0].Get_Int()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.NaturalLog expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::Log(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.Log expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(log10(args[0].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value(log10(args[0].Get_Int()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.Log expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::Cos(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.Cos expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(cos(args[0].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value(cos(args[0].Get_Int()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.Cos expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::Sin(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.Sin expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(sin(args[0].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value(sin(args[0].Get_Int()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.Sin expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::Tan(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.Tan expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(tan(args[0].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value(tan(args[0].Get_Int()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.Tan expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::ArcSin(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.ArcSin expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(asin(args[0].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value(asin(args[0].Get_Int()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.ArcSin expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::ArcCos(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.ArcCos expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(acos(args[0].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value(acos(args[0].Get_Int()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.ArcCos expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::ArcTan(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.ArcTan expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(atan(args[0].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value(atan(args[0].Get_Int()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.ArcTan expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::GetDegrees(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.GetDegrees expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(args[0].Get_Float() * 180 / PI);
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value((float)(args[0].Get_Int()) * 180 / PI);
	}
	else {
		error = true;
		error_message = "Program Error - Math.GetDegrees expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::GetRadians(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.GetDegrees expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(args[0].Get_Float() * PI / 180);
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value((float)(args[0].Get_Int()) * PI / 180);
	}
	else {
		error = true;
		error_message = "Program Error - Math.GetDegrees expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::SquareRoot(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.GetDegrees expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}
	else if (args[0].Get_Type() == Value::FLOAT) {
		return Value(sqrt(args[0].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return Value(sqrt(args[0].Get_Int()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.GetDegrees expects a numeric argument but was not passed a numeric argument";
		return Value();
	}
}

Value Math::Power(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - Math.Power expects 2 arguments but was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() == Value::INT && args[1].Get_Type() == Value::INT) {
		return Value(pow(args[0].Get_Int(), args[1].Get_Int()));
	}
	else if (args[0].Get_Type() == Value::INT && args[1].Get_Type() == Value::FLOAT) {
		return Value(pow((double)args[0].Get_Int(), args[1].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::FLOAT && args[1].Get_Type() == Value::INT) {
		return Value(pow(args[0].Get_Float(), (double)args[1].Get_Int()));
	}
	else if (args[0].Get_Type() == Value::FLOAT && args[1].Get_Type() == Value::FLOAT) {
		return Value(pow(args[0].Get_Float(), args[1].Get_Float()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.Power expects numeric arguments but was not passed a numeric argument";
		return Value();
	}
}

Value Math::Round(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1){
		error = true;
		error_message = "Program Error - Math.Round expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() == Value::FLOAT) {
		return Value(round(args[0].Get_Float() + 0.5));
	}
	else if (args[0].Get_Type() == Value::INT) {
		return args[0];
	}
}

template<typename T> T MAX(T a1, T a2) {
	if (a1 >= a2) {
		return a1;
	}
	else {
		return a2;
	}
}

Value Math::Max(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - Math.Max expects 2 arguments but was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() == Value::INT && args[1].Get_Type() == Value::INT) {
		return Value(MAX(args[0].Get_Int(), args[1].Get_Int()));
	}
	else if (args[0].Get_Type() == Value::INT && args[1].Get_Type() == Value::FLOAT) {
		return Value(MAX((double)args[0].Get_Int(), args[1].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::FLOAT && args[1].Get_Type() == Value::INT) {
		return Value(MAX(args[0].Get_Float(), (double)args[1].Get_Int()));
	}
	else if (args[0].Get_Type() == Value::FLOAT && args[1].Get_Type() == Value::FLOAT) {
		return Value(MAX(args[0].Get_Float(), args[1].Get_Float()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.Max expects numeric arguments but was not passed a numeric argument";
		return Value();
	}
}

template<typename T> T MIN(T a1, T a2) {
	if (a1 <= a2) {
		return a1;
	}
	else {
		return a2;
	}
}

Value Math::Min(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - Math.Min expects 2 arguments but was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() == Value::INT && args[1].Get_Type() == Value::INT) {
		return Value(MIN(args[0].Get_Int(), args[1].Get_Int()));
	}
	else if (args[0].Get_Type() == Value::INT && args[1].Get_Type() == Value::FLOAT) {
		return Value(MIN((double)args[0].Get_Int(), args[1].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::FLOAT && args[1].Get_Type() == Value::INT) {
		return Value(MIN(args[0].Get_Float(), (double)args[1].Get_Int()));
	}
	else if (args[0].Get_Type() == Value::FLOAT && args[1].Get_Type() == Value::FLOAT) {
		return Value(MIN(args[0].Get_Float(), args[1].Get_Float()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.Min expects numeric arguments but was not passed a numeric argument";
		return Value();
	}
}

Value Math::Remainder(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 2) {
		error = true;
		error_message = "Program Error - Math.Remainder expects 2 arguments but was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() == Value::INT && args[1].Get_Type() == Value::INT) {
		return Value(args[0].Get_Int() % args[1].Get_Int());
	}
	else if (args[0].Get_Type() == Value::INT && args[1].Get_Type() == Value::FLOAT) {
		return Value(fmod((double)args[0].Get_Int(), args[1].Get_Float()));
	}
	else if (args[0].Get_Type() == Value::FLOAT && args[1].Get_Type() == Value::INT) {
		return Value(fmod(args[0].Get_Float(), (double)args[1].Get_Int()));
	}
	else if (args[0].Get_Type() == Value::FLOAT && args[1].Get_Type() == Value::FLOAT) {
		return Value(fmod(args[0].Get_Float(), args[1].Get_Float()));
	}
	else {
		error = true;
		error_message = "Program Error - Math.Remainder expects numeric arguments but was not passed a numeric argument";
		return Value();
	}
}

static std::random_device rd;
std::mt19937 mt(rd());

Value Math::GetRandomNumber(std::vector<Value> args, bool& error, std::string& error_message) {
	if (args.size() != 1) {
		error = true;
		error_message = "Program Error - Math.GetRandomNumber expects 1 argument but was passed " + std::to_string(args.size());
		return Value();
	}

	if (args[0].Get_Type() != Value::INT && args[0].Get_Type() != Value::FLOAT) {
		error = true;
		error_message = "Program Error - Math.GetRandomNumber expects an integer argument but was not passed an integer argument";
		return Value();
	}

	std::uniform_int_distribution<int64_t> uid;
	if (args[0].Get_Type() == Value::INT) {
		uid = std::uniform_int_distribution<int64_t>(1, args[0].Get_Int());
	}
	else {
		uid = std::uniform_int_distribution<int64_t>(1, (int64_t)args[0].Get_Float());
	}
	return uid(mt);
}
