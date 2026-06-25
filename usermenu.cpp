#include <fstream>
#include "auth.h"
#include <string>
#include <iostream>
#include "menu.h"
#include "models.h"

//set variable for menu,this whole stucture is quite simillar to the main menu,u can check my explaination there :D
void showUserMenu() {
	int subChoice;
	bool loggedIn = true;

	while (loggedIn) {
		std::cout << "\n--- User Menu ---\n";
		std::cout << "1. View Food List (Not yet done)\n2. Logout\n Please choose one option by typing the number\n";
		std::cin >> subChoice;

		switch (subChoice) {
		case 1:
			std::cout << "I Said, NO YET DONE!!!\n";
			break;
		case 2:
			loggedIn = false;
			std::cout << "Logged out successfully.\n";
			break;
		default:
			std::cout << "Invalid choice!\n";
		}
	}
}
   