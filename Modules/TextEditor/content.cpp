#include "content.h"
#include <iostream>
#include <vector>
using namespace std;


/*
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

*/

Element::Element( int size, string content, int type , bool editable, bool bold, int color, bool clickable)
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

void Element::setString(string content)
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

Line::Line( vector<Element*>* elements , int position )
{
	this->elements = elements;
	this->position = position;
}

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
	/*
	   if( totalsize > cols )
	   {
	   return "";
	   }
	 */

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
