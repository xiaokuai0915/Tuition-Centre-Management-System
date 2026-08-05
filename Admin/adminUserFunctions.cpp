#include "adminUserFunctions.h"
#include "../Utils/tools.h"
#include "../Utils/models.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>

void userModulePortal(User& currentUser) {
    bool portal = true;
    int portalChoice;
    while (portal) {
        std::cout << "\n=============================\n";
        std::cout << "| Admin Portal: User module |\n";
        std::cout << "=============================\n\n";

        std::cout << "Choose one option by typing number:\n"
            "1. Add new record\n"
            "2. Update record\n"
            "3. Delete record\n"
            "4. Search record\n"
            "5. Display records\n"
            "0. Back to Admin Menu\n";
        std::cout << std::setfill('=') << std::setw(50) << "" << '\n';

        portalChoice = intgerinputfilter("Enter your choice(0-5): ");

        switch (portalChoice) {
        case 1:
            addNewUser();
            break;
        case 2:
            updateUser(currentUser);
            break;
        case 3:
            deleteUser(currentUser);
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
        case -2: //-2 means empty input
            std::cout << "Input cannot be empty. Please enter a valid number.\n";
            break;
        default:
            std::cout << "Invalid input! Please enter a valid number.\n\n";
            break;
        }
    }
}

