#include "adminUserFunctions.h"
#include "../Utils/tools.h"
#include "../Utils/models.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

// 1.add
void addNewUser() {
    std::ofstream outfile("Data/user.txt", std::ios::app);
    std::string username, password;
    int role, ID;

    bool checkname;
    do {
        checkname = false;
        username = stringinputfilter("Create username (Enter 0 to cancel registration) : "); //call the input filter function to get the input and check if it is valid

        if (username == "0") {
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

                std::cout << "[DEBUG] Comparing " << username << " with " << fileusername << "\n"; //same reason as login, for debugging purpose
                if (username == fileusername) {
                    std::cout << "Username already exist, please use another username.\n";
                    checkname = true;
                    break;
                }
            }
        }
    } while (checkname);
    password = stringinputfilter("Create password: ");
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
    do {
        role = intgerinputfilter("Enter role (Teacher=1, Student=0): ");
        if (role == -1) { //if -1 is returned, it means a !int value is entered
            std::cout << "Invalid input. Please try again!\n";
        }
        else if (role == -2) { //if -2 is returned, it means an empty input was entered
            std::cout << "Input cannot be empty. Please enter a valid number.\n";
        }
        else if (role == 0) {
            ID = lineCount[0];
            break;
        }
        else if(role == 1) {
            ID = lineCount[1];
            break;
        }
        else {
            std::cout << "Invalid input. Please try again!\n";
        }
    } while (true);


    outfile << (std::to_string(role) == "0" ? "S" : "T") << std::setfill('0') << std::setw(3) << ID << ","
        << username << "," << password << "," << role << std::endl; //Enter data to file
    outfile.close();
    std::cout << "User added successfully.\n";
}

// 2. update
void updateUser(User& currentUser) {
    std::ifstream infile("Data/user.txt");
    std::string line;
    std::vector<User> userList;

    std::string searchUser = stringinputfilter("Enter username to update: ");
    if (searchUser == currentUser.username) { //don't allow to edit logged in user
        std::cout << "Cannot update logged in user.\n";
        return;
    }

    bool found = false;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string fileID, fileusername, filepassword, filerole;

        if (std::getline(ss, fileID, ',')) {
            User u;
            u.ID = fileID;
            if (std::getline(ss, fileusername, ',') &&
                std::getline(ss, filepassword, ',') &&
                std::getline(ss, filerole, ',')) {

                u.username = fileusername;
                u.password = filepassword;
                u.role = std::stoi(filerole);
            }
            else {
                u.username = "";
                u.password = "";
                u.role = 2;
            }
            userList.push_back(u);
        }
    }
    infile.close();

    User* targetUser = nullptr;// holds memory address
    for (User& u : userList) {
        if (u.username == searchUser) {
            targetUser = &u;
            break;
        }
    }

    if (targetUser != nullptr) { // not null pointer
        std::cout << "User details:\n" << std::left
            << "- --------- - -------------------------------------------------- -\n"
            << "| ID        | " << std::setw(50) << (*targetUser).ID << " |\n"
            << "- --------- - -------------------------------------------------- -\n"
            << "| Username  | " << std::setw(50) << (*targetUser).username << " |\n"
            << "- --------- - -------------------------------------------------- -\n"
            << "| Password  | " << std::setw(50) << (*targetUser).password << " |\n"
            << "- --------- - -------------------------------------------------- -\n"
            << "| Role      | " << std::setw(50) << ((*targetUser).role == 1 ? "Teacher" : "Student") << " |\n"
            << "- --------- - -------------------------------------------------- -\n";
        bool checkname;
        do {
            checkname = false;
            std::string newUsername = stringinputfilter("Enter new username (Enter 0 to cancel) : ");

            if (newUsername == "0") {
                std::cout << "Registration cancelled.\n";
                return;
            }

            for (const User& u : userList) {
                if (u.username == newUsername && newUsername != searchUser) {
                    std::cout << "Username already exists, please use another username.\n";
                    checkname = true;
                    break;
                }
            }
            if (!checkname) {
                targetUser->username = newUsername;
            }
        } while (checkname);
        targetUser->password = stringinputfilter("Enter new password: ");
        do {
            targetUser->role = intgerinputfilter("Enter new role (Teacher=1, Student=0): ");
            if (targetUser->role == -1) { //if -1 is returned, it means a !int value is entered
                std::cout << "Invalid input. Please try again!\n";
            }
            else if (targetUser->role == -2) { //if -2 is returned, it means an empty input was entered
                std::cout << "Input cannot be empty. Please enter a valid number.\n";
            }
            else if (targetUser->role == 0 || targetUser->role == 1) { //role only accepts 0 and 1
                break;
            }
            else {
                std::cout << "Invalid input. Please try again!\n";
            }
        } while (true);

        std::ofstream outfile("Data/user.txt");
        for (const User& u : userList) {
            outfile << u.ID << "," << u.username << "," << u.password << ","
                << (std::to_string(u.role) == "2" ? "" : std::to_string(u.role)) << "\n";
        }
        outfile.close();
        std::cout << "User updated successfully.\n";
    }
    else {
        std::cout << "User not found.\n";
    }
}

