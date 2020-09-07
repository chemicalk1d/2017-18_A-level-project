#include "Clock.hpp"

#include <ctime>
#include <chrono>

Value Clock::Get_Time() {
	time_t t = time(0);
	struct tm * now = localtime(&t);
	return Value(std::to_string(now->tm_hour) + "::" + std::to_string(now->tm_min) + "::" + std::to_string(now->tm_sec));
}

Value Clock::Get_Date() {
	time_t t = time(0);
	struct tm * now = localtime(&t);
	return Value(std::to_string(now->tm_mday) + "/" + std::to_string(now->tm_mon+1) + "/" + std::to_string(now->tm_year+1900));
}

Value Clock::Get_Year() {
	time_t t = time(0);
	struct tm * now = localtime(&t);
	return Value((int64_t)now->tm_year+1900);
}

Value Clock::Get_Month() {
	time_t t = time(0);
	struct tm * now = localtime(&t);
	return Value((int64_t)now->tm_mon+1);
}

Value Clock::Get_Day() {
	time_t t = time(0);
	struct tm * now = localtime(&t);
	return Value((int64_t)now->tm_mday);
}

Value Clock::Get_WeekDay() {
	time_t t = time(0);
	struct tm * now = localtime(&t);
	return Value((int64_t)now->tm_wday);
}

Value Clock::Get_Hour() {
	time_t t = time(0);
	struct tm * now = localtime(&t);
	return Value((int64_t)now->tm_hour);
}

Value Clock::Get_Minute() {
	time_t t = time(0);
	struct tm * now = localtime(&t);
	return Value((int64_t)now->tm_min);
}

Value Clock::Get_Second() {
	time_t t = time(0);
	struct tm * now = localtime(&t);
	return Value((int64_t)now->tm_sec);
}
