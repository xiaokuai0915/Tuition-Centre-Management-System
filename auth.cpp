#include <fstream>
#include "auth.h"
#include <string>
#include <iostream>

//Register and save into txt file
void registerUser(){
	User newUser;
	std::cout << "Create username: "; std::cin >> newUser.username;
	std::cout << "Create password: "; std::cin >> newUser.password;

	std::ofstream outFile("user.txt", std::ios::app);
	outFile << newUser.username << " " << newUser.password << "\n";
	std::cout << "Registered sucessfully!\n";

}

//Check name and password from txt file and send result to main
bool login() {
	std::string inputU, inputP;
	std::cout << "Username: "; std::cin >> inputU;
	std::cout << "Password: "; std::cin >> inputP;

	std::ifstream inFile("user.txt");
	std::string fileU, fileP;

	while (inFile >>fileU >> fileP){ 
		if (fileU == inputU && fileP == inputP) return true;
	}
	return false;
}