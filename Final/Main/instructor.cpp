#include "./../UI/content.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include "./../UI/editor.h" 
#include "./../Student/student.h"
#include "./../Instructor/instructor_marks_list.h"
using namespace std;

int stoi(string str){
    int num = 0;
    int i = 0;
    bool isNegetive = false;
    if(str[i] == '-'){
        isNegetive = true;
        i++;
    }
    while (str[i] && (str[i] >= '0' && str[i] <= '9')){
        num = num * 10 + (str[i] - '0');
        i++;
    }
    if(isNegetive) num = -1 * num;
    return num;
}

int currentHistory;
string instructorName;
vector<int> marks;

vector<string> getGroupsBelonging( string username )
{
	vector<string> groups{"students", "Faculty", "admins", "hods"};
	vector<string> result;
	char filepath[] = "/etc/group";
	int fd = open(filepath, O_RDONLY);
	if( fd == -1 )
	{
		cout << "Error while opening /etc/group file, cannot verify user's group" << endl;
		return result;
	}

	long int size = lseek(fd, 0l, SEEK_END);
	lseek(fd, 0l, SEEK_SET);
	char* c = (char*) calloc( size, sizeof(char));

	int sizeRead = read(fd, c, size);
	c[size] = '\0';


	char* token = strtok(c, "\n");

	vector<string> lines;
	while( token != NULL )
	{
		lines.push_back(token);
		token = strtok(NULL,"\n");
	}

	for( int l = 0 ; l < lines.size() ; l++ )
	{
		vector<string> words;
		char t[lines[l].size()];
		strcpy(t, lines[l].c_str());

		token = strtok(t, ":");
		while( token != NULL )
		{
			words.push_back(token);
			token = strtok(NULL, ":");
		}

		for( int i = 0 ; i < groups.size() ; i++ )
		{
			if( groups[i] == words[0] and words.size() == 4)
			{
				vector<string> listOfUsers;

				char s[words[words.size()-1].size()];
				strcpy(s, words[words.size()-1].c_str() );
				token = strtok(s, ",");
				while( token != NULL )
				{
					listOfUsers.push_back(token);
					token = strtok(NULL, ",");
				}
				for( int j = 0 ; j < listOfUsers.size() ; j++ )
				{
					if( listOfUsers[j] == username )
					{
						result.push_back(groups[i]);
					}
				}
			}
		}

	}
	return result;
}

