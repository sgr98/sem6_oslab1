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

enum mode
{
	EDIT,
	NAVIGATION,
};

using namespace std;

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

struct editorConfig E;


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

//function to handle error
void die( const char* s )
{
	//clear the screen and reposition the cursor
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	perror(s);
	exit(1);
}

//Disables Raw mode
void disableRawMode() 
{
	if( tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1 )
	{
		die("tcsetattr");
	}
}

//Enables Raw Mode
void enableRawMode() 
{
	if( tcgetattr(STDIN_FILENO, &E.orig_termios) == -1 )
	{
		die("tcsetattr");
	}
	atexit(disableRawMode);

	struct termios raw = E.orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_lflag &= ~(OPOST);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	if( tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1 )
	{
		die("tcsetattr");
	}
}

//function to read the character entered
int editorReadKey()
{
	int nread;
	char c;
	while((nread = read(STDIN_FILENO, &c, 1)) != 1 )
	{
		if( nread == -1 and errno != EAGAIN )
		{
			die("read");
		}
	}
	//if we read a escape character, it is a special key, so we read what special key it is by reading the next 2 characters and appropriately resolve it.
	if( c == '\x1b' )
	{
		char seq[3];
		if( read( STDIN_FILENO, &seq[0], 1) != 1 )
		{
			return '\x1b';
		}
		if( read( STDIN_FILENO, &seq[1], 1) != 1 )
		{
			return '\x1b';
		}

		if( seq[0] == '[' )
		{
			if( seq[1] >= '0' and seq[1] <= '9' )
			{
				if( read( STDIN_FILENO, &seq[2], 1) != 1 )
				{
					return '\x1b';
				}
				if( seq[2] == '~' )
				{
					switch( seq[1] )
					{
						case '3': return DEL_KEY;
					}
				}
			}
			else
			{
				switch( seq[1] )
				{
					//these 4 keys suggest that the keys entered are arrow keys
					case 'A' : return ARROW_UP;
					case 'B' : return ARROW_DOWN;
					case 'C' : return ARROW_RIGHT;
					case 'D' : return ARROW_LEFT;
				}
			}
		}
		return '\x1b';
	}
	return c;
}

//function to get the current cursor position
int getCursorPosition( int *rows , int *cols ) 
{
	char buf[32];
	unsigned int i = 0;

	if( write(STDOUT_FILENO, "\x1b[6n", 4) != 4) 
	{
		return -1;
	}

	while( i < sizeof(buf) -1 )
	{
		if( read(STDIN_FILENO, &buf[i], 1) != 1)
		{
			break;
		}
		if( buf[i] == 'R' )
		{
			break;
		}
		i++;
	}

	buf[i] = '\0';

	if( buf[0] != '\x1b' or buf[1] != '[' )
	{
		return -1;
	}
	if( sscanf(&buf[2], "%d;%d", rows, cols) != 2 )
	{
		return -1;
	}
	printf("\r\n&buf[1]: '%s' \r\n", &buf[1]);

	return -1;
}

//this function fetches the window sizes
int getWindowSize( int* rows, int* cols )
{
	struct winsize ws;


	//position the cursor to the bottom right
	if( ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 or ws.ws_col == 0 )
	{
		if( write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12 )
		{
			return -1;
		}
		//the cursor position is the size of the screen
		return getCursorPosition(rows, cols);
	}
	else 
	{
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return 0;
	}
}

//buffer that contains the entire output to be displayed
struct abuf
{
	char* b;
	int len;
};

#define ABUF_INIT {NULL, 0}


//append s to the existing buffer
void abAppend( struct abuf* ab, const char* s, int len)
{
	char* n = (char*) realloc(ab->b, ab->len+len);

	if( n == NULL )
	{
		return;
	}
	memcpy(&n[ab->len], s, len);
	ab->b = n;
	ab->len += len;
}

//free buffer
void abFree(struct abuf* ab)
{
	free(ab->b);
}

