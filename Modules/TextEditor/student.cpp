#include "content.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstring>
#include "editor.h"
#include <fstream>
#include "../Student/student.h"
#include "./../InstructorMarksList/instructor_marks_list.h"
using namespace std;

string studentName;
void StudentMarks(string AdminName, vector<string> Instructors, string Student, vector<int> marks)
{
	lines.clear();
	Element* e1 = new Element( 20, "Student DashBoard", STRING, false, true, GREEN, false );
	vector<Element*>* elements1 = new vector<Element*>;
	elements1->push_back(e1);
	Line* l1 = new Line(elements1, CENTER);
	lines.push_back(l1);

	Element* e2 = new Element( 13, "Student Name :  ", STRING, false, true, GREEN, false );
	vector<Element*>* elements2 = new vector<Element*>;
	elements2->push_back(e2);
	elements2->push_back(new Element( 12, AdminName, STRING, false, false, RED, false ));
	Line* l2 = new Line(elements2, CENTER);
	lines.push_back(l2);

	lines.push_back(NULL);

	Element* e10 = new Element( 10, "Marks List", STRING, false, true, GREEN, false );
	vector<Element*>* elements10 = new vector<Element*>;
	elements10->push_back(e10);
	Line* l10 = new Line(elements10, CENTER);
	lines.push_back(l10);

	lines.push_back(NULL);

	lines.push_back(NULL);

	//                               size, content,   type,   edit , bold, color, clickable
	vector<Element*>* elements3 = new vector<Element*>;
	elements3->push_back(new Element( 15, "               ", STRING, false, true, BLUE, false ));
	for(int i=0; i<Instructors.size(); i++)
	{
		elements3->push_back(new Element( 15, Instructors[i], STRING, false, true, BLUE, false ));
	}

	Line* l3 = new Line(elements3, CENTER);
	lines.push_back(l3);

	lines.push_back(NULL);
	// for( int i = 0 ; i < Students.size() ; i++ )
	// {
		vector<Element*>** elements = new vector<Element*>*;
		*elements = new vector<Element*>;

		(*elements)->push_back(new Element( 15, Student , STRING, false, false, RED, false));
		for( int j = 0 ; j < marks.size() ; j++ )
		{
			(*elements)->push_back(new Element( 15, to_string(marks[j]) , INT, false, false, BLACK, false));
		}

		Line** l = new Line*;
		*l = new Line(*elements, CENTER);
		lines.push_back(*l);
	// }

    lines.push_back(NULL);

	lines.push_back(NULL);
	vector<Element*>** go_back = new vector<Element*>*;
	*go_back = new vector<Element*>;	
	//(*go_back)->push_back(new Element( 4, "    " , STRING, false, false, RED, false));
	(*go_back)->push_back(new Element( 8, "Download" , STRING, false, true, BLUE, true));
	
	Line* l5 = new Line(*go_back, CENTER);
	lines.push_back(l5);
}

void editorProcessKeypress()
{
	int c = editorReadKey();

	switch(c)
	{
		case '\n':
		case '\r':
			//exitEditorMode(&E.cx, &E.cy);
			enterEditorMode( &E.cx, &E.cy );
			break;
		case'q':
			ExitEditorMode();
			exit(0);
			break;
		case ARROW_UP:
		case ARROW_DOWN:
		case ARROW_LEFT:
		case ARROW_RIGHT:
			editorMoveCursor(c);
			break;
	}
}

int get_marks(string coursename,string student);

float get_mean(string coursename)
{
	string file = "./Instructors/" + coursename + "/hist0.txt";
    InstructorMarksList instructor_marks_list;
    return instructor_marks_list.getMarksAverage(file);
}

void handleButtonClick( string selection )
{
	if( selection == "Download" )
	{
		ofstream f;

        f.open(studentName+"Marks.txt");
        Student student;
        vector<string> course_list = student.getCourses("./Students/" + studentName + ".txt");
        vector< int > marks;
        int i;
        int space = 15;
        for(i=0;i<course_list.size();i++)
        {
            marks.push_back(get_marks(course_list[i], studentName));
        }
        f<<setw(space)<<"Courses:-";
        for(i=0;i<course_list.size();i++)
            f<<setw(space)<<course_list[i];
        f<<endl;
        f<<setw(space)<<studentName;
        for(i=0;i<marks.size();i++)
            f<<setw(space)<<marks[i];
        f<<endl;
        f<<setw(space)<<"Mean :";
        for(i=0;i<course_list.size();i++)
        f<<setw(space)<<get_mean(course_list[i]);
        f<<endl;
	}
	return;
} 

bool enterEditorMode( int* x, int* y )
{
	for( int j = 0 ; j < (*(*lines[*y]).elements).size() ; j++ )
	{
		if( (*(*lines[*y]).elements)[j]->start == *x )
		{
			(*(*lines[*y]).elements)[j]->underlined = true;
			if( (*(*lines[*y]).elements)[j]->clickable == false )
			{
				return false;
			}
			handleButtonClick((*(*lines[*y]).elements)[j]->content);
			return true;
		}
	}
	return false;
}

int get_marks(string coursename,string student)
{
	string files = "./Instructors/" + coursename + "/hist0.txt";
    InstructorMarksList instructor_marks_list;
    vector<pair<string, float>> student_marks_list = instructor_marks_list.getMarksList(files);
    int i;
    for(i=0;i<student_marks_list.size();i++)
    {
        if(student_marks_list[i].first == student)
        break;
    }
    return student_marks_list[i].second ;
}

void initialize()
{
	Student student;
	studentName = "student1";

	vector<string> course_list = student.getCourses("./Students/" + studentName + ".txt");

	vector< int > marks;

	int i;
	int space = 15;
	for(i=0;i<course_list.size();i++)
	{
		marks.push_back(get_marks(course_list[i],studentName));
	}

	/*
	cout<<setw(space)<<"Courses:-";
	for(i=0;i<course_list.size();i++)
		cout<<setw(space)<<course_list[i];
	cout<<endl;
	cout<<setw(space)<<studentName;
	for(i=0;i<marks.size();i++)
		cout<<setw(space)<<marks[i];
	cout<<endl;
	cout<<setw(space)<<"Mean :";
	for(i=0;i<course_list.size();i++)
		cout<<setw(space)<<get_mean(course_list[i]);
	cout<<endl;
	*/
	
	StudentMarks(studentName, course_list, studentName, marks);
}
