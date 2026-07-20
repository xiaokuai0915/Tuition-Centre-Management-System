#include "userpackage.h"
#include <iomanip>
#include <iostream>
#include "tools.h"
#include "storage.h"

void addCoursetoPackage(User& currentUser, const std::vector<Course>& allCourse) {
    int id = intgerinputfilter("Enter Course ID to add: ");
	if (id == -1) {
		std::cout << "Invalid input. Please try again!\n";
		return;
	}
    if (id == -2) {
        std::cout << "Input cannot be empty. Please enter a valid number.\n";
        return;
    }

	bool alreadyExists = false;
	for (const auto& c : currentUser.mypackage) {
		if (c.id == id) { alreadyExists = true; break; }
	}
    if (alreadyExists) {
		std::cout << "Error: Course (ID =" << id << ") already exists in your package\n";
        return;
    }
    else {
		bool found = false; //detect course found or not
		for (const auto& c : allCourse) {
			if (c.id == id) { //search for subject by check id one by one
				currentUser.mypackage.push_back(c); //save(push back) to mypackage that in storage.cpp
				std::cout << "\n------------------\n";
				std::cout << "Added " << c.Name << " to package!\n";
				found = true;
				saveUserCourses(currentUser); //save immediately to avoid course not save when program is close during half way
				std::cout << "[DEBUG] Saved the data into the text file.\n";
				return;
			}
		}
		if (!found) {
			std::cout << "Course not found in the available courses.\n";
            return;
		}
    }
}

void myCourseSummary(User& currentUser, const std::vector<Course>& allCourse) {
    if (currentUser.mypackage.empty()) {
        std::cout << "Your package is currently empty.\n";
        return;
    }
	std::cout << "\n--- My Package Summary ---\n";
	double total = 0;
	for (const auto& c : currentUser.mypackage) { //read all user course variable
		std::cout << "- " << c.Name << " ($" << std::fixed << std::setprecision(2) << c.price << ")\n";
		total += c.price;
	}
	std::cout << "Total Fee: $" << std::fixed << std::setprecision(2) << total << "\n";
}

void removeCoursefromPackage(User& currentUser, const std::vector<Course>& allCourse) {
	if (currentUser.mypackage.empty()) {
		std::cout << "Your package is currently empty.\n";
		return;
	}
	std::cout << "\n--- Remove Course from Package ---\n";
	for (const auto& c : currentUser.mypackage) { //read all user course variable
		std::cout << "(ID=" << c.id << ") - " << c.Name << " ($" << std::fixed << std::setprecision(2) << c.price << ")\n";
	}
	int id = intgerinputfilter("Enter Course ID to remove: ");
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
        if (it->id == id) {
            std::cout << "\nRemoved " << it->Name << " from package!\n";
            currentUser.mypackage.erase(it);
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "\nCourse ID entered is not found in your package.\n";
        return;
    }
}

void modifyUserPackage(User& currentUser, const std::vector<Course>& allCourse) {
    if (currentUser.mypackage.empty()) {
        std::cout << "Your package is currently empty.\n";
        return;
    }

    std::cout << "\n--- Modify User Package ---\n";
    std::cout << "Current Courses in Package:\n";
    for (const auto& c : currentUser.mypackage) {
        std::cout << c.id << ". " << c.Name << " - $" << std::fixed << std::setprecision(2) << c.price << "\n";
    }

		// remove stage
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
                currentUser.mypackage.erase(it);
                found = true;
                break;
            }
        }
        
        if (found) {
            break; // Exit the loop if a course was successfully removed then enter add stage
        }
        
        if (!found) {
            std::cout << "Course ID not found in your package.\n";
            continue; // If the course ID is not found, send user back to the start of the loop to try again
        }
    }

		// add stage
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
                currentUser.mypackage.push_back(c);
                std::cout << "\n------------------\n";
                std::cout << "Added " << c.Name << " to package!\n";
                saveUserCourses(currentUser);
                std::cout << "[DEBUG] Saved the data into the text file.\n";
                foundCourse = true;
                break;
            }
        }
		if (foundCourse) {
			break; // Exit the loop if a course was successfully added
		}
        
        if (!foundCourse) {
        std::cout << "Course not found in the available courses.\n";
        continue;
        }
    }
}