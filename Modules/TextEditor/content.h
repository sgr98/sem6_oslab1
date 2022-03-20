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

#endif
