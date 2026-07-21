#include "adminUserFunctions.h"
#include "tools.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>

void userModulePortal() {
    bool portal = true;
    int portalChoice;
    while (portal) {
        std::cout << "\n===========================\n";
        std::cout << "|Admin Portal: User module|\n";
        std::cout << "===========================\n\n";

        std::cout << "Choose one option by typing number:\n1. Add new record\n2. Update record\n3. Delete record\n4. Search record\n5. Display records\n0. Back to Admin Menu\n";
        std::cout << std::setfill('=') << std::setw(50) << "" << '\n';

        portalChoice = intgerinputfilter("Enter your choice(0-5): ");

        switch (portalChoice) {
        case 1:
            addNewUser();
            break;
        case 2:
            updateUser();
            break;
        case 3:
            deleteUser();
            break;
        case 4:
            searchUser();
            break;
        case 5:
            displayUser();
            break;
        case 0:
            portal = false;
            std::cout << "Reverting back to Admin menu......\n\n";
            break;
            //Using default to avoid user type in the wrong input
        case -2:
            std::cout << "Input cannot be empty. Please enter a valid number.\n";
            break;
        default:
            std::cout << "Invalid input! Please enter a valid number.\n\n";
            break;
        }
    }
}

void addNewUser() {
    std::ofstream outfile("user.txt", std::ios::app);
    std::string username, password;
    int role;

    bool checkname;
    do { //copied whole thing from auth.cpp, used to check if username exists or not
        checkname = false;
        username = stringinputfilter("Create username: "); //call the input filter function to get the input and check if it is valid

        if (username == "0") {
            std::cout << "Registration cancelled.\n";
            return;
        }

        std::ifstream file("user.txt");
        std::string fileU, fileP;
        int fileR;

        while (file >> fileU >> fileP >> fileR) {
            std::cout << "[DEBUG] Comparing " << username << " with " << fileU << "\n";
            if (username == fileU) {
                std::cout << "Username already exist, please use another username.\n";
                checkname = true;
                break;
            }
        }
    } while (checkname);
    password = stringinputfilter("Create password: ");
    do {
        role = intgerinputfilter("Enter role (Teacher=1, Student=0): ");
        if (role == -1) { //if -1 is returned, it means a !int value is entered
            std::cout << "Invalid input. Please try again!\n";
        }
        if (role == -2) { //if -2 is returned, it means an empty input was entered
            std::cout << "Input cannot be empty. Please enter a valid number.\n";
        }
        if (role == 0 || role == 1) { //role only accepts 0 and 1
            break;
        }
        else {
            std::cout << "Invalid input. Please try again!\n";
        }
    } while (true);

    outfile << username << " " << password << " " << role << std::endl; //Enter data to file
    outfile.close();
    std::cout << "User added successfully.\n";
}

