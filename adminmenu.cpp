#include <iostream>
#include <iomanip>
#include <vector>
#include "models.h"
#include "menu.h"
#include "reports.h"
#include "tools.h"


//Only can be access by admin
void showAdminMenu(User& currentUser) {
	std::vector<User> studentList;
	//loop
	int subchoice;
	bool loggedin = true;

	//Output that will be shown on screen after entering into the admin account
	while (loggedin) {
		std::cout << "==========\n";
		std::cout << "Admin Menu\n";
		std::cout << "==========\n";
		std::cout << "Welcome, Admin.\n\n";

		std::cout << "Choose one option by typing number:\n1. User Module\n2. Subject Module\n3. Schedule Module\n4. Booking Module\n5. Reporting Module\n6. Back to Main Menu\n";
		std::cout << std::setfill('=') << std::setw(50) << '\n';

		subchoice = intgerinputfilter("Enter your choice(1-6)= ");


		//using switch instead of if else
		switch (subchoice) {
		case 1:
			//mannage user module
			break;
		case 2:
			//subject module
		case 3:
			//schedule module
			break;
		case 4:
			//booking module
			break;
		case 5:
			std::cout << "\n[!] Opening Reporting Module dashboard......\n";//load the report module
			showReportModule(studentList);
			break;
		case 6:
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
