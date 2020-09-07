#ifndef INTERPRETERUTILS_HPP
#define INTERPRETERUTILS_HPP

#include <vector>

#include "Value.hpp"

typedef Value(*Method)(std::vector<Value> args, bool& error, std::string& errmsg);
typedef Value(*GetProperty)();
typedef Value(*SetProperty)(Value arg, bool& error, std::string& errmsg);

#endif