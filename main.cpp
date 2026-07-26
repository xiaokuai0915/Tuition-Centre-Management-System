#include <iostream>
#include "auth.h"
#include "../Utils/models.h"
#include "../Utils/menu.h"
#include "../Utils/storage.h"
#include "../Utils/tools.h"

int main() {
	//a basic loop system to keep alive
	DATA(); //create a folder called Data to store all the txt file if it is not exist yet
	User currentUser; //create a user based on the struct declared on models.h
	

	int choice;
	bool running = true; //set it to keep running until true become false

	while (running) {
		std::cout << "\n--- Welcome System --\n";
		std::cout << "1. Register\n2. Login\n0. Exit\nPlease choose one option by typing the number\n";
		choice = intgerinputfilter("Enter your choice: ");//call the input filter function to get the input and check if it is valid
		if (choice == -1) {
			std::cout << "Invalid input! Please enter a valid number\n";
			continue;
		}
		if (choice == -2) {
			std::cout << "Input cannot be empty! Please enter a valid number\n";
			continue;
		}

		//switch here get result from the choice and entering it to case for different result
		switch (choice) {
		case 1:
			registerUser(); //take result from auth.cpp and continue
			break; //break means end this case and go back to the choice section
		case 2:
			if (login(currentUser)) { //call login
				std::cout << "Login successful!\n";

				if (currentUser.role == 1) { //for admin role
					std::cout << "Redirecting to admin menu...\n";
					showAdminMenu(currentUser); 
				}
				else if (currentUser.role == 0) { //for student role
					std::cout << "Redirecting to user menu...\n";
					loadUserCourses(currentUser); //load user profile from storage.cpp
					loadActionLogs(); //load action logs from storage.cpp
					showUserMenu(currentUser);
				}
			}
			else {
				std::cout << "\nLogin failed! Please try again.\n";
			}
			break;
		case 0:
			running = false; //change the running status to false, so it wont continue run
			std::cout << "\nStoping the program. Bye!";
			break;
		default:
			std::cout << "Invalid input! Please enter a valid number,\n";
			break;
		}
	}
	return 0;
}
