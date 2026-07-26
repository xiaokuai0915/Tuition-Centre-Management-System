#include "tools.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <string>

int intgerinputfilter(const std::string& prompt) { // to cout the prompt and get the input from user, then check if it is valid
    std::cin.clear();
	std::string input; 
    while (true) {
        std::cout << prompt;

		if (!std::getline(std::cin, input)) { // read whole line of input and check if it is valid, no matter it is just a space or empty, it will return -2, if the input is not valid(not integer), it will return -1
            return -1;
        }

		if (input.empty()) { //if input is empty, return -2 to indicate that the input is empty
            return -2;
        }

		std::stringstream ss(input); //use stringstream to convert the input string to integer
        int val;
        char extra;

		if (ss >> val && !(ss >> extra)) { //fetch integer from the stringstream and check if there is any extra character after the integer, if yes, it will return -1 to indicate that the input is not valid
            return val;
        }
        else {
			return -1; //return -1 to indicate that the input is not valid
        }
    }
}

std::string stringinputfilter(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cin.clear();
		std::cout << prompt;
        if (!std::getline(std::cin, input)) {
            return ""; // Return empty string on input failure
        }

		if (input == "0") {
			return "0"; // Return 0 if the user inputs "0"
		}
        
        if (input.empty()) {
            std::cout << "Input cannot be empty! Please try again.\n";
            continue;
        }

        if (input.find(' ') != std::string::npos) {
            std::cout << "Input cannot contain spaces! Please try again.\n";
            continue;
        }

        return input;

    }
}
