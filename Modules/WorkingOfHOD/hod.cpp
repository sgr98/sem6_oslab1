#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <limits.h>

#include <fcntl.h>
#include <unistd.h>

#include "./../InstructorMarksList/instructor_marks_list.h"
#include "./hod.h"

using namespace std;

string padString(string s, int n) {
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

void printAllStudentInstructorMarks(vector<pair<string, vector<float>>> allStudentInstructorMarks) {
    int size = allStudentInstructorMarks.size();
    for(int i = 0; i < size; i++) {
        cout << allStudentInstructorMarks[i].first << "\t";
        int n = allStudentInstructorMarks[i].second.size();
        for(int j = 0; j < n; j++) {
            cout << allStudentInstructorMarks[i].second[j] << "\t";
        }
        cout << endl;
    }
}

int checkNameInAllStudentInstructorMarks(string student, vector<pair<string, vector<float>>> allStudentInstructorMarks) {
    int i = 0;
	int n = allStudentInstructorMarks.size();
	while(i < n) {
		if(student.compare(allStudentInstructorMarks[i].first) == 0)
			return i;
		i++;
	}
    return -1;
}

void printMarksList(vector<pair<string, float>> student_marks_list) {
	int n = student_marks_list.size();
	for(int i = 0; i < n; i++) {
		cout << student_marks_list[i].first << "\t" << student_marks_list[i].second << endl;
	}
}

vector<pair<string, vector<float>>> getAllStudentInstructorMarks(vector<pair<string, string>> instructor_and_files) {
    int n_ial = instructor_and_files.size();
    pair<string, vector<float>> student_marks_pair;
    vector<pair<string, vector<float>>> allStudentInstructorMarks;
    
    InstructorMarksList instructor_marks_list;

    // Initialise all the names of the students to the vector
    for(int i = 0; i < n_ial; i++) {
        string filePath = instructor_and_files[i].second + "hist0.txt";
        vector<pair<string, float>> student_marks_list = instructor_marks_list.getMarksList(filePath);
        instructor_marks_list.clearMarksList();

        int n_sml = student_marks_list.size();
        for(int j = 0; j < n_sml; j++) {
            if(checkNameInAllStudentInstructorMarks(student_marks_list[j].first, allStudentInstructorMarks) == -1) {
                student_marks_pair.first = student_marks_list[j].first;
                allStudentInstructorMarks.push_back(student_marks_pair);
            }
        }
    }

    // Add Marks to all students in the vector
    for(int i = 0; i < n_ial; i++) {
        string filePath = instructor_and_files[i].second + "/hist0.txt";
        vector<pair<string, float>> student_marks_list = instructor_marks_list.getMarksList(filePath);
        instructor_marks_list.clearMarksList();

        int n_sml = student_marks_list.size();
        for(int j = 0; j < n_sml; j++) {
            int ind = checkNameInAllStudentInstructorMarks(student_marks_list[j].first, allStudentInstructorMarks);
            if(ind != -1) {
                allStudentInstructorMarks[ind].second.push_back(student_marks_list[j].second);
            }
        }

        int n_asim = allStudentInstructorMarks.size();
        for(int j = 0; j < n_asim; j++) {
            if(allStudentInstructorMarks[j].second.size() != i + 1) {
                allStudentInstructorMarks[j].second.push_back(-1);
            }
        }
    }

    return allStudentInstructorMarks;
}

string getAllStudentInstructorMarksString(vector<pair<string, string>> instructor_and_files, vector<pair<string, vector<float>>> allStudentInstructorMarks) {
    string asim_string = "";

    pair<int, int> stringPads;
    stringPads.first = 0;
    stringPads.second = 0;
    int sz = allStudentInstructorMarks.size();
    for(int i = 0; i < sz; i++) {
        if(stringPads.first < allStudentInstructorMarks[i].first.length())
            stringPads.first = allStudentInstructorMarks[i].first.length();
    }
    stringPads.first += 2;
    sz = instructor_and_files.size();
    for(int i = 0; i < sz; i++) {
        if(stringPads.second < instructor_and_files[i].first.length())
            stringPads.second = instructor_and_files[i].first.length();
    }
    stringPads.second += 2;
    if(stringPads.second < 16)
        stringPads.second = 16;

    asim_string += padString("", stringPads.first);
    for(int i = 0; i < sz; i++) {
        asim_string += padString(instructor_and_files[i].first, stringPads.second);
    }
    asim_string += "\n";

    int size = allStudentInstructorMarks.size();
    for(int i = 0; i < size; i++) {
        asim_string += padString(allStudentInstructorMarks[i].first, stringPads.first);
        int n = allStudentInstructorMarks[i].second.size();
        for(int j = 0; j < n; j++) {
            if(allStudentInstructorMarks[i].second[j] == -1 )
                asim_string += padString("--", stringPads.second);
            else
                asim_string += padString(to_string(allStudentInstructorMarks[i].second[j]), stringPads.second);
        }
        asim_string += "\n";
    }
    
    return asim_string;
}

void downloadAllStudentsInstructorMarks(string fileStr, vector<pair<string, string>> instructor_and_files, vector<pair<string, vector<float>>> allStudentInstructorMarks ) {

    string asim_string = getAllStudentInstructorMarksString(instructor_and_files, allStudentInstructorMarks);
	
    asim_string = asim_string.substr(0, asim_string.length() - 1);
    int len = asim_string.length();
	char asim[len + 1];
	strcpy(asim, asim_string.c_str());

    int fd = -1;
    fd = open(fileStr.c_str(), O_CREAT | O_WRONLY);		// Add O_CREAT and proper PERMISSIONS

    if(fd < 0)
		cout << "Error opening file " << fileStr << endl;

	write(fd, asim, len);
    close(fd);
}
