#ifndef MENU
#define MENU
#include <vector>

void showUserMenu(User& currentUser); // User is struct , & is pass by reference
void showAdminMenu(User& currentUser);
void showReportModule(const std::vector<User>& studentList);

#endif