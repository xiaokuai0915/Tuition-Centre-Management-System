#include <fstream>
#include "../auth.h"
#include <string>
#include <iostream>
#include "../Utils/menu.h"
#include "../Utils/models.h"
#include "../Utils/storage.h"
#include "../Utils/tools.h"
#include "userpackage.h"
#include <vector>

std::vector<Course> allCourse = { //create a course vector to store courses
		{1,"Mathematics", 100.5},
		{2,"Problem solving and programming", 200.0},
		{3,"Science", 350.5}
};


void showUserMenu(User& currentUser) { //recieve current user detail
	int subChoice;
	bool loggedIn = true; //loop control

	while (loggedIn) {
		std::cout << "\n--- User Menu --- \n";
		std::cout << "1. View All Courses\n2. Add Course to Package\n3. Review my package\n4. Remove Course from Package\n5. Modify my package\n6. Search Booking Record\n0. Log out \nPlease choose one option by typing the number\n";
		subChoice = intgerinputfilter("Enter your choice: "); //call the input filter function to get the input and check if it is valid	

		if (subChoice == -1) {
			std::cout << "Invalid input. Please try again!\n";
			continue;
		}
		
		if (subChoice == -2) {
			std::cout << "Input cannot be empty. Please enter a valid number.\n";
			continue;
		}

		if (subChoice == 1) {
			for (const auto& c : allCourse) { /* c is temporary variable, autolet it auto detect the type of variable of c for allCourse that store in vector
													 const to avoid is telling the compiler to read the file only(no edit to the file)    & direct pass by reference ( no need to copy anymore so faster)*/
				std::cout << '\n';
				std::cout << "ID= " << c.id << ". " << c.Name << " - $" << c.price << "\n"; //since all the variable type is auto sync so can direct output easily
			}
		}
		else if (subChoice == 2) {
			std::cout << "\n--- Add Course to Package ---\n";
			addCoursetoPackage(currentUser, allCourse); //call the function in userpackage.cpp
		}

		else if (subChoice == 3) {
			myCourseSummary(currentUser, allCourse); //call the function in userpackage.cpp
		}

		else if (subChoice == 4) {
			removeCoursefromPackage(currentUser, allCourse); //call the function in userpackage.cpp
		}

		else if (subChoice == 5) {
			modifyUserPackage(currentUser, allCourse); //call the function in userpackage.cpp
		}

		else if (subChoice == 6) {
			searchBooking(); //call the function in storage.cpp
		}

		else if (subChoice == 0) {
			saveUserCourses(currentUser); //back up saving, save one more time to avoid accident
			loggedIn = false;    //end the loop by changing the bool variable on the top of this page
			std::cout << "Logged out successfully.\n";
			break;
		}
		else {
			std::cout << "Invalid option, try again.\n";
		}
	}
}
