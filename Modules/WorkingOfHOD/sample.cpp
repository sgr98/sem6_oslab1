#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <limits>

#include "./hod.h"

using namespace std;

// Compilation: g++ sample.cpp hod.cpp ./../InstructorMarksList/instructor_marks_list.cpp -o sample

int main() {
	pair<string, string> instructor_file;
	vector<pair<string, string>> instructor_and_files;

	instructor_file.first = "instructor_1";
	instructor_file.second = "./instructor_paths/instructor_1/";
	instructor_and_files.push_back(instructor_file);

	instructor_file.first = "instructor_2";
	instructor_file.second = "./instructor_paths/instructor_2/";
	instructor_and_files.push_back(instructor_file);

    instructor_file.first = "instructor_3";
	instructor_file.second = "./instructor_paths/instructor_3/";
	instructor_and_files.push_back(instructor_file);

	while(true) {
		cout << "------------------------------------------\n";
		cout << "0: Exit" << endl;
		cout << "1: View all marks of students" << endl;
		cout << "2: Download marks" << endl;
		cout << "------------------------------------------\n";

		int c;
		cin >> c;
		if(c == 0)
			break;
		else if(c == 1) {
            getAllStudentInstructorMarks(instructor_and_files);
		}
		else if(c == 2) {

		}
	}
}