void StudentMarks(string AdminName, vector<string> Students, string Instructor, vector<int> marks) {
	lines.clear();
	Element* e1 = new Element( 20, "Instructor DashBoard", STRING, false, true, GREEN, false );
	vector<Element*>* elements1 = new vector<Element*>;
	elements1->push_back(e1);
	Line* l1 = new Line(elements1, CENTER);
	lines.push_back(l1);

	Element* e2 = new Element( 20, "Instructor Name :  ", STRING, false, true, GREEN, false );
	vector<Element*>* elements2 = new vector<Element*>;
	elements2->push_back(e2); elements2->push_back(new Element( 12, Instructor, STRING, false, false, RED, false ));
	Line* l2 = new Line(elements2, CENTER);
	lines.push_back(l2);

	lines.push_back(NULL);

	Element* e10 = new Element( 10, "Marks List", STRING, false, true, GREEN, false );
	vector<Element*>* elements10 = new vector<Element*>;
	elements10->push_back(e10);
	Line* l10 = new Line(elements10, CENTER);
	lines.push_back(l10);

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

	for( int i = 0 ; i < Students.size() ; i++ )
	{
		vector<Element*>** elements = new vector<Element*>*;
		*elements = new vector<Element*>;

		(*elements)->push_back(new Element( 20, "  " + Students[i] + "         " , STRING, false, false, RED, false));
		// for( int j = 0 ; j < marks.size() ; j++ )
		// {
			if( currentHistory == 1 )
			{
				(*elements)->push_back(new Element( 15, to_string(marks[i]) , INT, true, false, BLACK, false));
			}
			else
			{
				(*elements)->push_back(new Element( 15, to_string(marks[i]) , INT, false, false, BLACK, false));
			}
		// }

		Line** l = new Line*;
		*l = new Line(*elements, CENTER);
		lines.push_back(*l);
	}

    lines.push_back(NULL);

	lines.push_back(NULL);
	vector<Element*>** save = new vector<Element*>*;
	*save = new vector<Element*>;	
	(*save)->push_back(new Element( 8, "Save" , STRING, false, true, BLUE, true));
	(*save)->push_back(new Element( 8, "      " , STRING, false, true, BLUE, false));
	(*save)->push_back(new Element( 20, "Discard Changes" , STRING, false, true, BLUE, true));
	
	Line* l5 = new Line(*save, CENTER);
	lines.push_back(l5);


	lines.push_back(NULL);
    vector<Element*>** exit = new vector<Element*>*;
	*exit = new vector<Element*>;	
	//(*go_back)->push_back(new Element( 4, "    " , STRING, false, false, RED, false));
	(*exit)->push_back(new Element( 9, "Download" , STRING, false, true, BLUE, true));
	
	Line* l6 = new Line(*exit, CENTER);
	lines.push_back(l6);


    lines.push_back(NULL); lines.push_back(NULL);
    vector<Element*>** h0 = new vector<Element*>*;
	*h0 = new vector<Element*>;	
	//(*go_back)->push_back(new Element( 4, "    " , STRING, false, false, RED, false));
	(*h0)->push_back(new Element( 10, "History 0" , STRING, false, true, BLUE, true));
	(*h0)->push_back(new Element( 10, "      " , STRING, false, true, BLUE, false));
	(*h0)->push_back(new Element( 10, "History 1" , STRING, false, true, BLUE, true));
	(*h0)->push_back(new Element( 10, "      " , STRING, false, true, BLUE, false));
	(*h0)->push_back(new Element( 10, "History 2" , STRING, false, true, BLUE, true));
	
	Line* l7 = new Line(*h0, CENTER);
	lines.push_back(l7);
	lines.push_back(NULL);

    vector<Element*>** h1 = new vector<Element*>*;
	*h1 = new vector<Element*>;	
	(*h1)->push_back(new Element( 20, "Revert to History 1" , STRING, false, true, BLUE, true));
	(*h1)->push_back(new Element( 6, "    " , STRING, false, true, BLUE, false));
	(*h1)->push_back(new Element( 20, "Revert to History 2" , STRING, false, true, BLUE, true));
	
	Line* l8 = new Line(*h1, CENTER);
	lines.push_back(l8);
	lines.push_back(NULL);

    vector<Element*>** h2 = new vector<Element*>*;
	*h2 = new vector<Element*>;	
	(*h2)->push_back(new Element( 15, "Enroll Student" , STRING, false, true, BLUE, true));
	(*h2)->push_back(new Element( 6, "    " , STRING, false, true, BLUE, false));
	(*h2)->push_back(new Element( 15, "Remove Student" , STRING, false, true, BLUE, true));
	
	Line* l9 = new Line(*h2, CENTER);
	lines.push_back(l9);
}

void exitEditorMode( int* x, int* y)
{
	for( int j = 0 ; j < (*(*lines[*y]).elements).size() ; j++ )
	{
		if( (*(*lines[*y]).elements)[j]->start <= *x and (*(*lines[*y]).elements)[j]->end >= *x)
		{
			if( (*(*lines[*y]).elements)[j]->content.size() == 0 )
			{
				(*(*lines[*y]).elements)[j]->content = "0";
			}
			(*(*lines[*y]).elements)[j]->underlined = false;
			(*(*lines[*y]).elements)[j]->invert = true;
			*x = (*(*lines[*y]).elements)[j]->start;
		}
	}
}

void handleBackSpace( int* x, int* y )
{
	for( int j = 0 ; j < (*(*lines[*y]).elements).size() ; j++ )
	{
		int size = (*(*lines[*y]).elements)[j]->content.size();
		if( (*(*lines[*y]).elements)[j]->start + size == *x )
		{
			string str = (*(*lines[*y]).elements)[j]->content;
			(*(*lines[*y]).elements)[j]->content = str.substr(0, str.length()-1);
			size = (*(*lines[*y]).elements)[j]->content.size();
			*x = (*(*lines[*y]).elements)[j]->start + size;
			return;
		}
	}
}

