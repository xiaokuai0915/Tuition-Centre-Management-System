#pragma once
#include <iostream>
#include <string>

namespace AdminAuth {

	const std::string AdminPassword = "Admin1234";
	
	inline bool authenticateAdmin() {

		system("cls");
		std::cout << "==================\n";
		std::cout << "Welcome, Admin.\n";
		std::cout << "==================\n";
		std::cout << "Enter Admin Password: ";

		std::string input;
		std::cin >> input;

		if (input == AdminPassword) {
			std::cout << "\n\t ACCESS GRANDTED! Verifying credentials......\n";
			std::cout << "\t Transferring to Admin dashboard......";
			system("pause");
			return true; //Verification success
		}
		else {
			std::cout << "\n\t ACCESS DENIED: Invalid admin pssword.\n";
			std::cout << "\tPress any key to drop back to the main menu.";
			system("pause");
			return false; //Verification failed
		}
		
	}

}
