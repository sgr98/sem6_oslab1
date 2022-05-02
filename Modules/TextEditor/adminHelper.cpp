#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<vector>
#include<string.h>
#include "adminHelper.h"
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

void createUser( string username )
{	
	string temp = "sudo useradd -m " + username;
	const char* command = temp.c_str();
	system(command);
	
	cout << "Enter the Password" << endl;
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
	createUser(username);
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
	createUser(username);
	addUserGroup( username, "students" );

	createFile("Students/" + username + ".txt");
	setPermissions("setfacl -m g::--- Students/" + username + ".txt");
	setPermissions("setfacl -m u::rwx Students/" + username + ".txt");
	setPermissions("setfacl -m o::--- Students/" + username + ".txt");
	setPermissions("sudo chown " + username + ": Students/" + username + ".txt");
}

void createHod( string username )
{
	createUser(username);
	addUserGroup( username, "hods" );
}

void removeStudent( string username )
{
	vector<string> groups = getGroupsBelonging(username);
	bool b = false;
	for( int i = 0 ; i < groups.size() ; i++ )
	{
		if( groups[i] == "students" )
		{
			b = true;
			break;
		}
	}
	if( b == false )
	{
		cout << username << " is not a Student" << endl;
	}
	else
	{
		removeUser( username );
		setPermissions("sudo rm Students/" + username + ".txt");
	}
}

void removeInstructor( string username )
{
	vector<string> groups = getGroupsBelonging(username);
	bool b = false;
	for( int i = 0 ; i < groups.size() ; i++ )
	{
		if( groups[i] == "Faculty" )
		{
			b = true;
			break;
		}
	}
	if( b == false )
	{
		cout << username << " is not an Instructor" << endl;
	}
	else
	{
		removeUser( username );
		setPermissions("sudo rm -r Instructors/" + username + "/");
	}
}

void removeHod( string username )
{
	vector<string> groups = getGroupsBelonging(username);
	bool b = false;
	for( int i = 0 ; i < groups.size() ; i++ )
	{
		if( groups[i] == "hods" )
		{
			b = true;
			break;
		}
	}
	if( b == false )
	{
		cout << username << " is not a Hod" << endl;
	}
	else
	{
		removeUser( username );
	}
}