void insertChar( int* x, int* y , int c)
{
	for( int j = 0 ; j < (*(*lines[*y]).elements).size() ; j++ )
	{
		int size = (*(*lines[*y]).elements)[j]->content.size();
		if( (*(*lines[*y]).elements)[j]->start + size == *x )
		{
			if( (*(*lines[*y]).elements)[j]->type == INT )
			{
				if( c < (int)'0' or c > (int)'9' )
				{
					return;
				}
			}
			string str = (*(*lines[*y]).elements)[j]->content;
			if( str.size() < (*(*lines[*y]).elements)[j]->size - 1)
			{
				(*(*lines[*y]).elements)[j]->content = str + (char)c;
			}
			size = (*(*lines[*y]).elements)[j]->content.size();
			*x = (*(*lines[*y]).elements)[j]->start + size;
			return;
		}
	}
}

void restoreMarks()
{
	currentHistory = 1;

	InstructorMarksList instructor_marks_list;

	vector<pair<string, float>> list = instructor_marks_list.getMarksList("./Database/Instructors/" + instructorName + "/hist0.txt");

	vector<string> studentList;
	for(int i=0; i< list.size(); i++)
	{
		studentList.push_back(list[i].first);
	}

	StudentMarks(instructorName, studentList, instructorName, marks);
}

void editorProcessKeypress()
{
	int c = editorReadKey();

	switch(c)
	{
		case '\n':
		case '\r':
			//exitEditorMode(&E.cx, &E.cy);
			if( E.mode == NAVIGATION )
			{
				if( enterEditorMode( &E.cx, &E.cy ) )
				{
					E.mode = EDIT;
				}
			}
			else if( E.mode == EDIT )
			{
				E.mode = NAVIGATION;
				exitEditorMode(&E.cx, &E.cy);
			}
			break;
		case'q':
			ExitEditorMode();
			exit(0);
			break;
		case '\033':
			E.mode = NAVIGATION;
			restoreMarks();
			break;
		case ARROW_UP:
		case ARROW_DOWN:
		case ARROW_LEFT:
		case ARROW_RIGHT:
			if( E.mode == NAVIGATION )
			{
				editorMoveCursor(c);
			}
			break;
		case BACKSPACE:
			if( E.mode == EDIT )
			{
				handleBackSpace(&E.cx, &E.cy);
			}
			break;
		default:
			if( E.mode == EDIT )
			{
				insertChar(&E.cx, &E.cy, c);
			}
			break;
	}
}

void setMarksList()
{
	for( int i = 5 ; ; i++ )
	{
		if(	lines[i] == NULL )
		{
			break;
		}
		marks[i-5] = stoi((*(*lines[i]).elements)[1]->content);
	}
}

void setPermissions( string permission )
{
	system(permission.c_str());
}

