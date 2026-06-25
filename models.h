#ifndef MODELS_H
#define MODELS_H

#include <string>

//base struct for the system to create user
struct User {
	std::string username;
	std::string password;
	int userid = 0;
};
#endif
