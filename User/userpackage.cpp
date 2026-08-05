#include "userpackage.h"
#include <iomanip>
#include <iostream>
#include <string>
#include "../Utils/tools.h"
#include "../Utils/storage.h"
#include "../Utils/models.h"

void userpackage(User& currentUser, const std::vector<Course>& allCourse) {
    bool running = true; //loop control
    while (running) {
        std::cout << "\n---View Course or Manage Course Section---\n========================================\n1.View All Courses\n2.Add Course to Package\n3.Review my package\n4.Remove Course from Package\n5.Modify my package\n6.Search Booking Record\n0.Back to User Menu\n========================================\nPlease choose one option by typing the number\n";
        int subChoice = intgerinputfilter("Enter your choice: "); //call the input filter function to get the input and check if it is valid)
        
        if (subChoice == -1) {
            std::cout << "Invalid input. Please try again!\n";
            continue;
        }

        if (subChoice == -2) {
            std::cout << "Input cannot be empty. Please enter a valid number.\n";
            continue;
        }

        if (subChoice == 1) {
            for (const auto& c : allCourse) { /* c is temporary variable, autolet it auto detect the type of variable of c for allCourse that store in vector
                                                 const to avoid is telling the compiler to read the file only(no edit to the file)    & direct pass by reference ( no need to copy anymore so faster)*/
                std::cout << '\n';
                std::cout << "ID= " << c.id << ". " << c.Name << " - $" << c.price << "\n"; //since all the variable type is auto sync so can direct output easily
            }
        }
        else if (subChoice == 2) {
            std::cout << "\n--- Add Course to Package ---\n";
            addCoursetoPackage(currentUser, allCourse);
        }

        else if (subChoice == 3) {
            myCourseSummary(currentUser, allCourse); 
        }

        else if (subChoice == 4) {
            removeCoursefromPackage(currentUser, allCourse); 
        }

        else if (subChoice == 5) {
            modifyUserPackage(currentUser, allCourse); 
        }

        else if (subChoice == 6) {
            searchBooking(); 
        }

        else if (subChoice == 0) {
            saveUserCourses(currentUser); //back up saving, save one more time to avoid accident
            running = false;    //end the loop by changing the bool variable on the top of this page
            std::cout << "Redirecting back to User Menu...\n";
            break;
        }
        else {
            std::cout << "Invalid option, try again.\n";
        }

    }
}

// 1. Add a course to the user's course package
void addCoursetoPackage(User& currentUser, const std::vector<Course>& allCourse) {
    int id = intgerinputfilter("Enter Course ID to add: "); // Ask user to input the course ID they want to add
    if (id == -1) {
        std::cout << "Invalid input. Please try again!\n";
        return;
    }

    if (id == -2) {
        std::cout << "Input cannot be empty. Please enter a valid number.\n";
        return;
    }

    bool alreadyExists = false; // Check if the course is already in the user's package
    for (const auto& c : currentUser.mypackage) {
        if (c.id == id) { alreadyExists = true; break; }
    }
    if (alreadyExists) {
        std::cout << "Error: Course (ID =" << id << ") already exists in your package\n";
    }
    else {
        bool found = false; // Flag to check if we can find this ID in all available courses
        for (const auto& c : allCourse) {
            if (c.id == id) { // Compare with all course IDs one by one
                currentUser.mypackage.push_back(c); // If found, push it back into the user's package vector
                std::cout << "\n------------------\n";
                std::cout << "Added " << c.Name << " to package!\n";
                found = true;

                recordUserAction(id, "ADD", 1, currentUser.username); // Log the action into the 1D/2D arrays and txt file
                saveUserCourses(currentUser); // Save immediately to prevent data loss if the program closes halfway
                std::cout << "[DEBUG] Saved the data into the text file.\n";
            }
        }
        if (!found) {
            std::cout << "Course not found in the available courses.\n"; // Finished checking but ID doesn't exist
        }
    }
}

// 2. Display all courses chosen by the current user and calculate the total fee
void myCourseSummary(User& currentUser, const std::vector<Course>& allCourse) {
    if (currentUser.mypackage.empty()) {
        std::cout << "Your package is currently empty.\n"; // If the package is empty, notify the user
    }

    std::cout << "\n--- My Package Summary ---\n";
    double total = 0;
    for (const auto& c : currentUser.mypackage) { // Loop through every course in the user's package
        std::cout << "- " << c.Name << " ($" << std::fixed << std::setprecision(2) << c.price << ")\n";
        total += c.price; // Accumulate the total price
    }
    std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << total << "\n"; // Print final total fee
}

