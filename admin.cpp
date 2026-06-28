#include <iostream>
#include "adminauth.h"
//add the below informs or else the program wrong run properly
void openTuitionAdminDashboard() {
	system("cls");
	system("pause");
}
//I haven't add anything to the real main so I added int main here
int main() {

	int choice;
//the dashboard for admin
	while (true) {
		system("cls");
		std::cout << "===========================\n";
		std::cout << "Welcome to tuition centre.\n";
		std::cout << "===========================\n";
		std::cout << "1. Admin Dashboard (Staff only)\n";
		std::cout << "2. Exit\n";
		std::cout << "Enter input selection\n";
		std::cin >> choice;
//u can access the adminauth.h file if the password is correct
		if (choice == 1) {
			if (AdminAuth::authenticateAdmin()) {
				openTuitionAdminDashboard();
			}
		}
		else if (choice == 2) { //password incorrect and return back to the dashboard
			break;
		}
	}
	return 0;
}
