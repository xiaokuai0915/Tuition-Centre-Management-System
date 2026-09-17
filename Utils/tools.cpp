#include "tools.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>

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

        return input;
    }
}

void searchUI(const std::string& searchQuery, const std::vector<std::string>& searchData, int& page) {
    std::cout << "\033[2J\033[1;1H"
        << "- ------------------------------------------------------------------- -\n"
        << "| Search: " << std::left << std::setw(40) << searchQuery << "(ENTER to confirm) |\n"
        << "- ------------------------------------------------------------------- -\n";

    std::vector<std::string>matchLine;
    for (const std::string l : searchData) {
        if (searchQuery.empty()) {
            continue;
        }
        if (l.find(searchQuery) != std::string::npos) {
            matchLine.push_back(l);
        }
    }

    const int maxDisplay = 10;
    int totalMatch = matchLine.size();
    int totalPage = (totalMatch == 0) ? 1 : ceil((double)totalMatch / maxDisplay);
    if (page > totalPage) {
        page = totalPage;
    }
    else if (page < 1) {
        page = 1;
    }

    int start = (page - 1) * maxDisplay;
    int end = std::min(start + maxDisplay, totalMatch);

    for (int i = start; i < end; ++i) {
        std::cout << '\t' << matchLine[i] << '\n';
    }

    std::cout << "- ------------------------------------------------------------------- -\n"
        << "                                                            Page: " << page << '/' << totalPage;
}
std::string liveSearch(const std::vector<std::string>& searchData) {
    std::string searchQuery = "";
    int currentPage = 1;
    while (true) {
        searchUI(searchQuery, searchData, currentPage);
        int ch = _getch();

        if (ch == 13) { // Enter
            break;
        }
        else if (ch == 8) { //\b
            if (!searchQuery.empty()) {
                searchQuery.pop_back();
                currentPage = 1;
            }
        }
        else if (ch == 0 || ch == 224) {
            ch = _getch();
            if (ch == 75) {
                currentPage--;
            }
            else if (ch == 77) {
                currentPage++;
            }
        }
        else if (ch >= 32 && ch <= 126) {
            searchQuery += static_cast<char>(ch);
            currentPage = 1;
        }
    }
    std::cout << std::endl;
    return searchQuery;
}
