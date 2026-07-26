#ifndef STORAGE
#define STORAGE
#include "../auth.h"

void saveUserCourses(const User& currentUser);
void loadUserCourses(User& currentUser);
const int MAX_LOGS = 100;
extern std::string logActionName[MAX_LOGS]; // 1D array to store maximum 100 logs
extern int logMatrix2D[MAX_LOGS][3]; // 2D array to store maximum 100 logs with 3 columns (userID, actionID, counter)
extern int logCounter; // Counter to keep track of the number of logs
void recordUserAction(int courseId, const std::string& name, int statusCode, const std::string& username);
void loadActionLogs(); 
void searchBooking();
void DATA();

#endif