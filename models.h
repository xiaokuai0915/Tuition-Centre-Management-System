#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <vector>
//base struct for the system to create subject
struct Course {
	int id = 0;
	std::string Name = "";
	double price = 0.0;
};

//base struct for the system to create user
struct User {
	std::string username;
	std::string password;
	std::vector<Course> mypackage;
	int level = 0;
	int code = 0;
	int adminCode = 123456; //code to register as a admin
};

#endif