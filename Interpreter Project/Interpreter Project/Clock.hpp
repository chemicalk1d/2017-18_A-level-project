#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "Value.hpp"

#include <vector>

namespace Clock {

	Value Get_Time();
	Value Get_Date();
	Value Get_Year();
	Value Get_Month();
	Value Get_Day();
	Value Get_WeekDay();
	Value Get_Hour();
	Value Get_Minute();
	Value Get_Second();
}

#endif