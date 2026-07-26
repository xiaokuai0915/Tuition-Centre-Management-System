#include <iomanip>
#include <string>
#include <vector> 
#include <algorithm>
#include "../Utils/models.h"
#include "../Utils/menu.h"
#include "../Utils/tools.h"
#include "../Admin/report.h"

void showReportModule() {

	bool running = true;  //loop the menu
	int reportchoice;
	while (running) {

		std::cout << "\n================================\n";
		std::cout << "|Admin Portal: Reporting module|\n";
		std::cout << "================================\n\n";
		std::cout << "Choose an option Choose one option by typing number:\n1. Generate Summary Report\n2. Generate Detailed Report\n3. Calculate Statistic\n4. Sort Record\n5. Display Analysis\n0. Back to Admin Menu\n";

		reportchoice = intgerinputfilter("Enter your choice(0-5): ");
		if (reportchoice == -1) {
			std::cout << "Invalid input! Please enter a valid number.";
			continue;
		}

		if (reportchoice == -2) {
			std::cout << "Input cannot be empty! Please enter a valid number.";
			continue;
		}
		//use switch to choose the function
		switch (reportchoice) {
		case 1:
			generateSummaryReport();
			break;
		case 2:
			generateDetailReport();
			break;
		case 3:
			calculateStatistic();
			break;
		case 4:
			sortRecord();
			break;
		case 5:
			displayAnalysis();
			break;
		case 0:
			running = false;  //end loop
			std::cout << "Reverting back to admin menu......\n\n";
			break;
		default:
			std::cout << "Invalid input. Please enter a valid number.\n";
			break;
		}
	
	}	
}
//case 1: generate summary report
void generateSummaryReport(){
	std::vector<User> allusers;
	readUserandCoursefile(allusers);   //load the users files from the header、
		
	size_t totalusers = allusers.size();   //size() tells compiler to go and count how many users they are in the allusers
	if (totalusers == 0) {
		std::cout << "System ERROR. No user record found\n";
		return;
	}
	size_t totalenrollments = 0;    //total amount of course taken by student
	int zeroCourseStudent = 0;   //student who doesn't has any course taken

	for (const auto user : allusers) {   //read the current user from the text file 
		size_t studentCourseCount = user.mypackage.size();  //count the user course taken and save into the studentCourseCount
		totalenrollments += studentCourseCount;    //totalenrollments = totalenrollments + studentCourseCount
		if (studentCourseCount == 0) {   //if compiler found out that this user has zero course, then the user will be save into here
			zeroCourseStudent++;
		}
	}
	
	//summary report menu
	//I'm not using setw and setfill due to the weird mechanic from it when I output my menu, so I will just use std::string to act as setw and setfill
	std::cout << '\n' << std::string(78, '=') << "\n";
	std::cout << std::string(30, ' ') << "Summary Report\n";
	std::cout << std::string(78, '=') << '\n';
	std::cout << "Total student registered: " << std::string(42, '.') << totalusers << " students\n";
	std::cout << "Total course registered: " << std::string(43, '.') << totalenrollments << " courses\n";
	std::cout << "[WARNING] Currently there are " << zeroCourseStudent << " students that doesn't registered any courses!\n";
	std::cout << std::string(78, '=') << "\n";
}

//case 2: generate detail report
void generateDetailReport() {
	std::vector<User> allusers;   //declare the allusers
	readUserandCoursefile(allusers);    //read file from header

	if (allusers.size() == 0) {
		std::cout << "System ERROR. No user record found.\n";  //error message if there is no txt file
		return;
	}

	std::string searchUser;
	searchUser = stringinputfilter("Enter username to search: ");   //input filter
	bool founduser = false;

	for (const auto& user : allusers) {
		if (user.username == searchUser) {
			founduser = true;

			//detail report menu
			if (user.mypackage.empty()) {   //if the course txt file is empty then give error message
				std::cout << "\nERROR. This student has not registered any course.\n";  //when they is no course recorded in this user, return an error message
			}
			else {  //a loop for the compiler to load the specific user's course one by one
				for (size_t j = 0; j < user.mypackage.size(); ++j) {
					//detail report menu
					std::cout << '\n' << std::string(78, '=') << "\n";
					std::cout << std::string(30, ' ') << "Detailed Report\n";
					std::cout << std::string(78, '=') << '\n';
					std::cout << "Name: " << user.username << '\n';
					std::cout << std::string(78,'=') << '\n';
					std::cout << "[Class Enrolled]\n";
					std::cout << "Total course taken: " << user.mypackage.size() << '\n';
					std::cout << std::string(78, '-') << '\n';
					std::cout << "Course ID" << std::string(13, ' ') << "Course Name" << std::string(21, ' ') << "Price (RM)\n";
					std::cout << std::string(78, '-') << '\n';
					std::cout << " " << user.mypackage[j].id << std::string(20, ' ') << user.mypackage[j].Name << std::string(21, ' ') << "RM " << std::fixed << std::setprecision(2) << user.mypackage[j].price << '\n';
					std::cout << std::string(78, '-') << '\n';
					break;
				}
			}
			if (!founduser) {
				std::cout << "User not found!";  //if the user not found, return error message and end loop
				break;
			}
		}
	}

}

