#include <fstream>
#include "tools.h"
#include "auth.h"
#include "models.h"
#include <string>
#include <iostream>
#include <limits>


//Register and save into txt file
void registerUser() {
    User newUser;
    bool checkname;
    bool registration = false;


    //check if username already exists
    do {
        checkname = false;
		newUser.username = stringinputfilter("Create username: (Enter 0 to cancel registration)"); //call the input filter function to get the input and check if it is valid

		if (newUser.username == "0") {
			std::cout << "Registration cancelled.\n";
			return;
		}

        std::ifstream inFile("user.txt"); //ifstream means read the file
        std::string fileU, fileP;
        int fileR;

        while (inFile >> fileU >> fileP >> fileR) {
            std::cout << "[DEBUG] Comparing " << newUser.username << " with " << fileU << "\n"; //same reason as login, for debugging purpose
            if (newUser.username == fileU) {
                std::cout << "Username already exist, please use another username.\n";
                checkname = true;
                break;
            }
        }
    } while (checkname);

	newUser.password = stringinputfilter("Create password: "); //call the input filter function to get the input and check if it is valid

    do {
		newUser.role = intgerinputfilter("Enter role (0 for Student, 1 for Teacher): "); //call the input filter function to get the input and check if it is valid
        
		if (newUser.role == -1) {
			std::cout << "Invalid input. Please try again.\n";
			continue;
		}

		if (newUser.role == -2) {
			std::cout << "Input cannot be empty. Please enter a valid number.\n";
			continue;
		}

        if (newUser.role == 0 || newUser.role == 1) {
            break;
        }
        else {
            std::cout << "Invalid input.\n";
        }
    } while (true); //code always run unless breaked

    if (newUser.role == 1) {
        newUser.codeT = intgerinputfilter("Enter Teacher code: "); //call the input filter function to get the input and check if it is valid

		if (newUser.codeT == -1) {
			std::cout << "Invalid input. Please try again.\n";
			continue;
		}

		if (newUser.codeT == -2) {
			std::cout << "Input cannot be empty. Please enter a valid number.\n";
			continue;
		}

        if (newUser.codeT == newUser.teacherCode) { //detect teacher code from models.h
            registration = true;
        }
        else {
            std::cout << "Code invalid.\n";
			continue;
        }
    }
    else {
        registration = true;
    }

    if (registration) {
        //ofstream is create or edit the file, ios::app is to keep the previous thing that alr available inside the file so it wont get wipe out when running this row
        std::ofstream outFile("user.txt", std::ios::app);
        outFile << newUser.username << " " << newUser.password << " " << newUser.role << "\n"; // store username , password, role one by one
        outFile.close();//close the file to avoid error input into the file
        std::cout << "Registered successfully! Please log in now!\n";
    }
    else {
        std::cout << "Registration unsuccessful. Please try again.\n";
    }
}

//Check name and password from txt file and send result to main
bool login(User& currentUser) {
    std::string inputU, inputP;
    inputU = stringinputfilter("Username: (Enter 0 to cancel login) ");
    
	if (inputU == "0") {
		std::cout << "Login cancelled.\n";
		return false;
	}

    inputP = stringinputfilter("Password: ");

    std::ifstream inFile("user.txt"); //ifstream means read the file
    std::string fileU, fileP;
    int fileR;


    //if input username = username in txt file then send true as output, if no then false, password also
    while (inFile >> fileU >> fileP >> fileR) {
        std::cout << "[DEBUG] Comparing " << inputU << " with " << fileU << "\n"; //temporary for me to debug, i just leave it here until when we need to delete it :D

        if (fileU == inputU && fileP == inputP) {
            currentUser.username = inputU;
            currentUser.role = fileR;
            return true;
        }

    }
    return false;
}
