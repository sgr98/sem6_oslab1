#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include "./../InstructorMarksList/instructor_marks_list.h"

using namespace std;

// Compilation: g++ sample.cpp ./../InstructorMarksList/instructor_marks_list.cpp -o sample

int main() {
	string fileName0 = "./hist0.txt";
	string fileName1 = "./hist1.txt";
	string fileName2 = "./hist2.txt";
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

	bool unsaved = false;
	while(true) {
		cout << "------------------------------------------\n";
		cout << "0: Exit" << endl;
		cout << "1: Add Marks to student" << endl;
		cout << "2: Remove Student" << endl;
		cout << "3: Modify Entry" << endl;
		cout << "4: Add marks and students as a list" << endl;
		cout << "5: Get Student Marks" << endl;
		cout << "6: Get Marks Average" << endl;
		cout << "7: Edit student marks" << endl;
		cout << "8: Save Edit" << endl;
		cout << "9: Revert to History 1" << endl;
		cout << "10: Revert to History 2" << endl;
		cout << "11: Download Marks" << endl;
		cout << "------------------------------------------\n";

		int c;
		cin >> c;
		if(c == 0)
			break;
		else if(c == 1) {
			cout << "Enter name :" << endl;
			string s;
			cin >> s;
			cout << "Enter marks:" << endl;
			float d;
			cin >> d;
			instructor_marks_list.addMark(fileName0, s, d);
			unsaved = true;
		}
		else if(c == 2) {
			cout << "Enter name :" << endl;
			string s;
			cin >> s;
			instructor_marks_list.removeMark(fileName0, s);
			unsaved = true;
		}
		else if(c == 3) {
			cout << "Enter old name :" << endl;
			string s1;
			cin >> s1;
			cout << "Enter new name :" << endl;
			string s2;
			cin >> s2;
			cout << "Enter marks:" << endl;
			float d;
			cin >> d;
			instructor_marks_list.modifyMark(fileName0, s1, s2, d);
			unsaved = true;
		}
		else if(c == 4) {
			instructor_marks_list.writeMarksList(fileName0, addMarksList);
			unsaved = true;
		}
		else if(c == 5) {
			vector<pair<string, float>> student_marks_list = instructor_marks_list.getMarksList(fileName0);
			int n = student_marks_list.size();
			for(int i = 0; i < n; i++) {
				cout << student_marks_list[i].first << "\t" << student_marks_list[i].second << endl;
			}
		}
		else if(c == 6) {
			cout << instructor_marks_list.getMarksAverage(fileName0) << endl;
		}
		else if(c == 7) {
			cout << "Enter name :" << endl;
			string s;
			cin >> s;
			cout << "Enter marks:" << endl;
			float d;
			cin >> d;
			instructor_marks_list.editStudentMark(fileName0, s, d);
			unsaved = true;
		}
		else if(c == 8) {
			if(unsaved) {
				cout << "1: Save" << endl;
				cout << "2: Don't save" << endl;
				int e;
				cin >> e;
				if(e == 1) {
					instructor_marks_list.saveEdit(fileName0, fileName1, fileName2);
                }
                else if(e == 2) {
                    instructor_marks_list.clearMarksList();
                }
                unsaved = false;
			}
            else {
                cout << "Already Saved" << endl;
            }
		}
		else if(c == 9) {
			if(!unsaved)
				instructor_marks_list.revertHistory1(fileName0, fileName1);
			else
				cout << "Please save or unsave the file first" << endl;
		}
		else if(c == 10) {
			if(!unsaved)
				instructor_marks_list.revertHistory2(fileName0, fileName1, fileName2);
			else
				cout << "Please save or unsave the file first" << endl;
		}
		else if(c == 11) {
			if(!unsaved) {
				string downloadStr = "marks_download.txt";
				instructor_marks_list.downloadAllinstructorMarks(fileName0, downloadStr);
			}
			else
				cout << "Please save or unsave the file first" << endl;
		}
	}
}