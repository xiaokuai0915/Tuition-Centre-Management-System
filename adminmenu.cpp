#include <iostream>
#include <iomanip>
#include <vector>
#include "models.h"
#include "menu.h"
#include "report.h"
#include "tools.h"
#include "adminUserFunctions.h"


//Only can be access by admin
void showAdminMenu(User& currentUser) {
	//loop
	int subchoice;
	bool loggedin = true;

	//Output that will be shown on screen after entering into the admin account
	while (loggedin) {
		std::cout << "\n==========\n";
		std::cout << "Admin Menu\n";
		std::cout << "==========\n";
		std::cout << "Welcome, Admin.\n\n";

		std::cout << "Choose one option by typing number:\n1. User Module\n2. Subject Module\n3. Schedule Module\n4. Booking Module\n5. Reporting Module\n0. Back to Main Menu\n";
		std::cout << std::setfill('=') << std::setw(50) << '\n';

		subchoice = intgerinputfilter("\nEnter your choice(0-5)= ");
		if (subchoice == -1) {
			std::cout << "Invalid input! Please enter a valid number\n";
			continue;
		}
		if (subchoice == -2) {
			std::cout << "Input cannot be empty! Please enter a valid number\n";
			continue;
		}


		//using switch instead of if else
		switch (subchoice) {
		case 1:
			userModulePortal();
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
			showReportModule();
			break;
		case 0:
			loggedin = false;
			std::cout << "Logging out......\n\n";
			break;
		default:
			std::cout << "Invalid input! Please enter a valid number.\n\n";
			break;
		}

	}
}
