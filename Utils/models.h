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

extern std::vector<Course> allCourse; //ask for space to link not real declare

//base struct for the system to create user
struct User {
	std::string username;
	std::string password;
	std::vector<Course> mypackage;
	int role = 0;
};

#endif