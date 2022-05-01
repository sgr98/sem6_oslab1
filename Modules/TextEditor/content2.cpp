#include "content.h"
#include <iostream>
#include <vector>
using namespace std;


enum position
{
	CENTER = 0,
	LEFT,
	RIGHT,
};

enum color
{
	BLUE,
	RED,
	GREEN,
	BLACK,
};

enum type
{
	INT = 0,
	STRING,
	CHAR,
};

class Element
{
	public:
	int size;
	int type;
	string content;
	bool editable;
	bool bold;
	int color;
	int start; 
	bool underlined;
	bool invert;
	int end;
	bool clickable;


	Element( int size, string content, int type , bool editable, bool bold, int color, bool clickable)
	{
		this->size = size;
		this->type = type;
		this->editable = editable;
		this->bold = bold;
		this->color = color;
		this->start = 0;
		this->end = 0;
		this->underlined = 0;
		this->invert = 0;
		this->clickable = clickable;
		setString(content);
	}

	void setString(string content)
	{
		if( content.size() > size )
		{
			this->content = content.substr(0, size);
		}
		else
		{
			this->content = content;
		}
	}
};


class Line
{
	public:
	vector<Element*>* elements;
	int position;

	Line( vector<Element*>* elements , int position )
	{
		this->elements = elements;
		this->position = position;
	}
};

string getLine( Line* l, int cols )
{
	if( l == NULL or l->elements == NULL )
	{
		return "";
	}
	vector<Element*> elements = *(l->elements);
	int current = 0;
	string line = "";
	int totalsize = 0;
	for( int i = 0 ; i < elements.size() ; i++ )
	{
		totalsize += elements[i]->size;
	}
	if( totalsize > cols )
	{
		return "";
	}

	switch( l->position )
	{
		case CENTER:
			for( int i = 0 ; i < (cols-totalsize)/2 ; i++ )
			{
				line += " ";
				current++;
			}
			break;
		case LEFT:
			break;
		case RIGHT:
			for( int i = 0 ; i < (cols-totalsize) ; i++ )
			{
				line += " ";
				current++;
			}
			break;
			
	}

	for( int i = 0 ; i < elements.size() ; i++ )
	{
		elements[i]->start = current;
		switch(elements[i]->color)
		{
			case BLUE:
				line += "\033[34m";
				break;
			case RED:
				line += "\033[31m";
				break;
			case GREEN:
				line += "\033[32m";
				break;
			case BLACK:
				line += "\033[39m";
				break;
		}

		if( elements[i]->bold )
		{
			line += "\033[1m";
		}

		if( elements[i]->underlined )
		{
			line += "\033[4m";
		}
		
		if( elements[i]->invert )
		{
			line += "\033[7m";
		}

		line += elements[i]->content;

		line += "\033[0m";
		for( int j = 0 ; j < elements[i]->size - elements[i]->content.size() ; j++ )
		{
			line += " ";
		}
		current += elements[i]->size;
		elements[i]->end = current-1;
	}
	return line;
}


void print(Element e)
{
	cout << "content\tsize\ttype\tedit\tbold\tcolor\tstart\tend\tunline\tinvert\tclick" << endl;
	cout << e.content << "\t" << e.size << "\t" <<  e.type << "\t" << e.editable << "\t" << e.bold << "\t" << e.color << "\t" << e.start << "\t" << e.end  << "\t" << e.underlined << "\t" << e.invert << "\t" << e.clickable << endl;
}

vector<Line*> lines;


vector<string> getContent( int rows, int cols )
{
	vector<string> content;

	int noOfLines = lines.size();
	if( noOfLines > rows )
	{
		noOfLines = rows;
	}

	for( int i = 0 ; i < noOfLines ; i++ )
	{
		content.push_back(getLine(lines[i],  cols));
	}

	return content;
}

void getStartPos(int* x, int* y)
{
	for( int i = 0 ; i < lines.size() ; i++ )
	{
		if( lines[i] != NULL )
		{
			for( int j = 0 ; j < (*(*lines[i]).elements).size() ; j++ )
			{
				if( (*(*lines[i]).elements)[j]->editable == true or (*(*lines[i]).elements)[j]->clickable == true )
				{
					*y = i;
					*x = (*(*lines[i]).elements)[j]->start;
					return;
				}
			}
		}
	}
}

void getRightPos( int* x, int* y)
{
	for( int j = 0 ; j < (*(*lines[*y]).elements).size() ; j++ )
	{
		if( (*(*lines[*y]).elements)[j]->start > *x )
		{
			if( (*(*lines[*y]).elements)[j]->editable == true or (*(*lines[*y]).elements)[j]->clickable == true )
			{
				*y = *y;
				*x = (*(*lines[*y]).elements)[j]->start;
				return;
			}
		}
	}
}

void getLeftPos( int* x, int* y )
{
	for( int j = (*(*lines[*y]).elements).size()-1 ; j >= 0 ; j-- )
	{
		if( (*(*lines[*y]).elements)[j]->start < *x )
		{
			if( (*(*lines[*y]).elements)[j]->editable == true or (*(*lines[*y]).elements)[j]->clickable == true )
			{
				*y = *y;
				*x = (*(*lines[*y]).elements)[j]->start;
				return;
			}
		}
	}
}

