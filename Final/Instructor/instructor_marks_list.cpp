#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <stdio.h>

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "../UI/content.h"
#include "instructor_marks_list.h"

using namespace std;
int atoi(string str){
    int num = 0;
    int i = 0;
    bool isNegetive = false;
    if(str[i] == '-'){
        isNegetive = true;
        i++;
    }
    while (str[i] && (str[i] >= '0' && str[i] <= '9')){
        num = num * 10 + (str[i] - '0');
        i++;
    }
    if(isNegetive) num = -1 * num;
    return num;
}

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

void InstructorMarksList::setInstructorMarkList( vector<pair<string, float>> input )
{
	student_marks_list = input;
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
			mark.second = atoi(val);
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

void InstructorMarksList::fetchMarksList(string fileStr) {
	int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());
	
	// Initialising the marks list
	if(student_marks_list.size() == 0) {
		openFile(fileName, 1);
		clearMarksList();
		tokenizeMarksList();
		closeFile(fileName);
	}
}

int InstructorMarksList::copyFile(char *fileName1, char *fileName2) {
	int charLen;
	char buffer[4000];
	// Get contents of file 1
	openFile(fileName1, 1);
	charLen = read(fileDescpritor, buffer, 1000);
	buffer[charLen] = '\0';
	closeFile(fileName1);
	// Remove contents in the file 2
	if(truncate(fileName2, 0) == -1) {
		perror("Could not truncate");
		return -1;
	}
	// Add file 1 contents to file 2
	openFile(fileName2, 2);	
	write(fileDescpritor, buffer, charLen);
	closeFile(fileName2);

	return 1;
}


// ///////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////
// PUBLIC MEMBERS
// ///////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////


InstructorMarksList::InstructorMarksList() {
	
}

void InstructorMarksList::addMark(string fileStr, string student, float mark) {
	student_marks_list.clear();
    fetchMarksList(fileStr);

    // Adding mark list
    pair<string, float> entry;
	entry.first = student;
	entry.second = mark;

	int i = 0;
	int n = student_marks_list.size();
	while(i < n) {
		if(student.compare(student_marks_list[i].first) == 0)
			break;
		i++;
	}
	if(i >= n)
	{
		student_marks_list.push_back(entry);

		string str = "";
		int n = student_marks_list.size();
		for(int i = 0; i < n; i++) {
			str += student_marks_list[i].first + "\t" + to_string(student_marks_list[i].second) + "\n";
		}
		str = str.substr(0, str.length() - 1);
		int len = str.length();

		char chr[len];
		strcpy(chr, str.c_str());
		fileDescpritor = open(fileStr.c_str(), O_WRONLY);
		write(fileDescpritor, chr, len);
	}
	else
		cout << student << " already exists in this marks list" << endl;
}

void InstructorMarksList::removeMark(string fileStr, string student) {
	student_marks_list.clear();
	fetchMarksList(fileStr);

	vector<pair<string, float>>::iterator it;
	it = student_marks_list.begin();
	int i = 0;
	int n = student_marks_list.size();
	bool b = false;
	while(i < n) {
		if(student.compare(student_marks_list[i].first) == 0)
		{
			b = true;
			break;
		}
		i++;
	}
	if( b == true )
	{
		student_marks_list.erase(it + i);

		string str = "";

		int n = student_marks_list.size();
		for(int i = 0; i < n; i++) {
			str += student_marks_list[i].first + "\t" + to_string(student_marks_list[i].second) + "\n";
		}
		str = str.substr(0, str.length() - 1);
		int len = str.length();

		char chr[len];
		strcpy(chr, str.c_str());
		fileDescpritor = open(fileStr.c_str(), O_WRONLY | O_TRUNC );
		int res = write(fileDescpritor, chr, len);
	}
	else
	{
		cout << student << " doesn't exist in this marks list" << endl;
	}
}

void InstructorMarksList::modifyMark(string fileStr, string student, string newStudent, float newMark) {
	if(student_marks_list.size() == 0) {
		// Initialising the marks list
		fetchMarksList(fileStr);
	}

	// Modifying marks list
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
}

void InstructorMarksList::writeMarksList(string fileStr, vector<pair<string, float>> marks) {
	if(student_marks_list.size() == 0) {
		// Initialising the marks list
		fetchMarksList(fileStr);
	}

	int n = marks.size();
	for(int i = 0; i < n; i++)
		student_marks_list.push_back(marks[i]);
}

vector<pair<string, float>> InstructorMarksList::getMarksList(string fileStr) {
	fetchMarksList(fileStr);
	return student_marks_list;
}

void InstructorMarksList::clearMarksList() {
	student_marks_list.clear();
}

float InstructorMarksList::getMarksAverage(string fileStr) {
	if(student_marks_list.size() == 0) {
		// Initialising the marks list
		fetchMarksList(fileStr);
	}
	int n = student_marks_list.size();
	float avg = 0;
	for(int i = 0; i < n; i++) {
		avg += student_marks_list[i].second;
	}
	avg /= (float) n;
	return avg;
}

