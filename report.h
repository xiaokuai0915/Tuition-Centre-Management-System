#ifndef REPORTS_H
#define REPORTS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../Utils/models.h"


inline void readUserandCoursefile(std::vector<User>& allusers) { //inline is a function that when multiple files use this header file, it will not copy the whole real function into 
	std::ifstream userfile("DATA/user.txt");          // its own cpp file, instead, it act like a virtual header file that only one function exist in the header file so that the compiler won't crash due to multiple same file in different cpp file
	std::ifstream coursefile("DATA/user_courses.txt");   //意思是强制系统就算有很多cpp在用report.h，最后只需要融合成一个function，不可以重复复制一样的function,不然我需要写很多次一样的function
	User tempUser;
	//read user.txt file
	while (userfile >> tempUser.username >> tempUser.password >> tempUser.role) {
		if (tempUser.role == 0) {
			tempUser.mypackage.clear();//clear the remain record before starting the next command
			allusers.push_back(tempUser);
		}	
	}
	userfile.close();

	//read course file, since it has comma at the text file, we will use getline here instead of reading it directly
	std::string line;

	while (std::getline(coursefile, line)) {
		std::stringstream ss(line);
		std::string username, idStr, CourseStr, priceStr;

		if (std::getline(ss, username, ',') &&
			std::getline(ss, idStr, ',') &&
			std::getline(ss, CourseStr, ',') &&
			std::getline(ss, priceStr, ',')) {

			//make a folder to store the value and equalize the models.h
			Course c;
			c.id = std::stoi(idStr);   //convert string to int
			c.Name = CourseStr;
			c.price = std::stod(priceStr);  //convert string to double

			for (auto& user : allusers) {  //go back to allusers at line 18
				if (user.username == username) {    //check if this is the current user
					user.mypackage.push_back(c); //if this is the current user, put the course that he had selected and put into this currrent user
					break;
				}
			}
		}
	}
	coursefile.close();
}

void showReportModule();
void generateSummaryReport();
void generateDetailReport();
void calculateStatistic();
void sortRecord();
void displayAnalysis();

#endif