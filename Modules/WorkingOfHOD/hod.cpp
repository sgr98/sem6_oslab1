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
                allStudentInstructorMarks[j].second.push_back(SHRT_MIN);
            }
        }
    }

    return allStudentInstructorMarks;
}

string getAllStudentInstructorMarksString(vector<pair<string, vector<float>>> allStudentInstructorMarks) {
    string asim_string = "";

    int size = allStudentInstructorMarks.size();
    for(int i = 0; i < size; i++) {
        asim_string += (allStudentInstructorMarks[i].first + "\t");
        int n = allStudentInstructorMarks[i].second.size();
        for(int j = 0; j < n; j++) {
            if(allStudentInstructorMarks[i].second[j] == SHRT_MIN)
                asim_string += "--\t";
            else
                asim_string += (to_string(allStudentInstructorMarks[i].second[j]) + "\t");
        }
        asim_string += "\n";
    }
    
    return asim_string;
}

void downloadAllStudentsInstructorMarks(string fileStr, vector<pair<string, string>> instructor_and_files) {
    int len = fileStr.length();
	char fileName[len + 1];
	strcpy(fileName, fileStr.c_str());

    vector<pair<string, vector<float>>> allStudentInstructorMarks = getAllStudentInstructorMarks(instructor_and_files);
    string asim_string = getAllStudentInstructorMarksString(allStudentInstructorMarks);
	
    asim_string = asim_string.substr(0, asim_string.length() - 1);
    len = asim_string.length();
	char asim[len + 1];
	strcpy(asim, asim_string.c_str());

    int fd = -1;
    fd = open(fileName, O_WRONLY);

    // if(truncate(fileName, 0) == -1) {
	// 	perror("Could not truncate");
	// }

    if(fd < 0)
		cout << "Error opening file " << fileName << endl;

	write(fd, asim, len);
}