void handleButtonClick( string selection )
{
	if( selection == "Download" )
	{
		ExitEditorMode();

		cout << "Enter the File name of the downloaded Marks (with the extension)" << endl;
		string fileName;
		cin >> fileName;

		InstructorMarksList instructor_marks_list;

		string prefix = "./Database/Instructors/" + instructorName + "/hist" + to_string(currentHistory-1) + ".txt";
		instructor_marks_list.downloadAllinstructorMarks(prefix, fileName);

		/*
		setPermissions("setfacl -m g::--- ./" + fileName);
		setPermissions("setfacl -m u::rwx ./" + fileName);
		setPermissions("setfacl -m o::--- ./" + fileName);
		*/

		//setPermissions("sudo chown " + instructorName + ": ./" + fileName);

		cout << "Successfully created file and set permissions" << endl;
		enterEditorMode();
	}
	else if( selection ==  "Save" )
	{
		setMarksList();

		InstructorMarksList instructor_marks_list;

		vector<pair<string, float>> list = instructor_marks_list.getMarksList("./Database/Instructors/" + instructorName + "/hist0.txt");

		for( int i = 0 ; i < marks.size() ; i++ )
		{
			list[i].second = marks[i];
		}

		string prefix = "./Database/Instructors/" + instructorName + "/hist";

		instructor_marks_list.setInstructorMarkList( list );
		cout << "save edit is going to be called" << endl;

		instructor_marks_list.saveEdit(prefix + "0.txt", prefix + "1.txt", prefix + "2.txt" );
	}
	else if( selection == "Discard Changes" )
	{
		currentHistory = 1;

		InstructorMarksList instructor_marks_list;

		vector<pair<string, float>> list = instructor_marks_list.getMarksList("./Database/Instructors/" + instructorName + "/hist0.txt");

		vector<string> studentList;
		marks.clear();

		for(int i=0; i< list.size(); i++)
		{
			studentList.push_back(list[i].first);
			marks.push_back((int)list[i].second);
		}

		StudentMarks(instructorName, studentList, instructorName, marks);
	}
	else if( selection == "History 0" )
	{
		currentHistory = 1;

		InstructorMarksList instructor_marks_list;

		vector<pair<string, float>> list = instructor_marks_list.getMarksList("./Database/Instructors/" + instructorName + "/hist0.txt");

		vector<string> studentList;
		marks.clear();

		for(int i=0; i< list.size(); i++)
		{
			studentList.push_back(list[i].first);
			marks.push_back((int)list[i].second);
		}

		StudentMarks(instructorName, studentList, instructorName, marks);
	}
	else if( selection == "History 1" )
	{
		currentHistory = 2;

		InstructorMarksList instructor_marks_list;

		vector<pair<string, float>> list = instructor_marks_list.getMarksList("./Database/Instructors/" + instructorName + "/hist1.txt");

		vector<string> studentList;
		marks.clear();

		for(int i=0; i< list.size(); i++)
		{
			studentList.push_back(list[i].first);
			marks.push_back((int)list[i].second);
		}

		StudentMarks(instructorName, studentList, instructorName, marks);
	}
	else if( selection == "History 2" )
	{
		currentHistory = 3;

		InstructorMarksList instructor_marks_list;

		vector<pair<string, float>> list = instructor_marks_list.getMarksList("./Database/Instructors/" + instructorName + "/hist2.txt");

		vector<string> studentList;
		marks.clear();

		for(int i=0; i< list.size(); i++)
		{
			studentList.push_back(list[i].first);

			marks.push_back((int)list[i].second);
		}

		StudentMarks(instructorName, studentList, instructorName, marks);
	}
	else if( selection == "Revert to History 1" )
	{
		currentHistory = 1;

		InstructorMarksList instructor_marks_list;

		instructor_marks_list.revertHistory1("./Database/Instructors/" + instructorName + "/hist0.txt", "./Instructors/" + instructorName + "/hist1.txt");

		vector<pair<string, float>> list = instructor_marks_list.getMarksList("./Database/Instructors/" + instructorName + "/hist0.txt");

		vector<string> studentList;
		marks.clear();

		for(int i=0; i< list.size(); i++)
		{
			studentList.push_back(list[i].first);

			marks.push_back((int)list[i].second);
		}

		StudentMarks(instructorName, studentList, instructorName, marks);
	}
	else if( selection == "Revert to History 2" )
	{
		currentHistory = 1;

		InstructorMarksList instructor_marks_list;

		instructor_marks_list.revertHistory2("./Database/Instructors/" + instructorName + "/hist0.txt", "./Database/Instructors/" + instructorName + "/hist1.txt", "./Database/Instructors/" + instructorName + "/hist2.txt");

		vector<pair<string, float>> list = instructor_marks_list.getMarksList("./Database/Instructors/" + instructorName + "/hist0.txt");

		vector<string> studentList;
		marks.clear();

		for(int i=0; i< list.size(); i++)
		{
			studentList.push_back(list[i].first);

			marks.push_back((int)list[i].second);
		}

		StudentMarks(instructorName, studentList, instructorName, marks);
	}
	else if( selection == "Enroll Student" )
	{
		ExitEditorMode();
		string hist0 = "./Database/Instructors/" + instructorName + "/hist0.txt";
		string hist1 = "./Database/Instructors/" + instructorName + "/hist1.txt";
		string hist2 = "./Database/Instructors/" + instructorName + "/hist2.txt";


		cout << "Enter the student name" << endl;
		string stname;
		cin >> stname;
		vector<string> groups = getGroupsBelonging(stname);
		bool b = false;
		for( int i= 0 ; i < groups.size() ; i++ )
		{
			if( groups[i] == "students" )
			{
				b = true;
				break;
			}
		}

		if( b == false )
		{
			cout << "There is no student called " << stname << endl;
		}
		else
		{
			InstructorMarksList instructor_marks_list;
			instructor_marks_list.addMark(hist0, stname, 0);
			instructor_marks_list.addMark(hist1, stname, 0);
			instructor_marks_list.addMark(hist2, stname, 0);

			Student student;
			student.addCourse("./Database/Students/" + stname + ".txt", instructorName);
		}
		currentHistory = 1;

		InstructorMarksList instructor_marks_list;

		vector<pair<string, float>> list = instructor_marks_list.getMarksList("./Database/Instructors/" + instructorName + "/hist0.txt");

		vector<string> studentList;

		for(int i=0; i< list.size(); i++)
		{
			studentList.push_back(list[i].first);
			marks.push_back((int)list[i].second);
		}

		StudentMarks(instructorName, studentList, instructorName, marks);
		enterEditorMode();
	}
	else if( selection == "Remove Student" )
	{
		ExitEditorMode();
		string hist0 = "./Database/Instructors/" + instructorName + "/hist0.txt";
		string hist1 = "./Database/Instructors/" + instructorName + "/hist1.txt";
		string hist2 = "./Database/Instructors/" + instructorName + "/hist2.txt";


		cout << "Enter the student name" << endl;
		string stname;
		cin >> stname;
		vector<string> groups = getGroupsBelonging(stname);
		bool b = false;
		for( int i= 0 ; i < groups.size() ; i++ )
		{
			if( groups[i] == "students" )
			{
				b = true;
				break;
			}
		}

		if( b == false )
		{
			cout << "There is no student called " << stname << endl;
		}
		else
		{
			InstructorMarksList instructor_marks_list;
			instructor_marks_list.removeMark(hist0, stname);
			instructor_marks_list.removeMark(hist1, stname);
			instructor_marks_list.removeMark(hist2, stname);

			Student student;
			student.removeCourse("./Database/Students/" + stname + ".txt", instructorName);
		}
		currentHistory = 1;

		InstructorMarksList instructor_marks_list;

		vector<pair<string, float>> list = instructor_marks_list.getMarksList("./Database/Instructors/" + instructorName + "/hist0.txt");

		vector<string> studentList;

		for(int i=0; i< list.size(); i++)
		{
			studentList.push_back(list[i].first);
			marks.push_back((int)list[i].second);
		}

		StudentMarks(instructorName, studentList, instructorName, marks);
		enterEditorMode();
	}
	return;
} 

