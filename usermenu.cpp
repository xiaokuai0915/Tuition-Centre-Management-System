#include <fstream>
#include "auth.h"
#include <string>
#include <iostream>
#include "menu.h"
#include "models.h"
#include <vector>

std::vector<Food> foodList = {
	{"Burger", 10.5},
	{"Pizza", 20.0},
	{"Soda", 3.5}
};

//set variable for menu,this whole stucture is quite simillar to the main menu,u can check my explaination there :D
void showUserMenu(User& currentUser) {
	int subChoice;
	bool loggedIn = true;

	while (loggedIn) {
		std::cout << "\n--- User Menu (Balance: $" << currentUser.credit << ") --- \n";
		std::cout << "1. View Food List\n2. Buy Food\n3. Logout\nPlease choose one option by typing the number\n";
		
		if (!(std::cin >> subChoice)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (subChoice == 1) {
			for (const auto& food : foodList) {
				std::cout << food.name << " - $" << food.price << "\n";
			}
		}
		else if (subChoice == 2) {
			int foodIndex;
			std::cout << " Enter food index (0-2): ";
			std::cin >> foodIndex;

			if (foodIndex >= 0 && foodIndex < foodList.size()) {
				if (currentUser.credit >= foodList[foodIndex].price) {
					currentUser.credit -= foodList[foodIndex].price;
					std::cout << "Purchased " << foodList[foodIndex].name << "!\n";
				}
				else {
					std::cout << "Insufficient credit!\n";
				}
			}
		}
		else if (subChoice == 3) {
			loggedIn = false;
			std::cout << "Logged out successfully.\n";
		}
		else {
			std::cout << "Invalid option, try again.\n";
		}
		
		
	}
}
   