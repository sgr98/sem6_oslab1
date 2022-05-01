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
	string destPath = "./marks_download.txt";

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
            vector<pair<string, vector<float>>> allStudentInstructorMarks = getAllStudentInstructorMarks(instructor_and_files);
			string asim_string = getAllStudentInstructorMarksString(instructor_and_files, allStudentInstructorMarks);
			cout << asim_string << endl;
		}
		else if(c == 2) {
			downloadAllStudentsInstructorMarks(destPath, instructor_and_files);
		}
	}
}