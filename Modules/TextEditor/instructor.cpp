#include "content.h"
#include <iostream>
#include <vector>
#include "editor.h"
using namespace std;


void StudentMarks(string AdminName, vector<string> Students, string Instructor, vector<int> marks)
{
	lines.clear();
	Element* e1 = new Element( 20, "Instructor DashBoard", STRING, false, true, GREEN, false );
	vector<Element*>* elements1 = new vector<Element*>;
	elements1->push_back(e1);
	Line* l1 = new Line(elements1, CENTER);
	lines.push_back(l1);

	Element* e2 = new Element( 20, "Instructor Name :  ", STRING, false, true, GREEN, false );
	vector<Element*>* elements2 = new vector<Element*>;
	elements2->push_back(e2);
	elements2->push_back(new Element( 12, Instructor, STRING, false, false, RED, false ));
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
	//vector<Element*>* elements3 = new vector<Element*>;
	// elements3->push_back(new Element( 15, "               ", STRING, false, true, BLUE, false ));
	// for(int i=0; i<Students.size(); i++)
	// {
	// 	elements3->push_back(new Element( 15, Students[i], STRING, false, true, BLUE, false ));
	// }

	// Line* l3 = new Line(elements3, CENTER);
	// lines.push_back(l3);

	lines.push_back(NULL);
	for( int i = 0 ; i < Students.size() ; i++ )
	{
		vector<Element*>** elements = new vector<Element*>*;
		*elements = new vector<Element*>;

		(*elements)->push_back(new Element( 20, "  " + Students[i] + "         " , STRING, false, false, RED, false));
		// for( int j = 0 ; j < marks.size() ; j++ )
		// {
			(*elements)->push_back(new Element( 15, to_string(marks[i]) , INT, true, false, BLACK, false));
		// }

		Line** l = new Line*;
		*l = new Line(*elements, CENTER);
		lines.push_back(*l);
	}

    lines.push_back(NULL);

	lines.push_back(NULL);
	vector<Element*>** save = new vector<Element*>*;
	*save = new vector<Element*>;	
	//(*go_back)->push_back(new Element( 4, "    " , STRING, false, false, RED, false));
	(*save)->push_back(new Element( 8, "Save" , STRING, false, true, BLUE, true));
	
	Line* l5 = new Line(*save, CENTER);
	lines.push_back(l5);


    vector<Element*>** exit = new vector<Element*>*;
	*exit = new vector<Element*>;	
	//(*go_back)->push_back(new Element( 4, "    " , STRING, false, false, RED, false));
	(*exit)->push_back(new Element( 8, "Exit" , STRING, false, true, BLUE, true));
	
	Line* l6 = new Line(*exit, CENTER);
	lines.push_back(l6);


    lines.push_back(NULL); lines.push_back(NULL);
    vector<Element*>** h0 = new vector<Element*>*;
	*h0 = new vector<Element*>;	
	//(*go_back)->push_back(new Element( 4, "    " , STRING, false, false, RED, false));
	(*h0)->push_back(new Element( 10, "History 0" , STRING, false, true, BLUE, true));
	
	Line* l7 = new Line(*h0, LEFT);
	lines.push_back(l7);

    vector<Element*>** h1 = new vector<Element*>*;
	*h1 = new vector<Element*>;	
	//(*go_back)->push_back(new Element( 4, "    " , STRING, false, false, RED, false));
	(*h1)->push_back(new Element( 10, "History 1" , STRING, false, true, BLUE, true));
	
	Line* l8 = new Line(*h1, CENTER);
	lines.push_back(l8);

    vector<Element*>** h2 = new vector<Element*>*;
	*h2 = new vector<Element*>;	
	//(*go_back)->push_back(new Element( 4, "    " , STRING, false, false, RED, false));
	(*h2)->push_back(new Element( 10, "History 2" , STRING, false, true, BLUE, true));
	
	Line* l9 = new Line(*h2, RIGHT);
	lines.push_back(l9);

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
    string instructor = "ron";
	vector<string> studentList;
	for(int i=0; i<10; i++)
	{
		studentList.push_back("Student" + to_string(i+1));
	}

	vector<int> marks;
	for(int i=0; i<10; i++)
	{
		marks.push_back(i+1);
	}
    StudentMarks(AdminName, studentList, instructor, marks);
}