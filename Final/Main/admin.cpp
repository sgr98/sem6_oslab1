#include "./../UI/content.h"
#include <iostream>
#include <vector>
#include "./../UI/editor.h"
#include "./../Admin/adminHelper.h"
using namespace std;

//adminMenu = 1
//list of users = 2
//students marks = 3
//confirmation = 4
int currentPage;
string AdminName;

void showAdminMenu()
{
	lines.clear();
	Element* e1 = new Element( 20, "Admin DashBoard", STRING, false, true, GREEN, false );
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

void StudentMarks(vector<string> Instructors, vector<string> Students, vector<vector<int>> marks)
{
	lines.clear();
	Element* e1 = new Element( 20, "Admin DashBoard", STRING, false, true, GREEN, false );
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

	vector<Element*>** go_back = new vector<Element*>*;
	*go_back = new vector<Element*>;	
	(*go_back)->push_back(new Element( 4, "    " , STRING, false, false, RED, false));
	(*go_back)->push_back(new Element( 30, "Go Back" , STRING, false, false, BLUE, true));
	
	Line* l5 = new Line(*go_back, LEFT);
	lines.push_back(l5);
}

void Confirmation(string message)
{
	lines.clear();
	lines.push_back(NULL);
	lines.push_back(NULL);
	lines.push_back(NULL);

	vector<Element*>** mes = new vector<Element*>*;
	*mes = new vector<Element*>;	
	(*mes)->push_back(new Element( 45, " "+message+" " , STRING, false, false, BLUE, false));
	Line** l1 = new Line*;
	*l1 = new Line(*mes, CENTER);
	lines.push_back(*l1);

	lines.push_back(NULL);
	lines.push_back(NULL);

	vector<Element*>** yes = new vector<Element*>*;
	*yes = new vector<Element*>;	
	(*yes)->push_back(new Element( 30, "            Yes            " , STRING, false, false, GREEN, true));
	Line** l2 = new Line*;
	*l2 = new Line(*yes, CENTER);
	lines.push_back(*l2);


	vector<Element*>** no = new vector<Element*>*;
	*no = new vector<Element*>;	
	(*no)->push_back(new Element( 30, "            No            " , STRING, false, false, RED, true));
	Line** l3 = new Line*;
	*l3 = new Line(*no, CENTER);
	lines.push_back(*l3);
}

void ListOfusers( string adminName, vector<string> userList, vector<string> groupList )
{
	lines.clear();
	Element* e1 = new Element( 20, "Admin DashBoard", STRING, false, true, GREEN, false );
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

	Element* e10 = new Element( 20, "All Users List", STRING, false, true, GREEN, false );
	vector<Element*>* elements10 = new vector<Element*>;
	elements10->push_back(e10);
	Line* l10 = new Line(elements10, CENTER);
	lines.push_back(l10);

	lines.push_back(NULL);

	//                               size, content,   type,   edit , bold, color, clickable
	vector<Element*>* elements3 = new vector<Element*>;
	elements3->push_back(new Element( 20, "    Users:", STRING, false, true, BLUE, false ));
	Line* l3 = new Line(elements3, LEFT);
	lines.push_back(l3);


	for( int i = 0 ; i < userList.size() ; i++ )
	{
		vector<Element*>** elements = new vector<Element*>*;
		*elements = new vector<Element*>;
		//size, content,   type,   edit , bold, color, clickable

		(*elements)->push_back(new Element( 6, "      " , STRING, false, false, RED, false));
		(*elements)->push_back(new Element( 20, userList[i] , STRING, false, false, RED, false));
		(*elements)->push_back(new Element( 30, groupList[i] , STRING, false, false, RED, false));

		Line** l = new Line*;
		*l = new Line(*elements, LEFT);
		lines.push_back(*l);
	}
	lines.push_back(NULL);

	vector<Element*>** go_back = new vector<Element*>*;
	*go_back = new vector<Element*>;	
	(*go_back)->push_back(new Element( 4, "    " , STRING, false, false, RED, false));
	(*go_back)->push_back(new Element( 30, "Go Back" , STRING, false, false, BLUE, true));
	Line** l = new Line*;
	*l = new Line(*go_back, LEFT);
	lines.push_back(*l);
}

void addStudent()
{
	ExitEditorMode();
	cout << "Enter the username of the Student" << endl;
	string username;
	cin >> username;
	if( !checkIfUserExists(username) )
	{
		createStudent( username );
	}
	else
	{
		cout << "User with the name '" << username << "' already exists" << endl;
	}
	enterEditorMode();
}

void addInstructor()
{
	ExitEditorMode();
	cout << "Enter the username of the Instructor" << endl;
	string username;
	cin >> username;
	if( !checkIfUserExists(username) )
	{
		createInstructor(username);
	}
	else
	{
		cout << "User with the name '" << username << "' already exists" << endl;
	}
	enterEditorMode();
}

void addHod()
{
	ExitEditorMode();
	cout << "Enter the username of the HOD" << endl;
	string username;
	cin >> username;
	if( !checkIfUserExists(username) )
	{
		createHod(username);
	}
	else
	{
		cout << "User with the name '" << username << "' already exists" << endl;
	}
	enterEditorMode();
}

void rmStudent()
{
	ExitEditorMode();
	cout << "Enter the username of the Student" << endl;
	string username;
	cin >> username;
	bool b = checkIfUserExists(username);
	if( b )
	{
		removeStudent(username);
	}
	else
	{
		cout << "User with the name '" << username << "' doesn't exist" << endl;
	}
	enterEditorMode();
}

void rmInstructor()
{
	ExitEditorMode();
	cout << "Enter the username of the Instructor" << endl;
	string username;
	cin >> username;
	if( checkIfUserExists(username) )
	{
		removeInstructor(username);
	}
	else
	{
		cout << "User with the name '" << username << "' doesn't exist" << endl;
	}
	enterEditorMode();
}

void rmHod()
{
	ExitEditorMode();
	cout << "Enter the username of the Hod" << endl;
	string username;
	cin >> username;
	if( checkIfUserExists(username) )
	{
		removeHod(username);
	}
	else
	{
		cout << "User with the name '" << username << "' doesn't exist" << endl;
	}
	enterEditorMode();
}
void handleButtonClick( string selection )
{
	cout << "selection = " << selection << endl;
	if( currentPage == 1 )
	{
		if( selection == "View All Users" )
		{
			currentPage = 2;
			vector<string> appUserlist;
			vector<string> userlist = getUserList();
			vector<string> groupList;

			for( int i= 0 ; i < userlist.size() ; i++ )
			{
				vector<string> groups = getGroupsBelonging( userlist[i]);
				for( int j = 0 ; j < groups.size() ; j++)
				{
					if( groups[j] == "Faculty" or groups[j] == "students" or groups[j] == "hods")
					{
						appUserlist.push_back(userlist[i]);
						groupList.push_back(groups[j]);
					}
				}
			}

			ListOfusers("leo", appUserlist, groupList);
		}
		else if( selection == "View Students Marks")
		{
			currentPage = 3;
			vector<string> studentList;
			for( int i = 0 ; i < 5 ; i++ )
			{
				studentList.push_back("Student " + to_string(i+1));
			}

			vector<string> instructor;
			for(int i=0; i< 5; i++)
			{
				instructor.push_back("Instructor" + to_string(i+1));
			}

			vector<vector<int>> marks;
			for(int i =0; i<5; i++)
			{
				vector<int> temp;
				for(int j=0; j<5; j++)
				{
					temp.push_back(j*2);
				}
				marks.push_back(temp);
			}
			StudentMarks(instructor, studentList, marks);
		}
		else if( selection == "Add Student" )
		{
			addStudent();
		}
		else if( selection == "Add Instructor" )
		{
			addInstructor();
		}
		else if( selection == "Add Hod" )
		{
			addHod();
		}
		else if( selection == "Remove Student" )
		{
			rmStudent();
		}
		else if( selection == "Remove Instructor" )
		{
			rmInstructor();
		}
		else if( selection == "Remove Hod" )
		{
			rmHod();
		}
	}
	else if( currentPage == 2 )
	{
		if( selection == "Go Back" )
		{
			currentPage = 1;
			showAdminMenu();
		}
	}
	else if( currentPage == 3 )
	{
		if( selection == "Go Back" )
		{
			currentPage = 1;
			showAdminMenu();
		}
	}  
	initEditor();
	return;
}

bool enterEditorMode( int* x, int* y )
{
	for( int j = 0 ; j < (*(*lines[*y]).elements).size() ; j++ )
	{
		if( (*(*lines[*y]).elements)[j]->start == *x )
		{
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

void initialize( string user )
{
	AdminName = user;
	currentPage = 1;
	showAdminMenu();
}