void InstructorMarksList::editStudentMark(string fileStr, string student, float newMark) {
	modifyMark(fileStr, student, "", newMark);
}

int InstructorMarksList::saveEdit(string fileStr0, string fileStr1, string fileStr2) {
	int len = fileStr0.length();
	char fileName0[len + 1];
	strcpy(fileName0, fileStr0.c_str());

	len = fileStr1.length();
	char fileName1[len + 1];
	strcpy(fileName1, fileStr1.c_str());

	len = fileStr2.length();
	char fileName2[len + 1];
	strcpy(fileName2, fileStr2.c_str());

	// Change and save every history file
	if(copyFile(fileName1, fileName2) == -1)
		return -1;
	if(copyFile(fileName0, fileName1) == -1)
		return -1;

	// /////////////////////////////////////////////
	// Add student_marks_list contents to file 0
	openFile(fileName0, 2);
	writeMarksListBack();
	closeFile(fileName0);

	return 1;
}

int InstructorMarksList::revertHistory1(string fileStr0, string fileStr1) {
	int len = fileStr0.length();
	char fileName0[len + 1];
	strcpy(fileName0, fileStr0.c_str());

	len = fileStr1.length();
	char fileName1[len + 1];
	strcpy(fileName1, fileStr1.c_str());

	int charLen;
	char buffer[4000];
	// Get contents of file 1
	openFile(fileName1, 1);
	charLen = read(fileDescpritor, buffer, 1000);
	buffer[charLen] = '\0';
	closeFile(fileName1);

	// Overwrite file 1 with content of file 0
	if(copyFile(fileName0, fileName1) == -1)
		return -1;

	// Remove contents in the file 0
	if(truncate(fileName0, 0) == -1) {
		perror("Could not truncate");
		return -1;
	}
	// Overwrite file 1 contents to file 0
	openFile(fileName0, 2);	
	write(fileDescpritor, buffer, charLen);
	closeFile(fileName0);

	clearMarksList();

	return 1;
}

int InstructorMarksList::revertHistory2(string fileStr0, string fileStr1, string fileStr2) {
	int len = fileStr0.length();
	char fileName0[len + 1];
	strcpy(fileName0, fileStr0.c_str());

	len = fileStr1.length();
	char fileName1[len + 1];
	strcpy(fileName1, fileStr1.c_str());

	len = fileStr2.length();
	char fileName2[len + 1];
	strcpy(fileName2, fileStr2.c_str());

	int charLen;
	char buffer[4000];
	// Get contents of file 1
	openFile(fileName2, 1);
	charLen = read(fileDescpritor, buffer, 1000);
	buffer[charLen] = '\0';
	closeFile(fileName2);

	// Overwrite file 2 with content of file 1
	if(copyFile(fileName1, fileName2) == -1)
		return -1;
	// Overwrite file 1 with content of file 0
	if(copyFile(fileName0, fileName1) == -1)
		return -1;

	// Remove contents in the file 0
	if(truncate(fileName0, 0) == -1) {
		perror("Could not truncate");
		return -1;
	}
	// Overwrite file 2 contents to file 0
	openFile(fileName0, 2);	
	write(fileDescpritor, buffer, charLen);
	closeFile(fileName0);

	clearMarksList();

	return 1;
}

string InstructorMarksList::padString(string s, int n) {
	if(n % 4 == 0)
		n += 4;
	else
		n += (n % 4);

	string t = "";
	for(int i = 0; i < n; i++) {
		if(i >= s.length()) {
			t += " ";
			continue;
		}
		t += s[i];
	}
	return t;
}

string InstructorMarksList::getAllInstructorMarksString(vector<pair<string, float>> student_marks_list) {
	string aim_string = "";

	int stringPads;
	stringPads = 0;
	int size = student_marks_list.size();
	for(int i = 0; i < size; i++) {
		if(stringPads < student_marks_list[i].first.length())
			stringPads = student_marks_list[i].first.length();
	}
	stringPads += 2;

	for(int i = 0; i < size; i++) {
		aim_string += padString(student_marks_list[i].first, stringPads);
		aim_string += to_string(student_marks_list[i].second);
		aim_string += "\n";
	}

	return aim_string;
}

void InstructorMarksList::downloadAllinstructorMarks(string instructorFilePath, string downloadFileStr) {
	int len = downloadFileStr.length();
	char fileName[len + 1];
	strcpy(fileName, downloadFileStr.c_str());

	vector<pair<string, float>> student_marks_list = getMarksList(instructorFilePath);
	string aim_string = getAllInstructorMarksString(student_marks_list);

	aim_string = aim_string.substr(0, aim_string.length() - 1);
	len = aim_string.length();
	char aim[len + 1];
	strcpy(aim, aim_string.c_str());

	int fd = -1;
	fd = open(fileName, O_WRONLY | O_CREAT);		// Add O_CREAT and proper PERMISSIONS

	// if(truncate(fileName, 0) == -1) {
	// 	perror("Could not truncate");
	// }

	if(fd < 0)
		cout << "Error opening file " << fileName << endl;

	write(fd, aim, len);
	close(fd);
}
