#include <iostream>
#include "auth.h"
#include "models.h"


int main() {
	int choice;
	bool running = true;

	while (running) {
		std::cout << "\n--- Welcome System --\n";
		std::cout << "1. Register\n2. Login\n3. Exit\nPlease choose one option by typing the number\n";
		std::cin >> choice;

		switch (choice) {
		case 1:
			registerUser();
			break;
		case 2:
			if (login()) {
				std::cout << "Login sucessful! Welcome.\n";
			}
			else
			{
				std::cout << "Login failed\n";
			}
			break;
		case 3:
			running = false;
			std::cout << "Stoping the program. Bye!";
			break;
		default:
			std::cout << "Invalid choice, please try again.\n";
		}
	}
	return 0;
}
