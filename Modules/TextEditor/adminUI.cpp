#include "content.h"
#include <iostream>
#include <vector>
using namespace std;

void AdminMenu( string adminName, vector<string> studentList )
{
	Element* e1 = new Element( 20, "Admin DashBoard", STRING, false, true, GREEN, false );
	vector<Element*>* elements1 = new vector<Element*>;
	elements1->push_back(e1);
	Line* l1 = new Line(elements1, CENTER);
	lines.push_back(l1);

	Element* e2 = new Element( 13, "Admin Name :  ", STRING, false, true, GREEN, false );
	vector<Element*>* elements2 = new vector<Element*>;
	elements2->push_back(e2);
	elements2->push_back(new Element( 12, adminName, STRING, false, false, RED, false ));
	Line* l2 = new Line(elements2, CENTER);
	lines.push_back(l2);

	lines.push_back(NULL);

	//                               size, content,   type,   edit , bold, color, clickable
	vector<Element*>* elements3 = new vector<Element*>;
	elements3->push_back(new Element( 20, "    Options:", STRING, false, true, BLUE, false ));
	Line* l3 = new Line(elements3, LEFT);
	lines.push_back(l3);


	vector<string> options;
	options.push_back("Add Student");
	options.push_back("Add Instructor");
	options.push_back("Add Hod");
	options.push_back("Remove Student");
	options.push_back("Remove Instructor");
	options.push_back("Remove Hod");
	options.push_back("View All Users");
	options.push_back("View Log File");
	options.push_back("View Students Marks");

	for( int i = 0 ; i < options.size() ; i++ )
	{
		vector<Element*>** elements = new vector<Element*>*;
		*elements = new vector<Element*>;
		//size, content,   type,   edit , bold, color, clickable

		(*elements)->push_back(new Element( 6, "      " , STRING, false, false, RED, false));
		(*elements)->push_back(new Element( 30, options[i] , STRING, false, false, RED, true));

		Line** l = new Line*;
		*l = new Line(*elements, LEFT);
		lines.push_back(*l);
	}
}

void initialize()
{
	vector<string> studentList;
	for( int i = 0 ; i < 20 ; i++ )
	{
		studentList.push_back("Student " + to_string(i+1));
	}
	AdminMenu("Poorna", studentList);
}
