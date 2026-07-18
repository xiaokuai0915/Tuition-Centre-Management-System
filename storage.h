#ifndef STORAGE
#define STORAGE
#include "auth.h"

void saveUserCourses(const User& currentUser);
void loadUserCourses(User& currentUser);

#endif

