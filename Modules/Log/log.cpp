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
    log(string date,string time,string user,string type,string action)
    {
        this->date=date;
        this->time=time;
        this->user=user;
        this->type=type;
        this->action=action;
    }
};

vector<log> get_logs()
{
    ifstream personal_filein("logfile.txt");
    vector<log> logs;
    string line="";
    string date,time,user,type,action;
    while ( getline ( personal_filein , line,' ' ) )
    {
        date=line;
        getline ( personal_filein , line,' ' );
        date+=line;
        getline ( personal_filein , line,' ' );
        date+=line;
        getline ( personal_filein , line,' ' );
        time=line;
        getline ( personal_filein , line,' ' );
        date+=line;
        getline ( personal_filein , line,' ' );
        user=line;
        getline ( personal_filein , line,' ' );
        type=line;
        getline ( personal_filein , line,'\n' );
        action=line;
        logs.push_back(log(date,time,user,type,action));
    }
    personal_filein.close();
    return logs;
}

bool entry(string username,string type,string action)//log format: date, time, username,action
{//action can be login or logout
    ofstream f;
    f.open("logfile.txt", std::ios_base::app);
    time_t now = time(0);
    char* dt = ctime(&now);
    //example
    //Sat Jan  8 20:07:41 2011
    string date=dt;
    f<<date.substr(0,date.size()-1)<<' '<<username<<' '<<type<<' '<<action<<endl;
    f.close();
    return true;
}

bool clearlog()
{
    if( remove( "logfile.txt" ) != 0 )
    perror( "Error deleting file" );
  else
    cout<< "File successfully deleted" <<endl;

    return true;
}
