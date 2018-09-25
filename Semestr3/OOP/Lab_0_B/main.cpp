#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<map>

using namespace std;

int main(int argc, char** argv){
	
	if (argc != 3) {
		cout << "Error input!";
		return -1;
	}

	ifstream infile (argv[1]);
	ofstream outfile (argv[2]);
	if (!infile) 
	{
	cout << "Not open input\n\n"; 
	return -1;
	}
	if (!outfile) 
	{
	cout << "Not open output\n\n"; 
	return -1;
	}

	int MaxWords = 0;
	string str;
	map <string,int> MapTable;
	map <int,vector<string>> MapTable2;
	getline(infile, str);

	char * str2 = new char [str.length()+1];
	strcpy( str2, str.c_str() );

	char * pch = strtok (str2," ,.-");
 
    while (pch != NULL)
    {	
    	MapTable[pch]++;
        //outfile << MapTable[pch]  << "\n";
        pch = strtok (NULL, " ,.-");
        MaxWords++;
    }

    for (auto it = MapTable.begin(); it != MapTable.end(); it++)
	{
		MapTable2[it->second].push_back(it->first);
	}

	for (auto it = MapTable2.rbegin(); it != MapTable2.rend(); it++)
	{
		vector<string> &Vect = it->second;
		for (auto jt = Vect.begin(); jt != Vect.end(); ++jt)
		{
			outfile << *jt <<";"<< it->first<< ";" << it->first*100.0/MaxWords <<"%" << endl;
		}
	}

    //outfile << MaxWords;

	infile.close();
	outfile.close();
}