#ifndef MATH_HPP
#define MATH_HPP

#include "Value.hpp"

#include <vector>

namespace Math {
	//properties
	Value Get_Pi();

	//Methods
	Value Abs(std::vector<Value> args, bool& error, std::string& error_message);
	Value Ceiling(std::vector<Value> args, bool& error, std::string& error_message);
	Value Floor(std::vector<Value> args, bool& error, std::string& error_message);
	Value NaturalLog(std::vector<Value> args, bool& error, std::string& error_message);
	Value Log(std::vector<Value> args, bool& error, std::string& error_message);
	Value Cos(std::vector<Value> args, bool& error, std::string& error_message);
	Value Sin(std::vector<Value> args, bool& error, std::string& error_message);
	Value Tan(std::vector<Value> args, bool& error, std::string& error_message);
	Value ArcSin(std::vector<Value> args, bool& error, std::string& error_message);
	Value ArcCos(std::vector<Value> args, bool& error, std::string& error_message);
	Value ArcTan(std::vector<Value> args, bool& error, std::string& error_message);
	Value GetDegrees(std::vector<Value> args, bool& error, std::string& error_message);
	Value GetRadians(std::vector<Value> args, bool& error, std::string& error_message);
	Value SquareRoot(std::vector<Value> args, bool& error, std::string& error_message);
	Value Power(std::vector<Value> args, bool& error, std::string& error_message);
	Value Round(std::vector<Value> args, bool& error, std::string& error_message);
	Value Max(std::vector<Value> args, bool& error, std::string& error_message);
	Value Min(std::vector<Value> args, bool& error, std::string& error_message);
	Value Remainder(std::vector<Value> args, bool& error, std::string& error_message);
	Value GetRandomNumber(std::vector<Value> args, bool& error, std::string& error_message);
}

#endif