void searchUser() {
    std::ifstream infile("user.txt");
    std::string username, password;
    int role;

    std::string searchUser;
    searchUser = stringinputfilter("Enter username to search: ");

    bool found = false;
    while (infile >> username >> password >> role) { //read file line by line until it reaches the end
        if (username == searchUser) {
            std::cout << "User found\n";
            std::cout << "Username: " << username << std::endl;
            std::cout << "Password: " << password << std::endl;
            std::cout << "Role: " << (role == 1 ? "Teacher" : "Student") << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "User not found.\n";
    }
    infile.close();
}

void updateUser() {
    std::ifstream infile("user.txt");
    std::string username, password;
    int role;
    std::ofstream temp("temp.txt");

    std::string searchUser;
    searchUser = stringinputfilter("Enter username to update: ");

    bool found = false;
    while (infile >> username >> password >> role) {
        if (username == searchUser) {
            
            bool checkname;
            do {
                checkname = false;
                username = stringinputfilter("Create username: ");

                if (username == "0") {
                    std::cout << "Registration cancelled.\n";
                    return;
                }

                std::ifstream file("user.txt");
                std::string fileU, fileP;
                int fileR;

                while (file >> fileU >> fileP >> fileR) {
                    std::cout << "[DEBUG] Comparing " << username << " with " << fileU << "\n";
                    if (username == fileU) {
                        std::cout << "Username already exist, please use another username.\n";
                        checkname = true;
                        break;
                    }
                }
            } while (checkname);
            password = stringinputfilter("Enter new password: ");
            do {
                role = intgerinputfilter("Enter new role (Teacher=1, Student=0): ");
                if (role == -1) { //if -1 is returned, it means a !int value is entered
                    std::cout << "Invalid input. Please try again!\n";
                }
                if (role == -2) { //if -2 is returned, it means an empty input was entered
                    std::cout << "Input cannot be empty. Please enter a valid number.\n";
                }
                if (role == 0 || role == 1) { //role only accepts 0 and 1
                    break;
                }
                else {
                    std::cout << "Invalid input. Please try again!\n";
                }
            } while (true);

            found = true;
        }
        temp << username << " " << password << " " << role << std::endl; //copies all data onto it
    }

    infile.close();
    temp.close();

    remove("user.txt");
    if (rename("temp.txt", "user.txt") != 0) { //rename will change temp.txt to user.txt and return 0, !=0 checks if it returns a non 0 value
        std::cout << "Update failed.\n";
    }

    std::cout << (found ? "User updated.\n" : "User not found.\n");
}

void deleteUser() {
    std::ifstream infile("user.txt");
    std::string username, password;
    int role;
    std::ofstream temp("temp.txt");

    std::string deleteUser = stringinputfilter("Enter username to delete: ");

    bool found = false;
    while (infile >> username >> password >> role) {
        if (username == deleteUser) {
            found = true;
            continue; //skips copying this line of data, achieving a delete function
        }
        temp << username << " " << password << " " << role << std::endl;
    }

    infile.close();
    temp.close();

    remove("user.txt");
    if (rename("temp.txt", "user.txt") != 0) {
        std::cout << "Update failed.\n";
    }

    std::cout << (found ? "User deleted.\n" : "User not found.\n");
}

void displayUser() {
    std::ifstream infile("user.txt");
    std::string username, password; int role;

    int displayChoice = intgerinputfilter("\nChoose one option by typing number:\n"
        "1. Display all user\n"
        "2. Display all teacher\n"
        "3. Display all student\n"
        "Enter your choice(1-3): ");
    int totalUser = 0;

    std::cout << "\n- -------------------- - ------- -\n";
    std::cout << "| Username             | Role    |\n";
    std::cout << "- -------------------- - ------- -\n";
    switch (displayChoice) {

        case 1:
            while (infile >> username >> password >> role) {
                std::cout << std::setfill(' ');
                std::cout << "| " << std::left << std::setw(20) << username
                    << std::setw(0) << " | "
                    << (role == 1 ? "Teacher" : "Student") << " |\n";

                totalUser++;
            }
            std::cout << "- -------------------- - ------- -\n";
            std::cout << "                    Total Users: " << totalUser << std::endl;
            break;

        case 2:
            while (infile >> username >> password >> role) {
                if (role == 1) {
                    std::cout << std::setfill(' ');
                    std::cout << "| " << std::left << std::setw(20) << username
                        << std::setw(0) << " | "
                        << (role == 1 ? "Teacher" : "Student") << " |\n";

                    totalUser++;
                }
            }
            std::cout << "- -------------------- - ------- -\n";
            std::cout << "                  Total teacher: " << totalUser << std::endl;
            break;

        case 3:
            while (infile >> username >> password >> role) {
                if (role == 0) {
                    std::cout << std::setfill(' ');
                    std::cout << "| " << std::left << std::setw(20) << username
                        << std::setw(0) << " | "
                        << (role == 1 ? "Teacher" : "Student") << " |\n";

                    totalUser++;
                }
            }
            std::cout << "- -------------------- - ------- -\n";
            std::cout << "                  Total student: " << totalUser << std::endl;
            break;

        case -2:
            std::cout << "Input cannot be empty. Please enter a valid number.\n";
            break;

        default:
            std::cout << "Invalid input! Please enter a valid number.\n";
            break;
    }
}
