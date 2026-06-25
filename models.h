#ifndef MODELS_H
#define MODELS_H

#include <string>

//base struct for the system to create user
struct User {
	std::string username;
	std::string password;
	double credit = 100.0;//100 credit for every new user
};

struct Food{
	std::string name;
	double price;
};
#endif
