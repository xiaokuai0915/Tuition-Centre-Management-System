#ifndef MODELS_H
#define MODELS_H

#include <string>

//base struct for the system to create user
struct User {
	std::string username;
	std::string password;
	int level = 0;
	double credit = 100.0;//100 credit for every new user
	int code = 0;
	int adminCode = 123456; //code to register as a admin
};

struct Food {
	std::string name;
	double price;
};
#endif
