#include <string>
#include <vector>
using namespace std;
class InstructorStudent
{
public:
    string name;
    InstructorStudent(string name);
    vector<string>fetch();
    bool addStudent(string stu);
    bool modifyStudent(string before,string after);
    bool removeStudent(string stu);
    bool deleteFile(const char *filename);
    bool deleteFile();
};
