#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include "instructor_marks_list.h"

using namespace std;

int main() {
	string fileName = "./marks.txt";
	string student1 = "student1";
	string student2 = "student20";
	
	
	pair<string, float> student_mark;
	vector<pair<string, float>> addMarksList;
	student_mark.first = "student30";
	student_mark.second = 30;
	addMarksList.push_back(student_mark);
	student_mark.first = "student40";
	student_mark.second = 40;
	addMarksList.push_back(student_mark);
	

	InstructorMarksList instructor_marks_list;

	int c;
	cin >> c;
	switch(c) {
		case 1:
			instructor_marks_list.addMark(fileName, student2, 70.5);
			break;
		case 2:
			instructor_marks_list.removeMark(fileName, student2);
			break;
		case 3:
			instructor_marks_list.modifyMark(fileName, student1, student2, 60);
			break;
		case 4:
			instructor_marks_list.fetchMarksList(fileName);
			break;
		case 5:
			instructor_marks_list.writeMarksList(fileName, addMarksList);
			break;
		case 6:
			cout << instructor_marks_list.getMarksAverage(fileName) << endl;
			break;
		default:
			break;
	}
	
	cout << "------------------------" << endl;
	// Get MarksList vector
	vector<pair<string, float>> student_marks_list = instructor_marks_list.getMarksList(fileName);
	int n = student_marks_list.size();
	for(int i = 0; i < n; i++) {
		cout << student_marks_list[i].first << "\t" << student_marks_list[i].second << endl;
	}
	
}