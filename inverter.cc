/*
Assignment 0
'Inverted Index' of words of multiple text file
Stephen Lendl

Takes in a single argument: a file that contains a list of filenames

inputs.txt
-----
foo1.txt
foo2.txt

Test if all the file names are valid to be indexed [is_open()]

Filter and index all the valid words within files
RULES:
1. "The" and "the" are separate words, and "The" comes first.
2. Words are anything that is made up of only alpha characters, and not numbers, spaces, etc.  "Th3e" is two words, "Th" and "e".

Store this result in a file and then print all the lines of the file in this format.
In particular, the output should have one space between the colon and the first document number, one space between each subsequent document number, and no spaces at the end of any line.
a: 0 1
also: 1
boring: 1
cool: 0
is: 0 1
test: 0 1
this: 0 1
*/

#include<iostream>
#include<map>
#include<string.h>
#include<sstream>
#include<fstream>
#include<cstdio>
#include <string>
using namespace std;

int main(int argc, char** argv) {
	char filenames[20][20];
	int i = 0;
	int max = 0;
	char t;
	int needHelp = 0;
	int opener = -1;
	string line;
	stringstream key, value, add;
	map <string, string> invertedIndex;
	std::pair<std::map<string,string>::iterator,bool> check;
	ifstream input;

	input.open(argv[1], ios::in);
	if(input.is_open()) {
		while(!input.eof()) {
			getline(input, line);
			//cout << line << endl;
			strcpy(filenames[i], line.c_str());
			//cout << filenames[i] << "|" << endl;
			i++;
		}
		max = i;
		i = 0;
		input.close();
	}

	for(int fn = 0; fn < max; fn++) {
		ifstream tfile;
		tfile.open(filenames[fn], ios::in);
		if(tfile.is_open()) {
			opener++;
			
			while(!tfile.eof()) {
				while(tfile.get(t)) {
					if(isalpha(t)) {
						key << t;
					}
					else {
						break;
					}
				}
				value << " " << opener;
				//cout << value.str() << endl;
				check = invertedIndex.insert(pair<string,string>(key.str(), value.str()));
				if(check.second == false) {
					string test1 = check.first->second;
					//cout <<"test1:"<< test1 << endl;
					string test2 = value.str();
					//cout <<"test2:" << test2 << endl;
					if(test1[test1.length()-1] != test2[1]) {
						//cout <<  test1[test1.length()-1] <<"and "<< test2[1] << endl;
						add << check.first->second << value.str();
						check.first->second = add.str();
						add.str("");
					}
				}
				value.str("");
				key.str("");
			}
		}
		else {
			//cout << "idk about this";
			needHelp++;
			if(needHelp == max){
				//cout<<needHelp;
				return 0;
			}
		}
	}
	if(invertedIndex.begin()->first == "") {
		invertedIndex.erase(invertedIndex.begin());
	}
	map<string, string>::iterator it;
	for(it = invertedIndex.begin(); it != invertedIndex.end(); it++){
	     cout << it->first << ":" << it->second << "\n";
	}
	return 0;
}