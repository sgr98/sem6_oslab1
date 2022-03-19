#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class Student {
	private:
		vector<string> courses;
		int fileDescpritor = -1;
		
		// Open a file in a specific mode
		void openFile(char *fileName, int mode);
		// Close a file
		void closeFile(char *fileName);
		// Read a file, tokenize courses and append them to courses vector
		void tokenizeCourses();
		// Write all courses back to the file
		void writeCoursesBack();
		// Print Courses
		void printCourses();
		// Clear courses vector
		void clearCourses();
		
	public:
		// Student Constructor
		Student();
		// Add course to a list of courses present in student file
		void addCourse(string fileStr, string courseName);
		// Remove course from a list of courses present in student file
		void removeCourse(string fileStr, string courseName);
		// Modify course from a list of courses present in student file
		void modifyCourse(string fileStr, string courseName, string newCourseName);
		// Fetch all courses present in student file
		void fetchAllCourses(string fileStr);
		// Create a file
		void createFile(string fileStr);
		// Remove a file
		void removeFile(string fileStr);
		// Return all course list of a student
		vector<string> getCourses(string fileStr);
};