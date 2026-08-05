#ifndef AUTH_H
#define AUTH_H
//variable for register and login system
#include "../Utils/models.h"
#include <string>

void registerUser();
int login(User& currentUser);

#endif 