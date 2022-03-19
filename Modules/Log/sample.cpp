#include <fstream>
#include <ctime>
#include <iostream>
#include <vector>
#include "log.h"

using namespace std;
int main()
{
    entry("hello","student","logout");
    vector<log> logs= get_logs();
    for(int i=0;i<logs.size();i++)
        cout<<logs[i].user<<endl;
    
}
