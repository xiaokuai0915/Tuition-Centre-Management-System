#include <fstream>
#include "../Utils/tools.h"
#include "auth.h"
#include "../Utils/models.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>


//Register and save into txt file
void registerUser() {
    User newUser;
    bool checkname;
    bool registration = false;
    int ID = 0;
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
        std::string line;

        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string fileID, fileusername, filepassword, filerole;

            if (std::getline(ss, fileID, ',') &&//when reach , then take the thing before , and put it into variable to 分类
                std::getline(ss, fileusername, ',') &&//&& means if the stuff is correct and can be read then continue to next row
                std::getline(ss, filepassword, ',') &&
                std::getline(ss, filerole, ',')) {

                std::cout << "[DEBUG] Comparing " << newUser.username << " with " << fileusername << "\n"; //same reason as login, for debugging purpose
                if (newUser.username == fileusername) {
                    std::cout << "Username already exist, please use another username.\n";
                    checkname = true;
                    break;
                }
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

    std::ifstream inFile("DATA/user.txt");
    std::string line;
    int lineCount[] = { 1, 1 };
    while (std::getline(inFile, line)) {
        if (line.front() == 'S') {
            ++lineCount[0];
        }
        else if (line.front() == 'T') {
            ++lineCount[1];
        }
    }
    inFile.close();
    if (newUser.role == 1) {
        codeT = intgerinputfilter("Enter Teacher code: "); //call the input filter function to get the input and check if it is valid

		if (codeT == -1) {
			std::cout << "Invalid input. Please try again.\n";
		}

		if (codeT == -2) {
			std::cout << "Input cannot be empty. Please enter a valid number.\n";
		}

        if (codeT == teacherCode) { //detect teacher code from models.h
            newUser.ID = "T";
            ID = lineCount[1];
            registration = true;
        }
        else {
            std::cout << "Code invalid.\n";
        }
    }
    else {
        newUser.ID = "S";
        ID = lineCount[0];
        registration = true;
    }

    if (registration) {
        //ofstream is create or edit the file, ios::app is to keep the previous thing that alr available inside the file so it wont get wipe out when running this row
        std::ofstream outFile("Data/user.txt", std::ios::app);
        outFile << newUser.ID << std::setfill('0') << std::setw(3) << ID << ","
            << newUser.username << "," << newUser.password << "," << newUser.role << "\n"; // store ID, username , password, role one by one
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
    std::string line;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string strID, username, password, role;

        if (std::getline(ss, strID, ',') &&//when reach , then take the thing before , and put it into variable to 分类
            std::getline(ss, username, ',') &&//&& means if the stuff is correct and can be read then continue to next row
            std::getline(ss, password, ',') &&
            std::getline(ss, role, ',')) {

            std::cout << "[DEBUG] Comparing " << inputU << " with " << username << "\n";

            if (username == inputU && password == inputP) {
                currentUser.ID = strID;
                currentUser.username = inputU; //if entered username and password is both found from the text file and it is correct
                currentUser.password = inputP;
                currentUser.role = stoi(role);  // assign username and role into the user structure that create on main file
                return 0;
            }
        }
    }

    //if input username = username in txt file then send true as output, if no then false, password also
    return 2;
}
