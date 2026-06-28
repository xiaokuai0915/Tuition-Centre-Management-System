#include <iostream>
#include "adminauth.h"

void openTuitionAdminDashboard() {
	system("cls");
	system("pause");
}

int main() {

	int choice;

	while (true) {
		system("cls");
		std::cout << "===========================\n";
		std::cout << "Welcome to tuition centre.\n";
		std::cout << "===========================\n";
		std::cout << "1. Admin Dashboard (Staff only)\n";
		std::cout << "2. Exit\n";
		std::cout << "Enter input selection\n";
		std::cin >> choice;

		if (choice == 1) {
			if (AdminAuth::authenticateAdmin()) {
				openTuitionAdminDashboard();
			}
		}
		else if (choice == 2) {
			break;
		}
	}
	return 0;
}