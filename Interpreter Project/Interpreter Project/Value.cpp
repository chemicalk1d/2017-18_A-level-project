#include "Value.hpp"

bool operator==(const Value& lhs, const Value& rhs) {

	switch (lhs.Get_Type()){
	
	case Value::INT:
		switch (rhs.Get_Type())
		{
		case Value::INT:
			return lhs.Get_Int() == rhs.Get_Int();
			break;
		case Value::FLOAT:
			return lhs.Get_Int() == (int64_t)rhs.Get_Float();
			break;
		default:
			return false;
			break;
		}
		break;


	case Value::FLOAT:
		switch (rhs.Get_Type())
		{
		case Value::INT:
			return lhs.Get_Float() == (double)rhs.Get_Int();
			break;
		case Value::FLOAT:
			return lhs.Get_Float() == rhs.Get_Float();
			break;
		default:
			return false;
			break;
		}
		break;


	case Value::BOOLEAN:
		if (lhs.Get_Type() != Value::BOOLEAN) {
			return false;
		}
		else {
			return lhs.Get_Bool() == rhs.Get_Bool();
		}
		break;

	case Value::STRING:
		if (lhs.Get_Type() != Value::STRING) {
			return false;
		}
		else {
			return lhs.Get_String() == rhs.Get_String();
		}
		break;

	case Value::NONE:
		if (lhs.Get_Type() != Value::NONE) {
			return false;
		}
		else {
			return true;
		}
		break;
	default:
		assert(false);
	}
}

bool operator!=(const Value& lhs, const Value& rhs) {
	return !(lhs == rhs);
}

bool operator<(const Value& lhs, const Value& rhs) {
	switch (lhs.Get_Type()) {

	case Value::INT:
		switch (rhs.Get_Type())
		{
		case Value::INT:
			return lhs.Get_Int() < rhs.Get_Int();
			break;
		case Value::FLOAT:
			return lhs.Get_Int() < (int64_t)rhs.Get_Float();
			break;
		default:
			return false;
			break;
		}
		break;


	case Value::FLOAT:
		switch (rhs.Get_Type())
		{
		case Value::INT:
			return lhs.Get_Float() < (double)rhs.Get_Int();
			break;
		case Value::FLOAT:
			return lhs.Get_Float() < rhs.Get_Float();
			break;
		default:
			return false;
			break;
		}
		break;


	case Value::BOOLEAN:
		if (lhs.Get_Type() != Value::BOOLEAN) {
			return false;
		}
		else {
			return lhs.Get_Bool() < rhs.Get_Bool();
		}
		break;

	case Value::STRING:
		if (lhs.Get_Type() != Value::STRING) {
			return false;
		}
		else {
			return lhs.Get_String() < rhs.Get_String();
		}
		break;

	case Value::NONE:
		return false;
		break;
	default:
		assert(false);
	}
}

bool operator<=(const Value& lhs, const Value& rhs) {
	return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Value& lhs, const Value& rhs) {
	return !(lhs <= rhs);
}

bool operator>=(const Value& lhs, const Value& rhs) {
	return !(lhs < rhs);
}