// 3. delete
void deleteUser(User& currentUser) {
    std::ifstream infile("Data/user.txt");
    std::string line;
    std::vector<User> userList;

    std::string searchUser = stringinputfilter("Enter username to delete: ");
    if (searchUser == currentUser.username) { //don't allow to edit logged in user
        std::cout << "Cannot update logged in user.\n";
        return;
    }

    bool found = false;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string fileID, fileusername, filepassword, filerole;

        if (std::getline(ss, fileID, ',')) {
            User u;
            u.ID = fileID;
            if (std::getline(ss, fileusername, ',') &&
                std::getline(ss, filepassword, ',') &&
                std::getline(ss, filerole, ',')) {

                u.username = fileusername;
                u.password = filepassword;
                u.role = std::stoi(filerole);
            }
            else {
                u.username = "";
                u.password = "";
                u.role = 2;
            }
            userList.push_back(u);
        }
    }
    infile.close();

    User* targetUser = nullptr;// holds memory address
    for (User& u : userList) {
        if (u.username == searchUser) {
            targetUser = &u;
            break;
        }
    }

    if (targetUser != nullptr) { // not null pointer
        std::cout << "User details:\n" << std::left
            << "- --------- - -------------------------------------------------- -\n"
            << "| ID        | " << std::setw(50) << (*targetUser).ID << " |\n"
            << "- --------- - -------------------------------------------------- -\n"
            << "| Username  | " << std::setw(50) << (*targetUser).username << " |\n"
            << "- --------- - -------------------------------------------------- -\n"
            << "| Password  | " << std::setw(50) << (*targetUser).password << " |\n"
            << "- --------- - -------------------------------------------------- -\n"
            << "| Role      | " << std::setw(50) << ((*targetUser).role == 1 ? "Teacher" : "Student") << " |\n"
            << "- --------- - -------------------------------------------------- -\n";
        do {
            int deleteconfirm = intgerinputfilter("Delete? (0=NO, 1=YES): ");
            if (deleteconfirm == -1) { //if -1 is returned, it means a !int value is entered
                std::cout << "Invalid input. Please try again!\n";
            }
            else if (deleteconfirm == -2) { //if -2 is returned, it means an empty input was entered
                std::cout << "Input cannot be empty. Please enter a valid number.\n";
            }
            else if (deleteconfirm == 0) {
                std::cout << "Deletion cancelled.\n";
                return;
            }
            else if (deleteconfirm == 1) {
                targetUser->username = "";
                targetUser->password = "";
                targetUser->role = 2;
                break;
            }
            else {
                std::cout << "Invalid input. Please try again!\n";
            }
        } while (true);

        std::ofstream outfile("Data/user.txt");
        for (const User& u : userList) {
            outfile << u.ID << "," << u.username << "," << u.password << "," << (std::to_string(u.role) == "2" ? "" : std::to_string(u.role)) << "\n";
        }
        outfile.close();
        std::cout << "User deleted successfully.\n";
    }
    else {
        std::cout << "User not found.\n";
    }
}

// 4. search
void searchUser() {
    std::string searchUser = " ";
    std::ifstream infile("Data/user.txt");
    std::string line;
    std::vector<std::string> searchData;
    std::vector<User> userList;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string fileID, fileusername, filepassword, filerole;

        if (std::getline(ss, fileID, ',') &&//when reach , then take the thing before , and put it into variable to 分类
            std::getline(ss, fileusername, ',') &&//&& means if the stuff is correct and can be read then continue to next row
            std::getline(ss, filepassword, ',') &&
            std::getline(ss, filerole, ',')) {

            User u;
            u.ID = fileID;
            u.username = fileusername;
            u.password = filepassword;
            u.role = std::stoi(filerole);
            userList.push_back(u);

            searchData.push_back(fileusername);
        }
    }
    infile.close();

    searchUser = liveSearch(searchData);
    if (searchUser == "SEARCHCANCEL") {
        std::cout << "Search cancelled.\n";
        return;
    }

    for (const User& u : userList) {
        if (searchUser == u.username) {
            std::cout << "User found:\n" << std::left
                << "- --------- - -------------------------------------------------- -\n"
                << "| ID        | " << std::setw(50) << u.ID << " |\n"
                << "- --------- - -------------------------------------------------- -\n"
                << "| Username  | " << std::setw(50) << u.username << " |\n"
                << "- --------- - -------------------------------------------------- -\n"
                << "| Password  | " << std::setw(50) << u.password << " |\n"
                << "- --------- - -------------------------------------------------- -\n"
                << "| Role      | " << std::setw(50) << (u.role == 1 ? "Teacher" : "Student") << " |\n"
                << "- --------- - -------------------------------------------------- -\n";
            return;
        }
    }
    std::cout << "User not found.\n";
}

