#include<iostream>
#include"helper.h"
using namespace std;

int main()
{
	while(true)
	{
		cout << "Enter 0 to exit" << endl;
		cout << "Enter 1 to add an Admin" << endl;
		cout << "Enter 2 to add a Student" << endl;
		cout << "Enter 3 to add a Instructor" << endl;
		cout << "Enter 4 to add an HOD " << endl;

		int choice;
		cin >> choice;
		
		if( choice == 0 )
		{
			break;
		}
		else if(choice == 1 )
		{
			cout << "Enter the username of the Admin" << endl;
			string username;
			cin >> username;
			cout << "Admin user name is " << username << endl;
			if( !checkIfUserExists(username) )
			{
				createUser(username);
			}
			addUserGroup( username, "admins" );
		}
		else if(choice == 2 )
		{
			cout << "Enter the username of the Student" << endl;
			string username;
			cin >> username;
			cout << "Student user name is " << username << endl;
			createStudent( username );
		}
		else if(choice == 3 )
		{
			cout << "Enter the username of the Instructor" << endl;
			string username;
			cin >> username;
			cout << "Instructor user name is " << username << endl;
			createInstructor(username);
		}
		else if(choice == 4 )
		{
			cout << "Enter the username of the HOD" << endl;
			string username;
			cin >> username;
			cout << "HOD user name is " << username << endl;
			if( !checkIfUserExists(username) )
			{
				createUser(username);
			}
			addUserGroup( username, "hods" );
		}
	}

	cout << "poorna " << checkIfUserExists("poorna") << endl;
	cout << "user1 " << checkIfUserExists("user1") << endl;
	return 0;
}
