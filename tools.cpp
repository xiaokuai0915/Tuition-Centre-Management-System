#include "tools.h"

int intgerinputfilter(const std::string& prompt) {
	int val;
	while (true) {
		std::cout << prompt;
		if (std::cin >> val) {
			char nextChar = std::cin.peek();
			if (nextChar == '\n' || nextChar == ' ' || nextChar == EOF) {
				return val; // valid input, exit the loop
			}
		}
		std::cin.clear(); // clear the error state of cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the line 
		return -1; //this doesnt mean it is no error, i just want it to sync as the normal input error if user type only integer but wrong
	}
}
