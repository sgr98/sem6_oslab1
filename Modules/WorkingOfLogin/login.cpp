#include<iostream>
#include<vector>
#include<string.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
using namespace std;

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
				cout << groups[i] << endl;
				/*
				for( int j = 0 ; j < words.size() ; j++ )
				{
					cout << words[j] << " ";
				}
				cout << endl;
				*/
				vector<string> listOfUsers;

				char s[words[words.size()-1].size()];
				strcpy(s, words[words.size()-1].c_str() );
				token = strtok(s, ",");
				while( token != NULL )
				{
					listOfUsers.push_back(token);
					token = strtok(NULL, ":");
				}
				for( int j = 0 ; j < listOfUsers.size() ; j++ )
				{
					cout << listOfUsers[j] << " ";
					if( listOfUsers[j] == username )
					{
						result.push_back(groups[i]);
					}
				}
				cout << endl;
			}
		}

	}
	return result;
}

int main()
{
	char command[] = "./admin";
	char* args[] = {command,NULL};

	int gid = getgid();
	int egid = getegid();
	cout << "gid = " << gid << endl;
	cout << "egid = " << egid << endl;

	//int r = execvp(args[0], args);
	//cout << "return value = " << r << endl;

	string username = "student1";
	vector<string> groups = getGroupsBelonging(username);
	cout << "user name = " << username << endl;
	cout << "given user belongs to the following groups" << endl;
	for( int i = 0 ; i < groups.size() ; i++ )
	{
		cout << groups[i] << " ";
	}
	cout << endl;
	return 0;
}
