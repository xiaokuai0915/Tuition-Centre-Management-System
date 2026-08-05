#include <fstream>
#include "../Utils/tools.h"
#include "auth.h"
#include "../Utils/models.h"
#include <string>
#include <iostream>
#include <limits>


//Register and save into txt file
void registerUser() {
    User newUser;
    bool checkname;
    bool registration = false;
	int teacherCode = 1234; //teacher code to register as teacher, can be changed to any number you want
    int codeT;
    //check if username already exists
    do {
        checkname = false;
		newUser.username = stringinputfilter("Create username (Enter 0 to cancel registration) : "); //call the input filter function to get the input and check if it is valid

		if (newUser.username == "0") {
			std::cout << "Registration cancelled.\n";
			return;
		}

        std::ifstream inFile("Data/user.txt"); //ifstream means read the file
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
        codeT = intgerinputfilter("Enter Teacher code: "); //call the input filter function to get the input and check if it is valid

		if (codeT == -1) {
			std::cout << "Invalid input. Please try again.\n";
			return;
		}

		if (codeT == -2) {
			std::cout << "Input cannot be empty. Please enter a valid number.\n";
			return;
		}

        if (codeT == teacherCode) { //detect teacher code from models.h
            registration = true;
        }
        else {
            std::cout << "Code invalid.\n";
			return;
        }
    }
    else {
        registration = true;
    }

    if (registration) {
        //ofstream is create or edit the file, ios::app is to keep the previous thing that alr available inside the file so it wont get wipe out when running this row
        std::ofstream outFile("Data/user.txt", std::ios::app);
        outFile << newUser.username << " " << newUser.password << " " << newUser.role << "\n"; // store username , password, role one by one
        outFile.close();//close the file to avoid error input into the file
        std::cout << "Registered successfully! Please log in now!\n";
    }
    else {
        std::cout << "Registration unsuccessful. Please try again.\n";
    }
}

//Check name and password from txt file and send result to main
int login(User& currentUser) { //0 if success, 1 if cancel, 2 if fail
    std::string inputU, inputP;
    inputU = stringinputfilter("Username (Enter 0 to cancel login) : ");
    
	if (inputU == "0") {
		return 1;
	}

    inputP = stringinputfilter("Password: ");

    std::ifstream inFile("Data/user.txt"); //ifstream means read the file
    std::string fileU, fileP;
    int fileR;


    //if input username = username in txt file then send true as output, if no then false, password also
    while (inFile >> fileU >> fileP >> fileR) {
        std::cout << "[DEBUG] Comparing " << inputU << " with " << fileU << "\n"; //temporary for me to debug, i just leave it here until when we need to delete it :D

        if (fileU == inputU && fileP == inputP) {
            currentUser.username = inputU; //if entered username and password is both found from the text file and it is correct
            currentUser.role = fileR;  // assign username and role into the user structure that create on main file
            return 0;
        }

    }
    return 2;
}
