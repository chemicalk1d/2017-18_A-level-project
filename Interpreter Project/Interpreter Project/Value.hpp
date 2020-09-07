#ifndef VALUE_HPP
#define VALUE_HPP

#include <cassert>
#include <cstdint>
#include <string>

//tagged union used to represent different types in the language
class Value{

public:
	//used to identify what type this is
	enum type {
		INT,			//the unamed union represents an integer
		FLOAT,			//the unamed union represents a float
		STRING,			//the unamed union represents a string
		BOOLEAN,		//the unamed union represents a boolean
		NONE,			//the unamed union represents nothing, any values are bogus
	};
private:

	union{
		int64_t i;
		double d;
		char* str;
		bool b;
	};

	type Type;

public:

	//copy constructor / assignment operator
	void operator=(const Value& other) {

		//check if we need to deallocate memory
		if (Type == STRING) {
			delete[] str;
		}

		int size;

		switch (other.Type)
		{
		case INT:
			i = other.i;
			Type = INT;
			break;
		case FLOAT:
			d = other.d;
			Type = FLOAT;
			break;
		case STRING:
			size = strlen(other.str);//get size of the string
			str = new char[size + 1];//allocate memory for the string
			memcpy(str, other.str, size + 1);//copy the string across including the null terminator
			Type = STRING;
			break;
		case BOOLEAN:
			b = other.b;
			Type = BOOLEAN;
			break;
		case NONE:
			Type = NONE;
			break;
		default:
			break;
		}
	}
	Value(const Value& other) {

		int size;

		switch (other.Type)
		{
		case INT:
			i = other.i;
			Type = INT;
			break;
		case FLOAT:
			d = other.d;
			Type = FLOAT;
			break;
		case STRING:
			size = strlen(other.str);//get size of the string
			str = new char[size+1];//allocate memory for the string
			memcpy(str, other.str, size + 1);//copy the string across including the null terminator
			Type = STRING;
			break;
		case BOOLEAN:
			b = other.b;
			Type = BOOLEAN;
			break;
		case NONE:
			Type = NONE;
			break;
		default:
			assert(false);
			break;
		}
	}

	//constructors used to instantiate a Value from a different type
	Value(int64_t I) {
		i = I;
		Type = INT;
	}
	Value(double D) {
		d = D;
		Type = FLOAT;
	}
	Value(std::string string) {
		//allocate memory for string
		str = new char[string.size() + 1];

		//copy string from std string class to char* 
		memcpy(str, string.c_str(), string.size());

		//add null terminator onto end
		str[string.size()] = '\0';

		Type = STRING;
	}
	Value(bool B) {
		Type = BOOLEAN;
		b = B;
	}
	Value() {
		Type = NONE;
	}

	//getters to retrieve either the type or an interpretation of the value
	type Get_Type()const{ return Type; }
	int64_t Get_Int()const{ return i; assert(Type == INT); }
	double Get_Float()const{ return d; assert(Type == FLOAT); }
	std::string Get_String()const{ return std::string(str); assert(Type == STRING); }
	bool Get_Bool()const{ return b; assert(Type == BOOLEAN); }

	~Value() {
		if (Type == STRING) {
			delete[] str;
		}
	}
};

//used to compare 2 values
extern bool operator==(const Value& lhs, const Value& rhs);
extern bool operator!=(const Value& lhs, const Value& rhs);
extern bool operator<(const Value& lhs, const Value& rhs);
extern bool operator<=(const Value& lhs, const Value& rhs);
extern bool operator>(const Value& lhs, const Value& rhs);
extern bool operator>=(const Value& lhs, const Value& rhs);

#endif