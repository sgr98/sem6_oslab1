#ifndef CONTENT_H
#define CONTENT_H

#include <iostream>
#include <vector>
using namespace std;

vector<string> getContent(int, int);
void initialize();
void getRightPos(int*, int*);
void getLeftPos(int*, int*);
void getUpPos(int*, int*);
void getDownPos(int*, int*);
void getStartPos(int*, int*);
void focus(int, int);
void unfocus(int, int);
bool enterEditorMode(int*, int*);
void exitEditorMode(int*, int*);
void handleBackSpace(int*, int*);
void insertChar(int*, int*, int);


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


	Element( int size, string content, int type , bool editable, bool bold, int color, bool clickable);

	void setString(string content);
};


class Line
{
	public:
	vector<Element*>* elements;
	int position;

	Line( vector<Element*>* elements , int position );
};

extern vector<Line*> lines;

#endif
