#include<iostream>
#include<unistd.h>
using namespace std;

int main()
{
	int gid = getgid();
	int egid = getegid();
	cout << "You logged in as admin" << endl;
	cout << "gid = " << gid << endl;
	cout << "egid = " << egid << endl;
}
