#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

#include "../Student/student.h"
#include "./../InstructorMarksList/instructor_marks_list.h"

using namespace std;

// Compilation: g++ sample.cpp ./../InstructorMarksList/instructor_marks_list.cpp -o sample

float get_mean(string coursename)
{
    string file = coursename+".txt";
    InstructorMarksList instructor_marks_list;
    return instructor_marks_list.getMarksAverage(file);
}

int get_marks(string coursename,string student)
{
    string file = coursename+".txt";
    InstructorMarksList instructor_marks_list;
    vector<pair<string, float>> student_marks_list = instructor_marks_list.getMarksList(file);
    int i;
    for(i=0;i<student_marks_list.size();i++)
    {
        if(student_marks_list[i].first == student)
        break;
    }
    return student_marks_list[i].second ;
}

bool helper(string name)
{
    string file = name +".txt";
    cout << "------------------------------------------\n";
	cout << "0: Exit" << endl;
	cout << "1: View Marks" << endl;
	cout << "2: Download Marks" << endl;
	cout << "3: Share marks with other students" << endl;
	cout << "4: See shared marks" << endl;
	cout << "------------------------------------------\n";

	int c;
	cin >> c;
		
    if(c==0)
    {
        return true;
    }
    else if(c==1)
    {
        Student student;
        vector<string> course_list = student.getCourses(file);
        vector< int > marks;
        int i;
        int space = 15;
        cout<<"here"<<endl;
        for(i=0;i<course_list.size();i++)
        {
            marks.push_back(get_marks(course_list[i],name));
        }
        cout<<setw(space)<<"Courses:-";
        for(i=0;i<course_list.size();i++)
        cout<<setw(space)<<course_list[i];
        cout<<endl;
        cout<<setw(space)<<name;
        for(i=0;i<marks.size();i++)
        cout<<setw(space)<<marks[i];
        cout<<endl;
        cout<<setw(space)<<"Mean :";
        for(i=0;i<course_list.size();i++)
        cout<<setw(space)<<get_mean(course_list[i]);
        cout<<endl;
    }
    else if(c==2)
    {
        ofstream f;
        f.open(name+"Marks.txt");
        Student student;
        vector<string> course_list = student.getCourses(file);
        vector< int > marks;
        int i;
        int space = 15;
        for(i=0;i<course_list.size();i++)
        {
            marks.push_back(get_marks(course_list[i],name));
        }
        f<<setw(space)<<"Courses:-";
        for(i=0;i<course_list.size();i++)
            f<<setw(space)<<course_list[i];
        f<<endl;
        f<<setw(space)<<name;
        for(i=0;i<marks.size();i++)
            f<<setw(space)<<marks[i];
        f<<endl;
        f<<setw(space)<<"Mean :";
        for(i=0;i<course_list.size();i++)
        f<<setw(space)<<get_mean(course_list[i]);
        f<<endl;
    }
    else if(c==3)
    {
        
    }
    else if(c==4)
    {

    }
    else
    {
        cout<<"Please Enter one of the below numbers only"<<endl;
    }
    return false;
}

void workingOfStudent(string name)
{
    while(true) {
        if(helper(name))
        return ;
	}
}

int main() {
	workingOfStudent("student1");
}