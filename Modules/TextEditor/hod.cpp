#include "content.h"
#include <iostream>
#include <vector>
#include "editor.h"
#include<unistd.h>
#include<fcntl.h>
#include "../WorkingOfHOD/hod.h"
using namespace std;

vector<string> getUserList()
{
	vector<string> users;
	char filepath[] = "/etc/passwd";
	int fd = open(filepath, O_RDONLY);
	if( fd == -1 )
	{
		cout << "Error: cannot open /etc/passwd file to verify users" << endl;
		return users;
	}

	long int size = lseek(fd, 0l, SEEK_END);
	lseek(fd, 0l, SEEK_SET);
	char* c = (char*) calloc(size, sizeof(char));

	int sizeRead = read(fd, c, size);
	c[size] = '\0';

	string str(c);

	char*token = strtok(c, "\n");

	vector<string>lines;
	while(token != NULL)
	{
		lines.push_back(token);
		token = strtok(NULL, "\n");
	}

	for( int i = 0 ; i < lines.size() ; i++ )
	{
		char t[lines[i].size()];
		strcpy(t, lines[i].c_str());
		token = strtok(t, ":");
		users.push_back(string(token));
	}
	return users;
}

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
			if( marks[i][j] != -1 )
			{
				(*elements)->push_back(new Element( 15, to_string(marks[i][j]) , INT, false, false, BLACK, false));
			}
			else
			{
				(*elements)->push_back(new Element( 15, "--" , INT, false, false, BLACK, false));
			}
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
	if( selection == "Download" )
	{
		vector<string> instructorList;
		vector<string> userlist = getUserList();
		for( int i= 0 ; i < userlist.size() ; i++ )
		{
			vector<string> groups = getGroupsBelonging( userlist[i]);
			for( int j = 0 ; j < groups.size() ; j++)
			{
				if( groups[j] == "Faculty" )
				{
					instructorList.push_back(userlist[i]);
				}
			}
		}

		pair<string, string> instructor_file;

		vector<pair<string, string>> instructorfiles;

		for( int i = 0 ; i < instructorList.size() ; i++ )
		{
			instructor_file.first = instructorList[i];
			instructor_file.second = "./Instructors/" + instructorList[i] + "/";

			instructorfiles.push_back(instructor_file);
		}

		downloadAllStudentsInstructorMarks("./EntireMarks.txt", instructorfiles);
	}
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
	string hodName = "hod1";

	vector<string> instructorList;
	vector<string> studentList;
	vector<string> userlist = getUserList();
	for( int i= 0 ; i < userlist.size() ; i++ )
	{
		vector<string> groups = getGroupsBelonging( userlist[i]);
		for( int j = 0 ; j < groups.size() ; j++)
		{
			if( groups[j] == "Faculty" )
			{
				instructorList.push_back(userlist[i]);
			}
			else if( groups[j] == "students" )
			{
				studentList.push_back(userlist[i]);
			}
		}
	}

	pair<string, string> instructor_file;

	vector<pair<string, string>> instructorfiles;

	for( int i = 0 ; i < instructorList.size() ; i++ )
	{
		instructor_file.first = instructorList[i];
		instructor_file.second = "./Instructors/" + instructorList[i] + "/";

		instructorfiles.push_back(instructor_file);
	}

	vector<pair<string, vector<float>>> table = getAllStudentInstructorMarks(instructorfiles);

	for( int i = 0 ; i < studentList.size() ; i++ )
	{
		bool b = false;
		for( int j = 0 ; j < table.size() ; j++ )
		{
			if( table[j].first == studentList[i] )
			{
				b = true;
				break;
			}
		}

		pair<string, vector<float>> studentMarks;
		if( b == false )
		{
			studentMarks.first = studentList[i];
			vector<float> f;
			for( int j = 0 ; j < table[0].second.size() ; j++ )
			{
				f.push_back(-1);
			}
			studentMarks.second = f;

			table.push_back(studentMarks);
		}
	}

	vector<string> stList;
	vector<vector<int>> marks;

	for( int i = 0 ; i < table.size() ; i++ )
	{
		stList.push_back(table[i].first);
		vector<int> temp;
		for( int j = 0 ; j < table[i].second.size() ; j++ )
		{
			temp.push_back((int)table[i].second[j]);
		}
		marks.push_back(temp);
	}




	for(int i =0; i<instructorList.size(); i++)
	{
		vector<int> temp;
		for(int j=0; j<instructorList.size(); j++)
		{
			temp.push_back(j*2);
		}
		marks.push_back(temp);
	}

	StudentMarks(hodName, instructorList, stList, marks);
}
