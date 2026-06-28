#include <fstream>
#include "auth.h"
#include "models.h"
#include <string>
#include <iostream>
#include <limits>

//Register and save into txt file
void registerUser() {
    User newUser;
    bool registration = false;

    std::cout << "Create username: "; std::cin >> newUser.username;
    std::cout << "Create password: "; std::cin >> newUser.password;

    do {
        newUser.role = -1; //Since 0 and 1 is used to determine role, set default value to -1 to avoid defaulting back to 0
        std::cout << "Enter role (Teacher=0, Student=1): ";
        if (!(std::cin >> newUser.role)) { //filter input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue; //ignore the rest of the code and start loop again
        }
        if (newUser.role == 0 || newUser.role == 1) {
            break;
        }
    } while (true); //code always run unless breaked

    if (newUser.role == 0) {
        std::cout << "Enter Teacher code: ";
        if (!(std::cin >> newUser.codeT)) { //filter input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (newUser.codeT == newUser.teacherCode) { //detect teacher code from models.h
            registration = true;
        }
        else {
            std::cout << "Code invalid.\n";
        }

        if (registration) {
            do {
                newUser.level = -1; //Since 0 and 1 is used to determine level, set default value to -1 to avoid defaulting back to 0
                std::cout << "Enter level (Admin=0, User=1): ";
                if (!(std::cin >> newUser.level)) { //filter input
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue; //ignore the rest of the code and start loop again
                }
                if (newUser.level == 0 || newUser.level == 1) {
                    break;
                }
            } while (true); //code always run unless breaked

            if (newUser.level == 0) {
                std::cout << "Enter Admin code: ";
                if (!(std::cin >> newUser.codeA)) { //filter input
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                if (newUser.codeA == newUser.adminCode) { //detect admin code from models.h
                    registration = true;
                }
                else {
                    std::cout << "Code invalid.\n";
                    registration = false;
                }
            }
        }
    }
    else {
        newUser.level = 1;
        registration = true;
    }

    if (registration) {
        //ofstream is create or edit the file, ios::app is to keep the previous thing that alr available inside the file so it wont get wipe out when running this row
        std::ofstream outFile("user.txt", std::ios::app);
        outFile << newUser.username << " " << newUser.password << " " << newUser.role << " " << newUser.level << "\n"; // store username , password, level one by one
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
    std::cout << "Username: "; std::cin >> inputU;
    std::cout << "Password: "; std::cin >> inputP;

    std::ifstream inFile("user.txt"); //ifstream means read the file
    std::string fileU, fileP;
    int fileR;
    int fileL;


    //if input username = username in txt file then send true as output, if no then false, password also
    while (inFile >> fileU >> fileP >> fileR >> fileL) {
        std::cout << "[DEBUG] Comparing " << inputU << " with " << fileU << "\n"; //temporary for me to debug, i just leave it here until when we need to delete it :D

        if (fileU == inputU && fileP == inputP) {
            currentUser.username = inputU;
            return true;
        }

    }
    return false;
}
