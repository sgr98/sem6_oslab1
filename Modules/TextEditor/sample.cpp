#include<iostream>
#include <chrono>
#include <thread>
#include<unistd.h>
using namespace std;
int main()
{
	this_thread::sleep_for(chrono::milliseconds(4000)); // sleep for 3 second

	system("ls");
	string s = "export PS1=\"\\u>\"";
	cout << s << endl;
	system(s.c_str());
	exit(0);
}
