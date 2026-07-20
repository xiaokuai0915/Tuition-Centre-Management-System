#include "adminUserFunctions.h"

void addNewUser() {
    std::ofstream file("user.txt", std::ios::app);
    std::string username, password;
    int role;

    std::cout << "Enter username: "; std::cin >> username;
    std::cout << "Enter password: "; std::cin >> password;
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

    file << username << " " << password << " " << role << std::endl; //Enter data to file
    file.close();
    std::cout << "User added successfully.\n";
}

void searchUser() {
    std::ifstream file("user.txt");
    std::string username, password;
    int role;

    std::string searchUser;
    std::cout << "Enter username to search: "; std::cin >> searchUser;

    bool found = false;
    while (file >> username >> password >> role) { //read file line by line until it reaches the end
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
    file.close();
}

void updateUser() {
    std::ifstream file("user.txt");
    std::string username, password;
    int role;
    std::ofstream temp("temp.txt");

    std::string searchUser;
    std::cout << "Enter username to update: "; std::cin >> searchUser;

    bool found = false;
    while (file >> username >> password >> role) {
        if (username == searchUser) {
            std::cout << "Enter new name: "; std::cin >> username;
            std::cout << "Enter new password: "; std::cin >> password;
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

    file.close();
    temp.close();

    remove("user.txt");
    if (rename("temp.txt", "user.txt") != 0) { //rename will change temp.txt to user.txt and return 0, !=0 checks if it returns a non 0 value
        std::cout << "Update failed.\n";
    }

    std::cout << (found ? "User updated.\n" : "User not found.\n");
}

void deleteUser() {
    std::ifstream file("user.txt");
    std::string username, password;
    int role;
    std::ofstream temp("temp.txt");

    std::string deleteUser;
    std::cout << "Enter username to delete: "; std::cin >> deleteUser;

    bool found = false;
    while (file >> username >> password >> role) {
        if (username == deleteUser) {
            found = true;
            continue; //skips copying this line of data, achieving a delete function
        }
        temp << username << " " << password << " " << role << std::endl;
    }

    file.close();
    temp.close();

    remove("user.txt");
    if (rename("temp.txt", "user.txt") != 0) {
        std::cout << "Update failed.\n";
    }

    std::cout << (found ? "User deleted.\n" : "User not found.\n");
}