void addNewUser() {
    std::ofstream outfile("Data/user.txt", std::ios::app);
    std::string username, password;
    int role;

    bool checkname;
    do { //check if username exists or not
        checkname = false;
        username = stringinputfilter("Create username (Enter 0 to cancel registration) : "); //call the input filter function to get the input and check if it is valid

        if (username == "0") {
            std::cout << "Registration cancelled.\n";
            return;
        }

        std::ifstream file("Data/user.txt");
        std::string fileU, fileP;
        int fileR;

        while (file >> fileU >> fileP >> fileR) {
            if (username == fileU) {
                std::cout << "Username already exist, please use another username.\n";
                checkname = true;
                break;
            }
        }
        file.close();
    } while (checkname);
    password = stringinputfilter("Create password: ");
    do {
        role = intgerinputfilter("Enter role (Teacher=1, Student=0): ");
        if (role == -1) { //if -1 is returned, it means a !int value is entered
            std::cout << "Invalid input. Please try again!\n";
        }
        else if (role == -2) { //if -2 is returned, it means an empty input was entered
            std::cout << "Input cannot be empty. Please enter a valid number.\n";
        }
        else if (role == 0 || role == 1) { //role only accepts 0 and 1
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
    std::ifstream infile("Data/user.txt");
    std::string username, password;
    int role;

    std::string searchUser;
    searchUser = stringinputfilter("Enter username to search: ");

    bool found = false;
    while (infile >> username >> password >> role) {
        if (username == searchUser) { //== means found
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

void updateUser(User& currentUser) {
    std::ifstream infile("Data/user.txt");
    std::string username, password;
    int role;
    std::vector<User> userList;

    std::string searchUser = stringinputfilter("Enter username to update: ");
    if (searchUser == currentUser.username) { //don't allow to edit logged in user
        std::cout << "Cannot update logged in user.\n";
        return;
    }

    bool found = false;
    while (infile >> username >> password >> role) {
        if (username == searchUser) { //edit user
            bool checkname;
            do { //check username
                checkname = false;
                username = stringinputfilter("Enter new username: ");

                if (username == "0") {
                    std::cout << "Registration cancelled.\n";
                    return;
                }

                std::ifstream file("Data/user.txt");
                std::string fileU, fileP;
                int fileR;

                while (file >> fileU >> fileP >> fileR) {
                    if (username == fileU && username != searchUser) {
                        std::cout << "Username already exist, please use another username.\n";
                        checkname = true;
                        break;
                    }
                }
                file.close();
            } while (checkname);
            password = stringinputfilter("Enter new password: ");
            do {
                role = intgerinputfilter("Enter new role (Teacher=1, Student=0): ");
                if (role == -1) { //if -1 is returned, it means a !int value is entered
                    std::cout << "Invalid input. Please try again!\n";
                }
                else if (role == -2) { //if -2 is returned, it means an empty input was entered
                    std::cout << "Input cannot be empty. Please enter a valid number.\n";
                }
                else if (role == 0 || role == 1) { //role only accepts 0 and 1
                    break;
                }
                else {
                    std::cout << "Invalid input. Please try again!\n";
                }
            } while (true);

            found = true;
        }
        User u; //push all data into userList
        u.username = username;
        u.password = password;
        u.role = role;
        userList.push_back(u);
    }

    infile.close();

    if (found) { //rewrites userList into user.txt if got changes
        std::ofstream outfile("Data/user.txt");
        for (User& u : userList) {
            outfile << u.username << " " << u.password << " " << u.role << "\n";
        }
        outfile.close();
        std::cout << "User updated.\n";
    }
    else {
        std::cout << "User not found.\n";
    }
}

void deleteUser(User& currentUser) {
    std::ifstream infile("Data/user.txt");
    std::string username, password;
    int role;
    std::vector<User> userList;

    std::string searchUser = stringinputfilter("Enter username to delete: ");
    if (searchUser == currentUser.username) { //don't allow to delete logged in user
        std::cout << "Cannot delete logged in user.\n";
        return;
    }

    bool found = false;
    while (infile >> username >> password >> role) {
        if (username != searchUser) { //push all data accept the user that'll be deleted
            User u;
            u.username = username;
            u.password = password;
            u.role = role;
            userList.push_back(u);;
        }
        else {
            found = true;
        }
    }

    infile.close();

    if (found) { //rewrites userList into user.txt if got changes
        std::ofstream outfile("Data/user.txt");
        for (User& u : userList) {
            outfile << u.username << " " << u.password << " " << u.role << "\n";
        }
        outfile.close();
        std::cout << "User deleted.\n";
    }
    else {
        std::cout << "User not found.\n";
    }
}

void displayUser() {
    std::ifstream infile("Data/user.txt");
    std::string username, password; int role;

    std::cout << std::setfill(' ');
    std::cout << "\nChoose one option by typing number:\n"
        << "1. Display all user\n"
        << "2. Display all teacher\n"
        << "3. Display all student\n";
    int displayChoice = 0;
    do {
        displayChoice = intgerinputfilter("Enter your choice(1-3): ");
        if (displayChoice == -2) { //if -2 is returned, it means an empty input was entered
            std::cout << "Input cannot be empty. Please enter a valid number.\n";
        }
        else if (displayChoice == -1 || !(displayChoice >= 1 && displayChoice <= 3)) { //if -1 is returned, it means a !int value is entered, also checks if displayChoice is 1,2,3
            std::cout << "Invalid input. Please try again!\n";
        }
        else {
            break;
        }
    } while (true);

    std::vector<User> allUsers;
    User temp;
    while (infile >> temp.username >> temp.password >> temp.role) { //repeats reading a line from user.txt and save into temp until it reaches the end
        allUsers.push_back(temp); //push data from temp into vector allUsers
    }
    for (int i = 0; i < allUsers.size() - 1; i++) { //bubble sort
        for (int j = 0; j < allUsers.size() - i - 1; j++) {
            std::string lowerCaseName1 = allUsers[j].username; //get the username on the current index
            std::string lowerCaseName2 = allUsers[j + 1].username; //get the username on the next index
            for (char& c : lowerCaseName1) { //convert current into lowercase char by char
                c = tolower(c);
            }
            for (char& c : lowerCaseName2) { //convert next into lowercase char by char
                c = tolower(c);
            }
            if (lowerCaseName1 > lowerCaseName2) { //comparison for string compares their ASCII values, if current's ASCII value is bigger than next's, then swap place
                temp = allUsers[j];
                allUsers[j] = allUsers[j + 1];
                allUsers[j + 1] = temp;
            }
        }
    }

    int totalUser = 0;
    std::cout << "\n- -------------------- - ------- -\n"
        << "| Username             | Role    |\n"
        << "- -------------------- - ------- -\n";

    switch (displayChoice) {
    case 1:
        for (const User& user : allUsers) { //display all user records
            std::cout << "| "
                << std::left << std::setw(20) << user.username
                << " | "
                << (user.role == 1 ? "Teacher" : "Student")
                << " |\n";
            totalUser++;
        }
        std::cout << "- -------------------- - ------- -\n"
            << "                    Total Users: " << totalUser << std::endl;
        break;

    case 2:
        for (const User& user : allUsers) { //display teacher records
            if (user.role == 1) {
                std::cout << "| "
                    << std::left << std::setw(20) << user.username
                    << " | Teacher |\n";
                totalUser++;
            }
        }
        std::cout << "- -------------------- - ------- -\n"
            << "                  Total teacher: " << totalUser << std::endl;
        break;

    case 3:
        for (const User& user : allUsers) { //display student records
            if (user.role == 0) {
                std::cout << "| "
                    << std::left << std::setw(20) << user.username
                    << " | Student |\n";
                totalUser++;
            }
        }
        std::cout << "- -------------------- - ------- -\n"
            << "                  Total student: " << totalUser << std::endl;
        break;
    }
}
