#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include "content.h"
#include <chrono>
#include <thread>

extern int editorOrNot;

enum mode
{
	EDIT,
	NAVIGATION,
};

struct editorConfig
{
	//this the terminal struct that is used to modify terminal properties
	struct termios orig_termios;
	
	//screen size
	int screenrows;
	int screencols;

	//cursor position
	int cx, cy;

	int mode;
};

extern struct editorConfig E;


//mappings for keypresses
enum editorKey
{
	BACKSPACE = 127,
	ARROW_LEFT = 1000,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	DEL_KEY,
};

struct abuf
{
	char* b;
	int len;
};

void die( const char* s );
void disableRawMode();
void enableRawMode();
void exitRawMode();
void ExitEditorMode();
int editorReadKey();
int getCursorPosition( int *rows , int *cols );
int getWindowSize( int* rows, int* cols );
void abAppend( struct abuf* ab, const char* s, int len);
void abFree(struct abuf* ab);
void editorDrawRows( struct abuf* ab );
void editorRefreshScreen();
void editorMoveCursor( int key );
void initEditor();
void editorProcessKeypress();
void keepRefreshing();
void enterEditorMode();
void ExitRawMode();