// 3. Remove a course from the user's package
void removeCoursefromPackage(User& currentUser, const std::vector<Course>& allCourse) {
    if (currentUser.mypackage.empty()) {
        std::cout << "Your package is currently empty.\n";
    }

    std::cout << "\n--- Remove Course from Package ---\n";
    for (const auto& c : currentUser.mypackage) { // First, list out what courses the user currently has
        std::cout << "(ID=" << c.id << ") - " << c.Name << " ($" << std::fixed << std::setprecision(2) << c.price << ")\n";
    }
    int id = intgerinputfilter("Enter Course ID to remove: "); // Ask for the course ID to remove
    if (id == -1) {
        std::cout << "Invalid input. Please try again!\n";
        return;
    }

    if (id == -2) {
        std::cout << "Input cannot be empty. Please enter a valid number.\n";
        return;
    }

    bool found = false;
    for (auto it = currentUser.mypackage.begin(); it != currentUser.mypackage.end(); ++it) {
        if (it->id == id) { // Found the matching ID
            std::cout << "\nRemoved " << it->Name << " from package!\n";
            currentUser.mypackage.erase(it); // Erase it from the vector using an iterator

            recordUserAction(id, "REMOVE", 2, currentUser.username); // Log the remove action
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "\nCourse ID entered is not found in your package.\n";
    }
}

// 4. Modify the user package (remove a course first, then add a new one)
void modifyUserPackage(User& currentUser, const std::vector<Course>& allCourse) {
    if (currentUser.mypackage.empty()) {
        std::cout << "Your package is currently empty.\n";
    }

    std::cout << "\n--- Modify User Package ---\n";
    std::cout << "Current Courses in Package:\n";
    for (const auto& c : currentUser.mypackage) {
        std::cout << c.id << ". " << c.Name << " - $" << std::fixed << std::setprecision(2) << c.price << "\n";
    }

    // Stage 1: Execute the "Remove" operation
    while (true) {
        int removeId = intgerinputfilter("Enter ID to remove (or 0 to cancel/exit): ");
        if (removeId == 0) {
            std::cout << "Exiting modify package.\n";
            return;
        }

        if (removeId == -1) {
            std::cout << "Invalid input. Please try again!\n";
            continue;
        }

        if (removeId == -2) {
            std::cout << "Input cannot be empty. Please enter a valid number.\n";
            continue;
        }

        bool found = false;
        for (auto it = currentUser.mypackage.begin(); it != currentUser.mypackage.end(); ++it) {
            if (it->id == removeId) {
                std::cout << "Removed " << it->Name << " from package.\n";
                currentUser.mypackage.erase(it); // Successfully erased from package

                recordUserAction(removeId, "MODIFY_REMOVE", 3, currentUser.username); // Log the modify-remove action
                found = true;
                break;
            }
        }

        if (found) {
            break; // Break out of this loop if successfully removed, then proceed to the add stage
        }

        if (!found) {
            std::cout << "Course ID not found in your package.\n";
            continue; // Loop back to let the user try again if ID wasn't found
        }
    }

    // Stage 2: Execute the "Add" operation
    while (true) {
        int id = intgerinputfilter("Enter Course ID to add (or 0 to cancel/exit): ");
        if (id == 0) {
            std::cout << "Exiting modify package.\n";
            return;
        }

        if (id == -1) {
            std::cout << "Invalid input. Please try again!\n";
            continue;
        }

        if (id == -2) {
            std::cout << "Input cannot be empty. Please enter a valid number.\n";
            continue;
        }

        bool alreadyExists = false;
        for (const auto& c : currentUser.mypackage) {
            if (c.id == id) { alreadyExists = true; break; }
        }

        if (alreadyExists) {
            std::cout << "Error: Course (ID =" << id << ") already exists in your package\n";
            continue;
        }

        bool foundCourse = false;
        for (const auto& c : allCourse) {
            if (c.id == id) {
                currentUser.mypackage.push_back(c); // Push the new course in
                std::cout << "\n------------------\n";
                std::cout << "Added " << c.Name << " to package!\n";

                recordUserAction(id, "MODIFY_ADD", 3, currentUser.username); // Log the modify-add action
                saveUserCourses(currentUser); // Save to the text file instantly
                std::cout << "[DEBUG] Saved the data into the text file.\n";
                foundCourse = true;
                break;
            }
        }
        if (foundCourse) {
            break; // Break out of the entire modification loop once added successfully
        }

        if (!foundCourse) {
            std::cout << "Course not found in the available courses.\n";
            continue;
        }
    }
}