#include<vector>
#include<iostream>
using namespace std;

void createUser( string username );
void removeUser( string username );
bool checkIfUserExists( string username );
void createGroup( string groupName );
void addUserGroup( string username, string groupname );
void removeUserGroup( string username, string groupname );
void createDirectory( string dirname );
void createFile( string filename );
void createInstructor( string username );
void createStudent( string username );
void createHod( string username );
void removeHod(string username);
void removeInstructor( string username );
void removeStudent( string username );
vector<string> getUserList();
vector<string> getGroupsBelonging( string username );
