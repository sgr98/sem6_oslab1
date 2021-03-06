#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<vector>
#include<string.h>
#include"helper.h"
#include<sys/stat.h>
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

void createUser( string username )
{	
	string temp = "sudo useradd " + username;
	const char* command = temp.c_str();
	system(command);
	
	temp = "sudo passwd " + username;
	const char* command2 = temp.c_str();
	system(command2);
}

void removeUser( string username )
{
	string temp = "sudo userdel " + username;
	const char* command = temp.c_str();
	system(command);
}

bool checkIfUserExists( string username )
{
	vector<string> userList = getUserList();
	for( int i = 0 ; i < userList.size() ; i++ )
	{
		if( userList[i] == username )
		{
			return true;
		}
	}
	return false;
}

void createGroup( string groupName )
{
	string temp = "sudo groupadd -f " + groupName;
	const char* command = temp.c_str();
	system(command);
}

void addUserGroup( string user, string group )
{
	string command = "sudo usermod -a -G " + group + " " + user;
	system(command.c_str());
}

void removeUserGroup( string user, string group )
{
	string command = "sudo gpasswd -d " + user + " " + group;
	system(command.c_str());
}

void createDirectory( string dirname )
{
	const char* path = dirname.c_str();
	if( mkdir(path, S_IRWXU) == -1 )
	{
		cerr << "Error: " << strerror(errno) << endl;
		return;
	}
}

void createFile( string filename )
{
	const char* path = filename.c_str();
	FILE *fp;
	fp = fopen(path, "w");
	if( fp == NULL )
	{
		cout << "fp is null" << endl;
	}
}

void setPermissions( string permission )
{
	system(permission.c_str());
}

void createInstructor( string username)
{
	if( !checkIfUserExists(username) )
	{
		createUser(username);
	}

	addUserGroup( username, "Faculty" );
	createDirectory("Instructors/" + username);
	setPermissions("setfacl -m g:studentsexecute:rwx Instructors/" + username);
	
	createFile("Instructors/" + username + "/hist0.txt");
	setPermissions("setfacl -m g:studentsexecute:r-- Instructors/" + username + "/hist0.txt");
	setPermissions("setfacl -m g::--- Instructors/" + username + "/hist0.txt");
	setPermissions("setfacl -m u::rwx Instructors/" + username + "/hist0.txt");
	setPermissions("setfacl -m o::--- Instructors/" + username + "/hist0.txt");
	setPermissions("sudo chown " + username + ": Instructors/" + username + "/hist0.txt");

	createFile("Instructors/" + username + "/hist1.txt");
	setPermissions("setfacl -m g:studentsexecute:r-- Instructors/" + username + "/hist1.txt");
	setPermissions("setfacl -m g::--- Instructors/" + username + "/hist1.txt");
	setPermissions("setfacl -m u::rwx Instructors/" + username + "/hist1.txt");
	setPermissions("setfacl -m o::--- Instructors/" + username + "/hist1.txt");
	setPermissions("sudo chown " + username + ": Instructors/" + username + "/hist1.txt");

	createFile("Instructors/" + username + "/hist2.txt");
	setPermissions("setfacl -m g:studentsexecute:r-- Instructors/" + username + "/hist2.txt");
	setPermissions("setfacl -m g::--- Instructors/" + username + "/hist2.txt");
	setPermissions("setfacl -m u::rwx Instructors/" + username + "/hist2.txt");
	setPermissions("setfacl -m o::--- Instructors/" + username + "/hist2.txt");
	setPermissions("sudo chown " + username + ": Instructors/" + username + "/hist2.txt");
	

	setPermissions("sudo chown " + username + ": Instructors/" + username);
}

void createStudent( string  username )
{
	if( !checkIfUserExists(username) )
	{
		createUser(username);
	}
	addUserGroup( username, "students" );

	createFile("Students/" + username + ".txt");
	setPermissions("setfacl -m g::--- Students/" + username + ".txt");
	setPermissions("setfacl -m u::rwx Students/" + username + ".txt");
	setPermissions("setfacl -m o::--- Students/" + username + ".txt");
	setPermissions("sudo chown " + username + ": Students/" + username + ".txt");
}