void getUpPos( int* x, int* y )
{	
	if( *y == 0 )
	{
		return;
	}
	int count = 0;
	for( int j = 0 ; j < (*(*lines[*y]).elements).size() ; j++ )
	{
		count++;
		if( (*(*lines[*y]).elements)[j]->start == *x )
		{
			break;
		}
	}

	for( int i = *y-1 ; i >= 0 ; i-- )
	{
		if( lines[i] != NULL )
		{
			if( count <= (*(*lines[i]).elements).size() )
			{
				if( (*(*lines[i]).elements)[count-1]->editable == true or (*(*lines[i]).elements)[count-1]->clickable == true )
				{
					*y = i;
					*x = (*(*lines[*y]).elements)[count-1]->start;
					return;
				}
			}
			for( int j = 0 ; j < (*(*lines[i]).elements).size() ; j++ )
			{
				if( (*(*lines[i]).elements)[j]->editable == true or (*(*lines[i]).elements)[j]->clickable == true )
				{
					*y = i;
					*x = (*(*lines[i]).elements)[j]->start;
					return;
				}
			}
		}
	}
}

void getDownPos( int* x, int* y )
{
	if( *y >= lines.size()-1 )
	{
		return;
	}
	int count = 0;
	for( int j = 0 ; j < (*(*lines[*y]).elements).size() ; j++ )
	{
		count++;
		if( (*(*lines[*y]).elements)[j]->start == *x )
		{
			break;
		}
	}

	for( int i = *y+1 ; i < lines.size() ; i++ )
	{
		if( lines[i] != NULL )
		{
			/*
			if( count <= (*(*lines[i]).elements).size() )
			{
				if( (*(*lines[i]).elements)[count-1]->editable == true or (*(*lines[i]).elements)[count-1]->clickable == true )
				{
					*y = i;
					*x = (*(*lines[*y]).elements)[count-1]->start;
				}
			}
			else
			{
				*y = i;
				*x = (*(*lines[i]).elements)[(*(*lines[i]).elements).size()-1]->start;
			}
			return;
			*/

			if( count <= (*(*lines[i]).elements).size() )
			{
				if( (*(*lines[i]).elements)[count-1]->editable == true or (*(*lines[i]).elements)[count-1]->clickable == true )
				{
					*y = i;
					*x = (*(*lines[*y]).elements)[count-1]->start;
					return;
				}
			}
			for( int j = 0 ; j < (*(*lines[i]).elements).size() ; j++ )
			{
				if( (*(*lines[i]).elements)[j]->editable == true or (*(*lines[i]).elements)[j]->clickable == true )
				{
					*y = i;
					*x = (*(*lines[i]).elements)[j]->start;
					return;
				}
			}
		}
	}
}

void focus( int x, int y )
{
	for( int j = 0 ; j < (*(*lines[y]).elements).size() ; j++ )
	{
		if( (*(*lines[y]).elements)[j]->start == x )
		{
			(*(*lines[y]).elements)[j]->invert = true;
			return;
		}
	}
}

void unfocus( int x, int y )
{
	for( int j = 0 ; j < (*(*lines[y]).elements).size() ; j++ )
	{
		if( (*(*lines[y]).elements)[j]->start == x )
		{
			(*(*lines[y]).elements)[j]->invert = false;
			return;
		}
	}
}

bool enterEditorMode( int* x, int* y )
{
	for( int j = 0 ; j < (*(*lines[*y]).elements).size() ; j++ )
	{
		if( (*(*lines[*y]).elements)[j]->start == *x )
		{
			if( (*(*lines[*y]).elements)[j]->editable == false )
			{
				return false;
			}
			(*(*lines[*y]).elements)[j]->underlined = true;
			(*(*lines[*y]).elements)[j]->invert = false;
			int size = (*(*lines[*y]).elements)[j]->content.size();
			*x = (*(*lines[*y]).elements)[j]->start + size;

			return true;
		}
	}
	return false;
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







void ListOfusers( string adminName, vector<string> userList )
{
	Element* e1 = new Element( 20, "All Users List", STRING, false, true, GREEN, false );
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
	elements3->push_back(new Element( 20, "    Users:", STRING, false, true, BLUE, false ));
	Line* l3 = new Line(elements3, LEFT);
	lines.push_back(l3);
	

	for( int i = 0 ; i < userList.size() ; i++ )
	{
		vector<Element*>** elements = new vector<Element*>*;
		*elements = new vector<Element*>;
		//size, content,   type,   edit , bold, color, clickable

		(*elements)->push_back(new Element( 6, "      " , STRING, false, false, RED, false));
		(*elements)->push_back(new Element( 30, userList[i] , STRING, false, false, RED, false));
		
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

void Confirmation(string message)
{
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

	// (*go_back)->push_back(new Element( 3, "Yes" , STRING, false, false, BLUE, true));
	// Line** l = new Line*;
	// *l = new Line(*go_back, LEFT);
	// lines.push_back(*l);
}



void StudentMarks(string adminName, vector<string> Instructors, vector<string> Students, vector<vector<int>> marks)
{
	Element* e1 = new Element( 20, "Students Marks List", STRING, false, true, GREEN, false );
	vector<Element*>* elements1 = new vector<Element*>;
	elements1->push_back(e1);
	Line* l1 = new Line(elements1, CENTER);
	lines.push_back(l1);

	Element* e2 = new Element( 14, "Admin Name :  ", STRING, false, true, GREEN, false );
	vector<Element*>* elements2 = new vector<Element*>;
	elements2->push_back(e2);
	elements2->push_back(new Element( 12, adminName, STRING, false, false, RED, false ));
	Line* l2 = new Line(elements2, CENTER);
	lines.push_back(l2);

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
			(*elements)->push_back(new Element( 15, to_string(marks[i][j]) , INT, true, false, BLACK, false));
		}

		Line** l = new Line*;
		*l = new Line(*elements, CENTER);
		lines.push_back(*l);
	}
}


void initialize()
{
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
	//Confirmation("Rage, Rage against the dying of the light.");
	//ListOfusers("leo", studentList);
	StudentMarks("max", instructor, studentList, marks);

}


