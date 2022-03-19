#include <iostream>
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
		// Clear Marks List vector
		void clearMarksList();
		
	public:
		// Student Constructor
		InstructorMarksList();
		// Add Student Mark to a list of courses present in student file
		void addMark(string fileStr, string student, float mark);
		// Remove Student Mark from a list of courses present in student file
		void removeMark(string fileStr, string student);
		// Modify Student Mark from a list of courses present in student file
		void modifyMark(string fileStr, string student, string newStudent, float newMark);
		// Fetch all Mark Lists present in student file
		void fetchMarksList(string fileStr);
		// Write Marks List to the file
		void writeMarksList(string fileStr, vector<pair<string, float>> marks);
		// Return all Marks lists of a student
		vector<pair<string, float>> getMarksList(string fileStr);
		// Get average of all marks
		float getMarksAverage(string fileStr);
};