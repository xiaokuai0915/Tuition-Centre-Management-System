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


void showUserMenu(User& currentUser) { //recieve current user detail
	int subChoice;
	bool loggedIn = true; //loop control

	while (loggedIn) {
		std::cout << "\n--- User Menu --- \n";
		std::cout << "1.View Course or Manage Course Section\n2.View timetable for taken course\n0.Log out \nPlease choose one option by typing the number\n";
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
			std::cout << "Redirecting to View Course or Manage Course section...\n";
			userpackage(currentUser, allCourse);
		}
		else if (subChoice == 2) {
			std::cout << "Redirecting to timetable section...\nTime table section is currently still in deveploment\nRedirecting back to User Menu...\n";
			break;
		}
		else if (subChoice == 0) {
			loggedIn = false; //change the running status to false, so it wont continue run
			std::cout << "\nLogged out!\nRedirecting back to Main Menu...\n";
			break;
		}

		else {
			std::cout << "Invalid option, try again.\n";
		}
	}
}
