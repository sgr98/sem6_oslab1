#include "instructorStudent.h"
#include <fstream>
#include <iostream>
using namespace std;
InstructorStudent::InstructorStudent(string name)//inputs instructor name
{
    this->name=name;
}

vector<string> InstructorStudent::fetch()
{
    vector<string>students;
    ifstream personal_filein(name+".txt");
    string line="";
    while ( getline ( personal_filein , line) )
    {
        students.push_back(line);
    }
    personal_filein.close();
    return students;
    }


bool InstructorStudent::addStudent(string stu)
    {
        ofstream out(name+".txt", std::ios_base::app);
        out<<stu<<endl;
        out.close();
        return true;
    }

bool InstructorStudent::modifyStudent(string before,string after)
    {
        if(removeStudent(before))
        {
            addStudent(after);
        }
        return false;
    }
bool InstructorStudent::removeStudent(string stu)
    {
        int i;
        vector<string>students=fetch();
        for(i=0;i<students.size();i++)
        {
            if(stu==students[i])
                break;
        }
        if(i<students.size())
        {
            students.erase(students.begin()+i);
            ofstream out(name+".txt");
            out<<"";
            for(i=0;i<students.size();i++)
                addStudent(students[i]);
            return true;
        }
        return false;
    }
bool InstructorStudent::deleteFile(const char *filename)
    {
        if( remove( filename ) != 0 )
        perror( "Error deleting file" );
        else
        cout<< "File successfully deleted" <<endl;
        return true;
    }
bool InstructorStudent::deleteFile()
    {
        string s=name+".txt";
        const char* file = s.c_str();
        deleteFile(file);
    }