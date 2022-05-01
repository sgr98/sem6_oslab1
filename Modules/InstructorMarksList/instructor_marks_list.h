#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class InstructorMarksList {
	private:
		vector<pair<string, float>> student_marks_list;
		int fileDescpritor = -1;
		
		// Open a file in a specific mode
		void openFile(char *fileName, int mode);
		// Close a file
		void closeFile(char *fileName);
		// Read a file, tokenize courses and append them to courses vector
		void tokenizeMarksList();
		// Write all Marks List back to the file
		void writeMarksListBack();
		// Print Marks List
		void printMarksList();
		// Fetch all Mark Lists present in student file
		void fetchMarksList(string fileStr);
		// Overwrite content of file 1 into file 2
		int copyFile(char *fileName1, char *fileName2);
		
	public:
		// Student Constructor
		InstructorMarksList();
		// Add Student Mark to a list of courses present in student file
		void addMark(string fileStr, string student, float mark);
		// Remove Student Mark from a list of courses present in student file
		void removeMark(string fileStr, string student);
		// Modify Student Mark from a list of courses present in student file
		void modifyMark(string fileStr, string student, string newStudent, float newMark);
		// Write Marks List to the file
		void writeMarksList(string fileStr, vector<pair<string, float>> marks);
		// Return all Marks lists of a student
		vector<pair<string, float>> getMarksList(string fileStr);
		// Clear Marks List vector
		void clearMarksList();
		// Get average of all marks
		float getMarksAverage(string fileStr);

		// Edit marks of specified student
		void editStudentMark(string fileStr, string student, float newMark);
		// Save the file cyclically
		int saveEdit(string fileStr0, string fileStr1, string fileStr2);
		// Revert to History 1
		int revertHistory1(string fileStr0, string fileStr1);
		// Revert to History 2
		int revertHistory2(string fileStr0, string fileStr1, string fileStr2);

		// Pad a string with given amount of white spaces
		string padString(string s, int n);
		// Get string value of all marks of instructors
		string getAllInstructorMarksString(vector<pair<string, float>> student_marks_list);
		// Download all marks of instructors in a file
		void downloadAllinstructorMarks(string instructorFilePath, string downloadFileStr);
};