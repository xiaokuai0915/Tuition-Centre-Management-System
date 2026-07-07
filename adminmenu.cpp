#include <iostream>
#include "models.h"
#include "adminmenu.h"

//Only can be access by admin
void showAdminMenu(User& currentUser) {

	//loop
	int subchoice;
	bool loggedin = true;

	//Output that will be shown on screen after entering into the admin account
	while (loggedin) {
		std::cout << "==========\n";
		std::cout << "Admin Menu\n";
		std::cout << "==========\n";
		std::cout << "Welcome, Admin.\n";
		std::cout << "Choose one option by typing number:\n1. Most Course Taken\n2. Student Enrollment\n3. Total amount of students\n4. Total amount of teachers\n5. Exit\n";

		//input filter
		if (!(std::cin >> subchoice)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		//using switch instead of if else
		switch (subchoice) {
		case 1:
			std::cout << "The most course taken is: \n\n";
			break;
		case 2:
			std::cout << "=====================\nStudent Enrollemnt\n=====================\n\n";
			break;
		case 3:
			std::cout << "The total amount of students is: \n\n";
			break;
		case 4:
			std::cout << "The total amount of teachers is: \n\n";
			break;
		case 5:
			loggedin = false;
			std::cout << "Logging out......\n\n";
			break;
			//Using default to avoid user type in the wrong input
		default:
			std::cout << "Invalid input! Please enter a valid number.\n\n";
			break;
		}

	}
}

