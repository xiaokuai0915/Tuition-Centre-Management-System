#include <fstream>
#include "auth.h"
#include <string>
#include <iostream>
#include "menu.h"
#include "models.h"
#include "storage.h"
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
		std::cout << "1. View All Courses\n2. Add Course to Package\n3. Review my package\n4. Remove Course from Package\n5. Log out \nPlease choose one option by typing the number\n";

		if (!(std::cin >> subChoice)) { //input filter, if not integer input will ignore and clear input
			std::cout << "Invalid option, try again.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else
		{
			char nextChar = std::cin.peek(); //peek to check the next character in the input buffer
			if (nextChar != '\n' && nextChar != ' ' && nextChar != EOF) { //if the next character is not a newline, it means there are extra characters in the input buffer
				std::cin.clear(); //clear the error state of cin
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore the rest of the line
				std::cout << "Invalid input , please try again!";
				continue; //go back to the start of the loop
			}
		}

		if (subChoice == 1) {
			for (const auto& c : allCourse) { /* c is temporary variable, autolet it auto detect the type of variable of c for allCourse that store in vector
													 const to avoid is telling the compiler to read the file only(no edit to the file)    & direct pass by reference ( no need to copy anymore so faster)*/
				std::cout << c.id << ". " << c.Name << " - $" << c.price << "\n"; //since all the variable type is auto sync so can direct output easily
			}
		}
		else if (subChoice == 2) {
			int id;
			std::cout << "\n--- Add Course to Package ---\n";
			std::cout << " Enter Course ID to add ";
			if (!(std::cin >> id)) {//input filter
				std::cout << "Invalid option, try again.\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}

			bool alreadyExists = false;
			for (const auto& c : currentUser.mypackage) {
				if (c.id == id) {alreadyExists = true; break;}
			}
			if (alreadyExists) {
				std::cout << "Error: Course (ID =" << id << ") is already exists in your package\n";
			}
			else {
				bool found = false; //detect course found or not
				for (const auto& c : allCourse) {

					if (c.id == id) { //search for subject by check id one by one
						currentUser.mypackage.push_back(c); //save(push back) to mypackage that in storage.cpp
						std::cout << "\n------------------\n";
						std::cout << "Added " << c.Name << " to package!\n";
						found = true;
						break;
					}
				}
			}
	    }
	
		else if (subChoice == 3) {
			std::cout << "\n--- My Package Summary ---\n";
			double total = 0;
			for (const auto& c : currentUser.mypackage) { //read all user course variable
				std::cout << "- " << c.Name << " ($" << c.price << ")\n";
				total += c.price;
			}
			std::cout << "Total Fee: $" << total << "\n";
	
		}

		else if (subChoice == 4) {
			int id;
			std::cout << "\n--- Remove Course from Package ---\n";
			for (const auto& c : currentUser.mypackage) { //read all user course variable
				std::cout << "(ID=" << c.id << ") - " << c.Name << " ($" << c.price << ")\n";
			}

			std::cout << "Enter Course ID to remove: ";
			if (!(std::cin >> id)) {//input filter
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input, please try again.\n";
				continue;
			}
			else {
				char nextChar = std::cin.peek(); //peek to check the next character in the input buffer
				if (nextChar != '\n' && nextChar != ' ' && nextChar != EOF) { //if the next character is not a newline, it means there are extra characters in the input buffer
					std::cin.clear(); //clear the error state of cin
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore the rest of the line
					std::cout << "Invalid input , please try again!";
					continue; //go back to the start of the loop
				}
			}
			bool found = false;
			for (auto it = currentUser.mypackage.begin(); it != currentUser.mypackage.end(); ++it) {
				if (it->id == id) {
					std::cout << "Removed " << it->Name << " from package!\n";
					currentUser.mypackage.erase(it); //remove the course from mypackage
					found = true;
					break;
				}
				if (!found) {
					std::cout << "\nCourse (id= " << id << ") is not found in your package ";
				}
			}  

		}
		else if (subChoice == 5) {
			saveUserCourses(currentUser);
			loggedIn = false;    //end the loop by changing the bool variable on the top of this page
			std::cout << "Logged out successfully.\n";
			break;
		}
		else {
			std::cout << "Invalid option, try again.\n";
		}
	}
}
