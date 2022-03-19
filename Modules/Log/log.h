#include <fstream>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class log
{
    public:
    string date;
    string time;
    string user;
    string type;
    string action;
    log(string date,string time,string user,string type,string action);
};
vector<log> get_logs();
bool entry(string username,string type,string action);
bool clearlog();
