#include <fstream>
#include "auth.h"
#include <string>
#include <iostream>

//Register and save into txt file
void registerUser(){
	User newUser;
	std::cout << "Create username: "; std::cin >> newUser.username;
	std::cout << "Create password: "; std::cin >> newUser.password;

	std::ofstream outFile("user.txt", std::ios::app); //ofstream is create nor edit the file, ios::app is to keep the previous thing that alr available inside the file so it wont get wipe out when running this row
	outFile << newUser.username << " " << newUser.password << "\n";
	std::cout << "Registered successfully! Please log in now!\n";

}

//Check name and password from txt file and send result to main
bool login() {
	std::string inputU, inputP;
	std::cout << "Username: "; std::cin >> inputU;
	std::cout << "Password: "; std::cin >> inputP;

	std::ifstream inFile("user.txt"); //ifstream means read the file
	std::string fileU, fileP;

	//i believe u understand by just watching here, it is just if input username = username in txt file then send true as output, if no then false, password either
	while (inFile >>fileU >> fileP){ 
		if (fileU == inputU && fileP == inputP) return true;
	}
	return false;
}