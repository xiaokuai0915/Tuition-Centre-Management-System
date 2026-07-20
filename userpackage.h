#ifndef USERPACKAGE
#define USERPACKAGE
#include "models.h"


void modifyUserPackage(User& currentUser, const std::vector<Course>& allCourse);
void addCoursetoPackage(User& currentUser, const std::vector<Course>& allCourse);
void myCourseSummary(User& currentUser, const std::vector<Course>& allCourse);
void removeCoursefromPackage(User& currentUser, const std::vector<Course>& allCourse);

#endif