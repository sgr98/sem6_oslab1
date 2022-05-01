#include "content.h"
#include <iostream>
#include <vector>
#include "editor.h"
using namespace std;


void StudentMarks(string AdminName, vector<string> Instructors, vector<string> Students, vector<vector<int>> marks)
{
	lines.clear();
	Element* e1 = new Element( 20, "HOD DashBoard", STRING, false, true, GREEN, false );
	vector<Element*>* elements1 = new vector<Element*>;
	elements1->push_back(e1);
	Line* l1 = new Line(elements1, CENTER);
	lines.push_back(l1);

	Element* e2 = new Element( 13, "Admin Name :  ", STRING, false, true, GREEN, false );
	vector<Element*>* elements2 = new vector<Element*>;
	elements2->push_back(e2);
	elements2->push_back(new Element( 12, AdminName, STRING, false, false, RED, false ));
	Line* l2 = new Line(elements2, CENTER);
	lines.push_back(l2);

	lines.push_back(NULL);

	Element* e10 = new Element( 20, "Students Marks List", STRING, false, true, GREEN, false );
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
	for( int i = 0 ; i < Students.size() ; i++ )
	{
		vector<Element*>** elements = new vector<Element*>*;
		*elements = new vector<Element*>;

		(*elements)->push_back(new Element( 15, Students[i] , STRING, false, false, RED, false));
		for( int j = 0 ; j < marks[i].size() ; j++ )
		{
			(*elements)->push_back(new Element( 15, to_string(marks[i][j]) , INT, false, false, BLACK, false));
		}

		Line** l = new Line*;
		*l = new Line(*elements, CENTER);
		lines.push_back(*l);
	}

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


void handleButtonClick( string selection )
{
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

void initialize()
{
	string AdminName = "leo";
    vector<string> studentList;
	for( int i = 0 ; i < 10 ; i++ )
	{
		studentList.push_back("Student " + to_string(i+1));
	}

	vector<string> instructor;
	for(int i=0; i<10; i++)
	{
		instructor.push_back("Instructor" + to_string(i+1));
	}

	vector<vector<int>> marks;
	for(int i =0; i<10; i++)
	{
		vector<int> temp;
		for(int j=0; j<10; j++)
		{
			temp.push_back(j*2);
		}
		marks.push_back(temp);
	}
    StudentMarks(AdminName, instructor, studentList, marks);
}