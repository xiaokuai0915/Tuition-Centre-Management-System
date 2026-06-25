#include <iostream>
#include "auth.h"
#include "models.h"


int main() {
	int choice;
	
	std::cout << "1. Register\n2. Login\n Please Choose: ";
	std::cin >> choice;

	if (choice == 1) {
		registerUser();
	}
	else if (choice == 2) {
		if (login()) {
			std::cout << "Login sucessful! Welcome to the system.\n";
		}
		else {
			std::cout << "Login failed. Please check your username or password again.\n";
		}
	}

	return 0;
}