//populate the buffer with the content
void editorDrawRows( struct abuf* ab )
{

	int size = 0;
	vector<string> content = getContent(E.screenrows, E.screencols);

	for( int i = 0 ; i < E.screenrows ; i++ )
	{
		//if we complete printing all rows then insert tildes for remaining screen
		if( i < content.size() )
		{
			abAppend(ab, content[i].c_str(), content[i].size());
		}
		/*
		if( i == E.screenrows/2 )
		{
			char text[80];
			int textlen = snprintf(text, sizeof(text), "this is a test message");

			if( textlen > E.screencols)
			{
				textlen = E.screencols;
			}
			int padding = (E.screencols - textlen)/2;
			while( padding-- )
			{
				abAppend(ab, " ",1);
			}
			abAppend(ab, text, textlen);
		}
		*/
		abAppend(ab, "\x1b[K", 3);
		if( i < E.screenrows -1 )
		{
			abAppend(ab, "\r\n", 2);
		}
	}
}

//refresh the screen
void editorRefreshScreen()
{
	//for each refresh, create a new buffer
	struct abuf ab = ABUF_INIT;

	//hide the cursor while writing
	//abAppend(&ab, "\x1b[?25l", 6);
	//position the cursor to the start of the screen
	abAppend(&ab, "\x1b[H", 3);

	//draw the rows and reposition the cursor to the start
	editorDrawRows(&ab);

	//position the cursor to the cursor positions
	char buf[32];
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy+1, E.cx+1);
	abAppend(&ab, buf, strlen(buf));

	//show the  cursor after writing
	//abAppend(&ab, "\x1b[?25h", 6);


	if( E.mode == NAVIGATION )
	{	
		abAppend(&ab, "\x1b[?25l", 6);
	}
	else
	{
		abAppend(&ab, "\x1b[?25h", 6);
	}

	//write the entire buffer with one single write
	write(STDOUT_FILENO, ab.b, ab.len);
	//free the buffer after writing
	abFree(&ab);
}

//function to control cursor movement
void editorMoveCursor( int key )
{
	switch(key)
	{
		case ARROW_LEFT:
			if( E.cx != 0 )
			{
				unfocus(E.cx, E.cy);
				getLeftPos(&E.cx, &E.cy);
				focus(E.cx, E.cy);
			}
			break;
		case ARROW_RIGHT:
			if( E.cx != E.screencols-1 )
			{
				unfocus(E.cx, E.cy);
				getRightPos(&E.cx, &E.cy);
				focus(E.cx, E.cy);
			}
			break;
		case ARROW_UP:
			if( E.cy != 0 )
			{
				unfocus(E.cx, E.cy);
				getUpPos(&E.cx, &E.cy);
				focus(E.cx, E.cy);
			}
			break;
		case ARROW_DOWN:
			if( E.cy != E.screenrows - 1 )
			{
				unfocus(E.cx, E.cy);
				getDownPos(&E.cx, &E.cy);
				focus(E.cx, E.cy);
			}
			break;
	}
}

//function to say what to do with the character entered
void editorProcessKeypress()
{
	int c = editorReadKey();

	switch(c)
	{
		//if entered enter key save the value and go to navigation mode
		case '\n':
		case '\r':
			E.mode = NAVIGATION;
			exitEditorMode(&E.cx, &E.cy);
			break;
		//if entered q then exit the program
		case'q':
			//clear the screen the reposition the cursor
			write(STDOUT_FILENO, "\x1b[2J", 4);
			write(STDOUT_FILENO, "\x1b[H", 3);
			printf("\033[?47l");
			printf("\033[u");
			printf("\033[?25h");
			exit(0);
			break;
		case 'i':
			if( enterEditorMode(&E.cx, &E.cy) )
			{
				E.mode = EDIT;
			}
			break;
		case '\033':
			E.mode = NAVIGATION;
			exitEditorMode(&E.cx, &E.cy);
			break;	
		//handle arrow keys press
		case ARROW_UP:
		case ARROW_DOWN:
		case ARROW_LEFT:
		case ARROW_RIGHT:
			if( E.mode == NAVIGATION )
			{
				editorMoveCursor(c);
			}
			break;
		//handle delete key
		case DEL_KEY:
			break;
		//handle backspace key
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


//initialize the editor
void initEditor()
{
	if( getWindowSize( &E.screenrows, &E.screencols ) == -1 )
	{
		die("getWIndowSize");
	}
	getContent( E.screenrows, E.screencols );
	getStartPos(&E.cx, &E.cy);
	focus(E.cx, E.cy);
	E.mode = NAVIGATION;
	cout << E.cx << " " << E.cy << endl;
}

int main() 
{
	printf("\033[s");
	printf("\033[?47h");
	initialize();
	enableRawMode();
	initEditor();

	while(true)
	{
		editorRefreshScreen();
		editorProcessKeypress();
	}
	return 0;
}