//case 3 
void calculateStatistic() {
	std::vector<User> allusers;
	readUserandCoursefile(allusers);

	size_t totalusers = allusers.size();   //size() tells compiler to go and count how many users they are in the allusers
	if (totalusers == 0) {
		std::cout << "System ERROR. No user record found.\n";
		return;
	}

	size_t totalenrollment = 0;
	int inactivestudent = 0;

	for (const auto user : allusers) {   //take the data from the txt file and put in here to calculate
		size_t courseCount = user.mypackage.size();  
		totalenrollment += courseCount;   //totalenrollment = totalenrollment + coursecount, when coursecount = 1, then total is 1, if another user have 2, then is 1+2=3 for total enrollment
		if (courseCount == 0) {
			inactivestudent++;  //if the user didnt register any course, it will direct to here
		}
	}
	double averageCourseperStudent = static_cast<double>(totalenrollment) / totalusers;   //static_cast is used to get even accurate 小数点
	double inactiveStudentRate = static_cast<double>(inactivestudent) / totalusers * 100;  //make it into percentage
	
	//calculate statistic menu
	std::cout << '\n' << std::string(78, '=') << '\n';
	std::cout << std::string(30, ' ') << "Calculate Statistic\n";
	std::cout << std::string(78, '=') << '\n';
	std::cout << "Academic Metrics" << std::string(40, ' ') << "Current Data\n";
	std::cout << std::string(78, '-') << '\n';
	std::cout << "Total Students: " << std::string(40, ' ') << totalusers << " students";
	std::cout << "\nTotal Enrollments: " << std::string(37, ' ') << totalenrollment << " students";
	std::cout << "\nAverage Courses Taken per Student: " << std::string(21, ' ') << std::fixed << std::setprecision(1) << averageCourseperStudent << " per students";
	std::cout << "\nTotal Inactive Students: " << std::string(31, ' ') << inactivestudent << " students";
	std::cout << "\nTotal Inactive Students Rate: " << std::string(26, ' ') << std::fixed << std::setprecision(1) << inactiveStudentRate << " %\n";
	std::cout << std::string(78, '-') << '\n';
}

//case 4: sort students'name 
void sortRecord() {
	std::vector<User> allusers;
	readUserandCoursefile(allusers);  //load the files from the header

	//check if the txt is create
	if (allusers.size() == 0) {
		std::cout << "System ERROR. No user record found.\n";
		return;
	}

	//selection sort
	size_t n = allusers.size();
	//outer loop: to decide who should be the first, second, third... etc
	for (size_t i = 0; i < n - 1; i++) {
		size_t min_idx = i; //it means that this is the first person who start from alphabet A, then it will put in the first place
		//inner loop: continue to find other name that is more forward than the previous i 
		for (size_t j = i + 1; j < n; j++) {
			if (allusers[j].username < allusers[min_idx].username) {
				min_idx = j;    //record the person who has closer alphabet
			}
		}
		if (min_idx != i) {
			std::swap(allusers[i], allusers [min_idx] ); //if the smaller number is not i, then swap place
		}
	}

	//the sort menu
	std::cout << '\n' << std::string(78, '=') << '\n';
	std::cout << std::string(30, ' ') << "Sort Menu By Username\n";
	std::cout << std::string(78, '=') << '\n';
	std::cout << "No.\tStudent\t\tCourse Taken\n";
	std::cout << std::string(78, '-') << '\n';

	for (size_t i = 0; i < n; i++) {  //compiler will always start from 0,1,2... This command can force the compiler to start from 1,2,3
		std::cout << " " << (i + 1) << "\t" << allusers[i].username << "\t\t" << allusers [i] .mypackage.size() << " courses" << '\n';
		std::cout << std::string(78, '-') << '\n';
	}
}

//case 5: display analysis
void displayAnalysis() {
	std::vector<User> allusers;
	readUserandCoursefile(allusers);

	size_t totalusers = allusers.size();   //size() tells compiler to go and count how many users they are in the allusers
	if (totalusers == 0) {
		std::cout << "System ERROR. No user record found.\n";
		return;
	}

	//menu
	std::cout << '\n' << std::string(80, '=') << '\n';
	std::cout << std::string(26, ' ') << "Tuition Centre Analysis\n";
	std::cout << std::string(80, '=') << '\n';
	std::cout << "Diagnostic Indicator 1: Zero Course Enrollment Attrtion Risk\n";
	bool hasriskstudent = false;

	for (const auto& user : allusers) {
		if (user.mypackage.empty()) {   //if course txt is empty for this user, output the warning message
			std::cout << "[WARNING] Student " << user.username << " currently have 0 courses registered!\n";
			hasriskstudent = true;
		}
	}
	if (hasriskstudent) {  //give suggestion for the current user if its true
		std::cout << "\nSYSTEM RECOMMENDATION: Front-desk course consultants should call the\n";
		std::cout << "student's parents immediately to assist in completing course enrollment.\n";
	}
	else { //if its false
		std::cout << "Good! All students have successfully registered their courses, zero loss risk.\n";
	}
	std::cout << std::string(80, '-') << '\n';

	std::cout << "Diagnostic Indicator 2: Academic Pressure for elite students\n";
	bool overloadstudent = false;

	for (const auto& user : allusers) {
		if (user.mypackage.size() >= 3) {  //if the course registered by the current user is more than equal to 3, give warning message
			std::cout << "[WARNING] Student " << overloadstudent << " has more or equal to 3 courses registered!\n";
			overloadstudent = true;
		}
	}
	if (overloadstudent) {  //if its true, give suggestions
		std::cout << "\nSYSTEM RECOMMENDATION: Instructors of each subject should pay closer attention\n";
		std::cout << "to the follow up of the above student to prevent excessive academic pressure.\n";
	}
	else {  //if its false
		std::cout << "Status Normal : No student is currently enrolled in more than three courses; the academic workload is balanced.\n";
	}
	std::cout << std::string(80, '-') << '\n';
}