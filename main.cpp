#include <iostream>
#include "auth.h"
#include "models.h"
#include "menu.h"
#include "storage.h"
#include "adminmenu.h"

int main() {
	//a basic loop system to keep alive
	User currentUser; //for user
	User currentAdmin; //for admin

	int choice;
	bool running = true; //set it to keep running until true become false

	while (running) {
		std::cout << "\n--- Welcome System --\n";
		std::cout << "1. Register\n2. Login\n3. Exit\nPlease choose one option by typing the number\n";
		if (!(std::cin >> choice)) {//input filter
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input , please try again!";
			continue; //continue means go back to the start of the loop
		}
		else{
			char nextChar = std::cin.peek(); //peek to check the next character in the input buffer
			if (nextChar != '\n' && nextChar !=' ' && nextChar !=EOF) { //if the next character is not a newline, it means there are extra characters in the input buffer
				std::cin.clear(); //clear the error state of cin
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore the rest of the line
				std::cout << "Invalid input , please try again!";
				continue; //go back to the start of the loop
			}
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
					showUserMenu(currentUser);
				}
			}
			else {
				std::cout << "Login failed! Please try again.\n";
			}
			break;
		case 3:
			running = false; //change the running status to false, so it wont continue run
			std::cout << "Stoping the program. Bye!";
			break;
		default:
			std::cout << "Invalid input! Please enter a valid number,\n";
			break;
		}
	}
	return 0;
}
