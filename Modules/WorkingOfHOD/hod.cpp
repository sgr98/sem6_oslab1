#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <limits.h>

#include "./../InstructorMarksList/instructor_marks_list.h"
#include "./hod.h"

using namespace std;

void printAllStudentInstructorMarks(vector<pair<string, vector<float>>> allStudentInstructorMarks) {
    int size = allStudentInstructorMarks.size();
    for(int i = 0; i < size; i++) {
        cout << allStudentInstructorMarks[i].first << "\t\t";
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
        string filePath = instructor_and_files[i].second + "/hist0.txt";
        vector<pair<string, float>> student_marks_list = instructor_marks_list.getMarksList(filePath);

        int n_sml = student_marks_list.size();
        for(int j = 0; j < n_sml; j++) {
            if(checkNameInAllStudentInstructorMarks(student_marks_list[j].first, allStudentInstructorMarks) == -1) {
                student_marks_pair.first = student_marks_list[j].first;
                allStudentInstructorMarks.push_back(student_marks_pair);
            }
        }
    }

    // Add Marks to all students in the vector
    // int n_asim = allStudentInstructorMarks
    for(int i = 0; i < n_ial; i++) {
        string filePath = instructor_and_files[i].second + "/hist0.txt";
        vector<pair<string, float>> student_marks_list = instructor_marks_list.getMarksList(filePath);

        int n_sml = student_marks_list.size();
        for(int j = 0; j < n_sml; j++) {
            if(checkNameInAllStudentInstructorMarks(student_marks_list[j].first, allStudentInstructorMarks) == -1) {
                student_marks_pair.first = student_marks_list[j].first;
                allStudentInstructorMarks.push_back(student_marks_pair);
            }
        }
    }



    printAllStudentInstructorMarks(allStudentInstructorMarks);

    return allStudentInstructorMarks;
}

string getAllStudentInstructorMarksString(vector<pair<string, vector<float>>> allStudentInstructorMarks) {

    
    return "";
}