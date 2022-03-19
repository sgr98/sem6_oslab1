#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include "student.h"

int main() {
	string fileName = "./sample_student_courses.txt";
	string newFile = "./target.txt";
	string course1 = "Computer Science";
	string course2 = "CS101";

	Student student;

	int c;
	cin >> c;
	switch(c) {
		case 1:
			student.addCourse(fileName, course2);
			break;
		case 2:
			student.removeCourse(fileName, course2);
			break;
		case 3:
			student.modifyCourse(fileName, course1, course2);
			break;
		case 4:
			student.fetchAllCourses(fileName);
			break;
		case 5:
			student.createFile(newFile);
			break;
		case 6:
			student.removeFile(newFile);
			break;
		default:
			break;
	}
	
	// Get courses vector
	vector<string> course_list = student.getCourses(fileName);
	int n = course_list.size();
	for(int i = 0; i < n; i++) {
		cout << course_list[i] << endl;
	}
	
}