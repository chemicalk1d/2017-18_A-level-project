#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <stack>
#include <map>

#include "Value.hpp"
#include "InterpreterUtils.hpp"

//to represent an object in the language
class Object {

public:

	//structure used to represent properties of an object
	struct Property {
		GetProperty getter;
		SetProperty setter;
	};

private:
	
	//maps function pointers of c++ functions to strings of method names
	std::map<std::string, Method> methods;

	//maps properties to strings of property names
	std::map<std::string, Property> properties;

	//name of the object
	std::string name;

public:

	std::string GetName() { return name; };
	void SetName(std::string n) { name = n; }

	void AddMethod(std::string name, Method method) {
		methods[name] = method;
	}

	bool MethodExists(std::string name) {
		auto ptr = methods.find(name);
		return ptr != methods.end();//if ptr == methods.end() that means that the method is not in the map
	}

	Method GetMethod(std::string name) {
		
		//make sure that the the method we are looking for is actually in the map
		//the assertion should never fail
		auto ptr = methods.find(name);
		assert(ptr != methods.end());

		return ptr->second;
	}

	void AddProperty(std::string name, Property p) {
		properties[name] = p;
	}

	bool PropertyExists(std::string name) {
		auto ptr = properties.find(name);
		return ptr != properties.end();
	}

	Property GetProperty(std::string name) {

		//make sure that the the method we are looking for is actually in the map
		//the assertion should never fail
		auto ptr = properties.find(name);
		assert(ptr != properties.end());

		return ptr->second;
	}

};

#endif