bool enterEditorMode( int* x, int* y )
{
	for( int j = 0 ; j < (*(*lines[*y]).elements).size() ; j++ )
	{
		if( (*(*lines[*y]).elements)[j]->start == *x )
		{
			if( (*(*lines[*y]).elements)[j]->clickable == true )
			{

				handleButtonClick((*(*lines[*y]).elements)[j]->content);
				return false;
			}
			else if( (*(*lines[*y]).elements)[j]->editable == true  and currentHistory == 1 )
			{
				(*(*lines[*y]).elements)[j]->underlined = true;
				(*(*lines[*y]).elements)[j]->invert = false;
				//(*(*lines[*y]).elements)[j]->content = "poorna";
				int size = (*(*lines[*y]).elements)[j]->content.size();
				*x = (*(*lines[*y]).elements)[j]->start + size;
				return true;
			}
		}
	}
	return false;
}

void initialize( string user)
{
	currentHistory = 1;
	instructorName = user;

	InstructorMarksList instructor_marks_list;

	vector<pair<string, float>> list = instructor_marks_list.getMarksList("./Database/Instructors/" + instructorName + "/hist0.txt");

	vector<string> studentList;

	for(int i=0; i< list.size(); i++)
	{
		studentList.push_back(list[i].first);
		marks.push_back((int)list[i].second);
	}

	StudentMarks(instructorName, studentList, instructorName, marks);
}
