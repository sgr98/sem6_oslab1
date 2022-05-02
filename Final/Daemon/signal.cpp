#include<iostream>
#include<signal.h>
using namespace std;

int main()
{
	int i;
	cin >> i;
	kill(i, SIGINT);
}
