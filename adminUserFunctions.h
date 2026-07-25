#ifndef ADMINUSERFUNCTIONS_H
#define ADMINUSERFUNCTIONS_H

#include "models.h"

void userModulePortal(User& currentUser);
void addNewUser();
void searchUser();
void updateUser(User& currentUser);
void deleteUser(User& currentUser);
void displayUser();

#endif // !ADMINUSERFUNCTIONS_H
