#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "student.h"

using namespace std;

void Student::openFile(char *fileName, int mode) {
	//cout << "Fetching " << fileName << endl;
	
	switch(mode) {
		case 1:
			fileDescpritor = open(fileName, O_RDONLY);
			break;
		case 2:
			fileDescpritor = open(fileName, O_WRONLY);
			break;
		default:
			break;
	}
	
	if(fileDescpritor < 0)
		cout << "Error opening file " << fileName << endl;
	else {
		//cout << "File " << fileName << " successfully opened" << endl;
	}
}

void Student::closeFile(char *fileName) {
	//cout << "Closing " << fileName << endl;
	close(fileDescpritor);
	fileDescpritor = -1;
}

void Student::tokenizeCourses() {
	int charLen;
	char buffer[1000];
	charLen = read(fileDescpritor, buffer, 1000);
	buffer[charLen] = '\0';
	
	if(charLen != 0) {
		char delim[] = "\n";
	
		char *token = strtok(buffer, delim);
		while(token) {
			courses.push_back(string(token));
			token = strtok(NULL, delim);
		}
		
		// Printing Courses
		// printCourses();
	}
}

void Student::writeCoursesBack() {		
	string str = "";
	int n = courses.size();
	for(int i = 0; i < n; i++) {
		str += courses[i] + "\n";
	}
	str = str.substr(0, str.length() - 1);
	int len = str.length();
	
	char chr[len];
	strcpy(chr, str.c_str());
	
	write(fileDescpritor, chr, len);
}

void Student::printCourses() {
	int n = courses.size();
	for(int i = 0; i < n; i++) {
		cout << courses[i] << endl;
	}
}

void Student::clearCourses() {
	courses.clear();
}

Student::Student() {
	
}

void Student::addCourse(string fileStr, string courseName) {
	int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());

	// Initialising the courses
	openFile(fileName, 1);
	clearCourses();
	tokenizeCourses();
	closeFile(fileName);
	
	// Adding Course
	openFile(fileName, 2);

	int i = 0;
	int n = courses.size();
	while(i < n) {
		if(courseName.compare(courses[i]) == 0)
			break;
		i++;
	}
	if(i >= n)
		courses.push_back(courseName);
	else
		cout << "Course with course name: " << courseName 
			<< " already exists in the student file" << endl;
	
	writeCoursesBack();
	closeFile(fileName);
}

void Student::removeCourse(string fileStr, string courseName) {
	int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());
	
	// Initialising the courses
	openFile(fileName, 1);
	clearCourses();
	tokenizeCourses();
	closeFile(fileName);
	
	// Remove contents in the file
	if(truncate(fileName, 0) == -1) {
		perror("Could not truncate");
	}
	
	// Removing Course
	openFile(fileName, 2);
	
	vector<string>::iterator it;
	it = courses.begin();
	int i = 0;
	int n = courses.size();
	while(i < n) {
		if(courseName.compare(courses[i]) == 0)
			break;
		i++;
	}
	courses.erase(it + i);
	writeCoursesBack();
	
	closeFile(fileName);
}

void Student::modifyCourse(string fileStr, string courseName, string newCourseName) {
	int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());
	
	// Initialising the courses
	openFile(fileName, 1);
	clearCourses();
	tokenizeCourses();
	closeFile(fileName);
	
	// Remove contents in the file
	if(truncate(fileName, 0) == -1) {
		perror("Could not truncate");
	}
	
	// Modifying course
	openFile(fileName, 2);
	
	int i = 0;
	int n = courses.size();
	while(i < n) {
		if(courseName.compare(courses[i]) == 0)
			break;
		i++;
	}
	if(i < n)
		courses[i] = newCourseName;
	writeCoursesBack();
	
	closeFile(fileName);
}

void Student::fetchAllCourses(string fileStr) {
	int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());
	
	// Initialising the courses
	openFile(fileName, 1);
	clearCourses();
	tokenizeCourses();
	closeFile(fileName);
}

void Student::createFile(string fileStr) {
	int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());
	
	// Set file permissions later
	int fd = open(fileName, O_CREAT, 0642);
	close(fd);
}

void Student::removeFile(string fileStr) {
	int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());
	
	remove(fileName);
}

vector<string> Student::getCourses(string fileStr) {
	fetchAllCourses(fileStr);
	return courses;
}