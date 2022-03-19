#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "instructor_marks_list.h"

using namespace std;

void InstructorMarksList::openFile(char *fileName, int mode) {
	//cout << "Fetching " << fileName << endl;
	
	switch(mode) {
		case 1:
			fileDescpritor = open(fileName, O_RDONLY);
			break;
		case 2:
			fileDescpritor = open(fileName, O_WRONLY);
			break;
		case 3:
			fileDescpritor = open(fileName, O_RDWR);
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

void InstructorMarksList::closeFile(char *fileName) {
	//cout << "Closing " << fileName << endl;
	close(fileDescpritor);
	fileDescpritor = -1;
}

void InstructorMarksList::tokenizeMarksList() {
	int charLen;
	char buffer[4000];
	charLen = read(fileDescpritor, buffer, 1000);
	buffer[charLen] = '\0';
	
	if(charLen != 0) {
		char delim1[] = "\n";
		char delim2[] = "\t";
	
		char *token1 = strtok(buffer, delim1);
		while(token1) {
			string str = string(token1);
			
			string studName, val;
			int i = 0;
			while(str[i] != delim2[0]) {
				studName += str[i];
				i++;
			}
			i++;
			while(str[i] != '\0') {
				val += str[i];
				i++;
			}
		
			pair<string, float> mark;
			mark.first = studName;
			mark.second = stof(val);
			student_marks_list.push_back(mark);
			
			token1 = strtok(NULL, delim1);
		}
		
		// Printing Courses
		// printMarksList();
	}
}

void InstructorMarksList::writeMarksListBack() {
	string str = "";
	int n = student_marks_list.size();
	for(int i = 0; i < n; i++) {
		str += student_marks_list[i].first + "\t" + to_string(student_marks_list[i].second) + "\n";
	}
	str = str.substr(0, str.length() - 1);
	int len = str.length();
	
	char chr[len];
	strcpy(chr, str.c_str());
	
	write(fileDescpritor, chr, len);
}

void InstructorMarksList::printMarksList() {
	int n = student_marks_list.size();
	for(int i = 0; i < n; i++) {
		cout << student_marks_list[i].first << "\t" << student_marks_list[i].second << endl;
	}
}

void InstructorMarksList::clearMarksList() {
	student_marks_list.clear();
}

InstructorMarksList::InstructorMarksList() {
	
}

void InstructorMarksList::addMark(string fileStr, string student, float mark) {
	int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());

	// Initialising the marks list
	openFile(fileName, 1);
	clearMarksList();
	tokenizeMarksList();
	closeFile(fileName);
	
	// Adding mark
	openFile(fileName, 2);
	pair<string, float> entry;
	entry.first = student;
	entry.second = mark;
	student_marks_list.push_back(entry);
	writeMarksListBack();
	closeFile(fileName);
}

void InstructorMarksList::removeMark(string fileStr, string student) {
	int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());
	
	// Initialising the marks list
	openFile(fileName, 1);
	clearMarksList();
	tokenizeMarksList();
	closeFile(fileName);
	
	// Remove contents in the file
	if(truncate(fileName, 0) == -1) {
		perror("Could not truncate");
	}
	
	// Removing mark
	openFile(fileName, 2);
	
	vector<pair<string, float>>::iterator it;
	it = student_marks_list.begin();
	int i = 0;
	int n = student_marks_list.size();
	while(i < n) {
		if(student.compare(student_marks_list[i].first) == 0)
			break;
		i++;
	}
	student_marks_list.erase(it + i);
	writeMarksListBack();
	
	closeFile(fileName);
}

void InstructorMarksList::modifyMark(string fileStr, string student, string newStudent, float newMark) {
	int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());
	
	// Initialising the marks list
	openFile(fileName, 1);
	clearMarksList();
	tokenizeMarksList();
	closeFile(fileName);
	
	// Remove contents in the file
	if(truncate(fileName, 0) == -1) {
		perror("Could not truncate");
	}
	
	// Modifying mark
	openFile(fileName, 2);
	
	int i = 0;
	int n = student_marks_list.size();
	while(i < n) {
		if(student.compare(student_marks_list[i].first) == 0)
			break;
		i++;
	}
	if(i < n) {
		if(newStudent.compare("") == 0 && newMark == -1);
		else if(newMark == -1)
			student_marks_list[i].first = newStudent;
		else if(newStudent.compare("") == 0)
			student_marks_list[i].second = newMark;
		else {
			student_marks_list[i].first = newStudent;
			student_marks_list[i].second = newMark;
		}
	}
	writeMarksListBack();
	
	closeFile(fileName);
}

void InstructorMarksList::fetchMarksList(string fileStr) {
	int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());
	
	// Initialising the marks list
	openFile(fileName, 1);
	clearMarksList();
	tokenizeMarksList();
	closeFile(fileName);
}

void InstructorMarksList::writeMarksList(string fileStr, vector<pair<string, float>> marks) {
	int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());
	
	// Initialising the marks list
	openFile(fileName, 1);
	clearMarksList();
	tokenizeMarksList();
	closeFile(fileName);
	
	// Remove contents in the file
	if(truncate(fileName, 0) == -1) {
		perror("Could not truncate");
	}
	
	// Appending marks list to the file
	openFile(fileName, 2);
	int n = marks.size();
	for(int i = 0; i < n; i++)
		student_marks_list.push_back(marks[i]);
	writeMarksListBack();
	closeFile(fileName);
}

vector<pair<string, float>> InstructorMarksList::getMarksList(string fileStr) {
	fetchMarksList(fileStr);
	return student_marks_list;
}

float InstructorMarksList::getMarksAverage(string fileStr) {
	fetchMarksList(fileStr);
	int n = student_marks_list.size();
	float avg = 0;
	for(int i = 0; i < n; i++) {
		avg += student_marks_list[i].second;
	}
	avg /= (float) n;
	return avg;
}