// 5. display
void displayUser() {
    std::ifstream infile("Data/user.txt");
    std::string line;
    std::vector<User> userList;

    std::cout << std::setfill(' ');
    std::cout << "\nChoose one option by typing number:\n"
        << "1. Display all user\n"
        << "2. Display all teacher\n"
        << "3. Display all student\n"
        << "0. Exit\n";
    int displayChoice = 0;
    do {
        displayChoice = intgerinputfilter("Enter your choice(0-3): ");
        if (displayChoice == -2) { //if -2 is returned, it means an empty input was entered
            std::cout << "Input cannot be empty. Please enter a valid number.\n";
        }
        else if (displayChoice == -1 || !(displayChoice >= 0 && displayChoice <= 3)) { //if -1 is returned, it means a !int value is entered, also checks if displayChoice is 0,1,2,3
            std::cout << "Invalid input. Please try again!\n";
        }
        else if (displayChoice == 0) { //return back to menu
            return;
        }
        else {
            break;
        }
    } while (true);

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string fileID, fileusername, filepassword, filerole;

        if (std::getline(ss, fileID, ',') &&
            std::getline(ss, fileusername, ',') &&
            std::getline(ss, filepassword, ',') &&
            std::getline(ss, filerole, ',')) {

            User u;
            u.ID = fileID;
            u.username = fileusername;
            u.password = filepassword;
            u.role = std::stoi(filerole);
            userList.push_back(u);
        }
    }
    infile.close();

    std::cout << "\nSort by:\n"
        << "1. ID Ascending order\n"
        << "2. ID Descending order\n"
        << "3. Name Ascending order\n"
        << "4. Name Descending order\n";
    int sortChoice = 0; //ask for if need to sort according to what
    do {
        sortChoice = intgerinputfilter("Enter your choice(1-3): ");
        if (sortChoice == -2) { //if -2 is returned, it means an empty input was entered
            std::cout << "Input cannot be empty. Please enter a valid number.\n";
        }
        else if (sortChoice == -1 || !(sortChoice >= 1 && sortChoice <= 4)) { //if -1 is returned, it means a !int value is entered, also checks if sortChoice is 1,2,3
            std::cout << "Invalid input. Please try again!\n";
        }
        else {
            break;
        }
    } while (true);

    if (sortChoice >= 2 && sortChoice <= 4) {
        for (int i = 0; i < userList.size() - 1; ++i) { //bubble sort
            for (int j = 0; j < userList.size() - i - 1; ++j) {
                if (sortChoice == 2) {
                    if (userList[j].ID < userList[j + 1].ID) {
                        User temp = userList[j];
                        userList[j] = userList[j + 1];
                        userList[j + 1] = temp;
                    }
                }
                else {
                    std::string lowerCaseName1 = userList[j].username; //get the username on the current index
                    std::string lowerCaseName2 = userList[j + 1].username; //get the username on the next index
                    for (char& c : lowerCaseName1) { //convert current into lowercase char by char
                        c = tolower(c);
                    }
                    for (char& c : lowerCaseName2) { //convert next into lowercase char by char
                        c = tolower(c);
                    }
                    if (sortChoice == 3) {
                        if (lowerCaseName1 > lowerCaseName2) { //if current's ASCII value is bigger than next's, then swap place
                            User temp = userList[j];
                            userList[j] = userList[j + 1];
                            userList[j + 1] = temp;
                        }
                    }
                    else if (sortChoice == 4) {
                        if (lowerCaseName1 < lowerCaseName2) { //if current's ASCII value is smaller than next's, then swap place
                            User temp = userList[j];
                            userList[j] = userList[j + 1];
                            userList[j + 1] = temp;
                        }
                    }
                }
            }
        }
    }

    int totalUser = 0;
    std::cout<< "\n"
        << "- ---- - -------------------------------------------------- - ------- -\n"
        << "| ID   | Username                                           | Role    |\n"
        << "- ---- - -------------------------------------------------- - ------- -\n";

    for (int i = 0; i < userList.size(); i++) {
        bool display = false;
        switch (displayChoice) {
        case 1:
            display = true;
            break;
        case 2:
            display = (userList[i].role == 1);
            break;
        case 3:
            display = (userList[i].role == 0);
            break;
        }
        if (display) {
            std::cout << std::left
                <<  "| " << std::setw(4) << userList[i].ID
                << " | " << std::setw(50) << userList[i].username
                << " | " << (userList[i].role == 1 ? "Teacher" : "Student") << " |\n";
            totalUser++;
        }
    }
    std::cout << "- ---- - -------------------------------------------------- - ------- -\n";
}

// menu
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
        std::cout << std::setfill('=') << std::setw(50) << "" << '\n' << std::setfill(' ');

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
