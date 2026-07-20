#include <sstream>
#include <fstream>
#include <vector>
#include "models.h"
#include "auth.h"
#include "menu.h"
#include "storage.h"

void saveUserCourses(const User& currentUser) { //load current user profile
	std::vector<std::string> otherUserData;  //using vector to temporary save other user profile（and skip the current user one first)
	std::ifstream infile("user_courses.txt"); //open user_courses.txt file
	std::string line;

	while (std::getline(infile, line)) {  //loop , read all the things inside the file one by one and store into variable line
		if (line.find(currentUser.username + ",") != 0) { //if the line doesnt have current user name
			otherUserData.push_back(line);                //store this line (as i mention on row 13) to the vector 
		}
	}
	infile.close();//close the file to avoid error 

	std::ofstream outfile("user_courses.txt");//write the file

	for (const auto& l : otherUserData) {//write all the things into the file one by one that alr store in the vector
		outfile << l << "\n";// l is temporary variable that create on row 22, this is write all the other user profile things back to the file
	}                        //i m not using ios::app here cuz i face multiplying bug when change user account when using that so i change it to this
	for (const auto& c : currentUser.mypackage) {//store current user data into the file
		outfile << currentUser.username << "," << c.id << "," << c.Name << "," << c.price << "\n";
	}
	outfile.close();//close the file to avoid error 
}

void loadUserCourses(User& currentUser) {
	std::ifstream infile("user_courses.txt");//read the file
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