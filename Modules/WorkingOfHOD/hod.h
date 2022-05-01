#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <limits.h>

#include <fcntl.h>
#include <unistd.h>

using namespace std;

// Number of columns    =   Number of Instructors   =   instructor_and_files.size() + 1 for student_name
// Number of rows       =   Number of Students      =   Union of all students present in each of instructor_and_files

// Pad a string with given amount of white spaces
string padString(string s, int n);
// Print all marks of all students and instructors
void printAllStudentInstructorMarks(vector<pair<string, vector<float>>> allStudentInstructorMarks);
// Check whether the given student name is present in AllStudentInstructorsMarks
int checkNameInAllStudentInstructorMarks(string student, vector<pair<string, vector<float>>> allStudentInstructorMarks);
// Get all marks of all students and instructors
vector<pair<string, vector<float>>> getAllStudentInstructorMarks(vector<pair<string, string>> instructor_and_files);
// Get string value of all marks of all students and instructors
string getAllStudentInstructorMarksString(vector<pair<string, string>> instructor_and_files, vector<pair<string, vector<float>>> allStudentInstructorMarks);
// Download all marks of all students and instructors in a file
void downloadAllStudentsInstructorMarks(string fileStr, vector<pair<string, string>> instructor_and_files);