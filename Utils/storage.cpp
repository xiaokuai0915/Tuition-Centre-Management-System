#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "tools.h"
#include "models.h"
#include "../auth.h"
#include "menu.h"
#include "storage.h"
#include <filesystem>

std::string logActionName[MAX_LOGS];
int logMatrix2D[MAX_LOGS][3];
int logCounter = 0;

void DATA() {
	if (!std::filesystem::exists("Data")) {
		std::filesystem::create_directory("Data");
	}
}

void saveUserCourses(const User& currentUser) { //load current user profile
	std::vector<std::string> otherUserData;  //using vector to temporary save other user profile（and skip the current user one first)
	std::ifstream infile("Data/user_courses.txt"); //open user_courses.txt file
	std::string line;

	while (std::getline(infile, line)) {  //loop , read all the things inside the file one by one and store into variable line
		if (line.find(currentUser.username + ",") != 0) { //if the line doesnt have current user name
			otherUserData.push_back(line);                //store this line (as i mention on row 13) to the vector 
		}
	}
	infile.close();//close the file to avoid error 

	std::ofstream outfile("Data/user_courses.txt");//write the file

	for (const auto& l : otherUserData) {//write all the things into the file one by one that alr store in the vector
		outfile << l << "\n";// l is temporary variable that create on row 22, this is write all the other user profile things back to the file
	}                        //i m not using ios::app here cuz i face multiplying bug when change user account when using that so i change it to this
	for (const auto& c : currentUser.mypackage) {//store current user data into the file
		outfile << currentUser.username << "," << c.id << "," << c.Name << "," << c.price << "\n";
	}
	outfile.close();//close the file to avoid error 
}

void loadUserCourses(User& currentUser) {
	std::ifstream infile("Data/user_courses.txt");//read the file
	std::string line;
	currentUser.mypackage.clear();//clean the vector before read

	while (std::getline(infile, line)) {//same as on top, but this time we string more variable to 分类 those stuff out
		std::stringstream ss(line);//auto process those variable into the format given(and we feed line into the when ss is created instantly everyloop)
		std::string username, idStr, name, priceStr;

		if (std::getline(ss, username, ',') &&//when reach , then take the thing before , and put it into variable to 分类
			std::getline(ss, idStr, ',') &&//&& means if the stuff is correct and can be read then continue to next row
			std::getline(ss, name, ',') &&
			std::getline(ss, priceStr, ',')) {

			if (username == currentUser.username) {//changing string that taken out from the file to the variable type that could be understand by the compiler
				Course c;
				c.id = std::stoi(idStr);// stoi is string to integer
				c.Name = name;
				c.price = std::stod(priceStr);//stod is string to double
				currentUser.mypackage.push_back(c);//
			}
		}

	}
	infile.close();//close the file to avoid error 
}

void loadActionLogs() {
	std::ifstream inFile("Data/action_logs.txt"); //open action_logs.txt to read previous history
	if (!inFile.is_open()) {
		return; //if file doesnt exist yet (first time run), just return nothing
	}

	std::string username, name;
	int courseId, statusCode;

	while (inFile >> username >> name >> courseId >> statusCode) { //read data piece by piece from file loop
		if (logCounter >= MAX_LOGS) {
			break; // Stop loading if we reach the maximum number of logs (prevent overflow)
		}

		logActionName[logCounter] = name;                  //store action name into 1d array
		logMatrix2D[logCounter][0] = courseId;             //store course id into 2d array column 0
		logMatrix2D[logCounter][1] = statusCode;           //store status code into 2d array column 1
		logMatrix2D[logCounter][2] = logCounter + 1; // Use logCounter + 1 as a simple timestamp or unique identifier (column 2)
		logCounter++;                                      //increase counter for next row
	}
	inFile.close(); //close file to avoid leak
}

void recordUserAction(int courseId, const std::string& name, int statusCode, const std::string& username) {
	if (logCounter >= MAX_LOGS) {
		std::cout << "Log limit reached. Cannot record more actions.\n"; //protect array from out of bound
		return;
	}

	logActionName[logCounter] = name;                  //save action name to 1d array
	logMatrix2D[logCounter][0] = courseId;             //save course id to 2d array col 0
	logMatrix2D[logCounter][1] = statusCode;           //save status code to 2d array col 1
	logMatrix2D[logCounter][2] = logCounter + 1; // Use logCounter + 1 as a simple timestamp or unique identifier (col 2)
	logCounter++;                                      //move to next index

	std::ofstream outFile("Data/action_logs.txt", std::ios::app); //open file with append mode to save permanently
	if (outFile.is_open()) {
		outFile << username << " " << name << " " << courseId << " " << statusCode << "\n"; //write log format into text
		outFile.close(); //close file
	}
	else {
		std::cout << "Error: Unable to open action_logs.txt for writing.\n";
	}
}

void searchBooking() {
	if (logCounter == 0) {
		std::cout << "No booking logs available.\n"; //check if array is empty
		return;
	}

	int searchId = intgerinputfilter("Enter Course ID to search: "); //ask user for course id they want to find
	if (searchId == -1) {
		std::cout << "Invalid input. Please try again!\n";
		return;
	}
	if (searchId == -2) {
		std::cout << "Input cannot be empty. Please enter a valid number.\n";
		return;
	}

	bool found = false; //flag to check if we matched anything
	std::cout << "\n--- Search Results for Course ID: " << searchId << " ---\n";

	for (int i = 0; i < logCounter; ++i) { //loop through 1d and 2d array one by one to search
		if (logMatrix2D[i][0] == searchId) { //if column 0 (course id) match user input
			std::cout << "Record No: " << logMatrix2D[i][2] //print out matching result details
				<< " | Action: " << logActionName[i]
				<< " | Course ID: " << logMatrix2D[i][0]
				<< " | Status: " << logMatrix2D[i][1] << "\n";
			found = true;
		}
	}
	if (!found) {
		std::cout << "No records found for Course ID: " << searchId << "\n"; //if loop finished but nothing match
	}
}