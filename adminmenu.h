#ifndef ADMINMENU_H
#define ADMINMENU_H
#include <vector>
#include "models.h"

void showAdminMenu(User& currentUser, const std::vector<User>& studentList);

void showReportModule(const std::vector<User>& studentList);

#endif