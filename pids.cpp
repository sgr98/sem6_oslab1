#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;



int remove_pid(string name, int pid){
	int suc = 0;
	string line;
	string deleteline = name + " " + to_string(pid); 
	ifstream fin;
	fin.open("pids_file.txt");
	ofstream temp;
	temp.open("temp.txt");



	while (getline(fin,line))
	{
		if (line != deleteline)
		{
		temp << line << endl;
		}
		else if(line == deleteline){
			suc = 1;
		}
	}

	temp.close();
	fin.close();
	remove("pids_file.txt");
	rename("temp.txt","pids_file.txt");

	return suc;

}

string fetch_pid(string name){
	int f_pid;
	fstream myfile;
	myfile.open("pids_file.txt", ios::in);
	if(myfile.is_open()){
		string line;
		while(getline(myfile, line)){
			char s1[line.size()+1];
			strcpy(s1, line.c_str());
			char* token = strtok(s1, " ");
			vector<string> tokens;
			while (token != NULL)
			{

				tokens.push_back(token);
				token = strtok(NULL, " ");
			}
			if(tokens[0] == name){
				return tokens[1];
			}
		}
	}
	
	return "-1";
}

void write_pid(string name, int pid){
	fstream myfile;
	myfile.open("pids_file.txt", ios::app);
	if(myfile.is_open()){
		string line;
		// while(getline(myfile, line)){
		// 	//
		// }
		string str = name + " " + to_string(pid) + "\n";
		myfile << str;
	}
	myfile.close();
}


int main(){

	write_pid("Nitesh", 9);
	write_pid("Vignesh", 8);
	write_pid("ney", 11);
	write_pid("leo", 10);
	write_pid("ron", 7);
	cout<<fetch_pid("leo")<<endl;
	cout<<remove_pid("Nitesh", 14)<<endl;
	

	return 0;
}
