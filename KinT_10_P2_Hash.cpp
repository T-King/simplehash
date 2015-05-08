//**************************************************
//Troy King (TroyKing@my.unt.edu)
//CSCE2110.001 Computer Foundations II
//Instructor: Dr. Patrick Burke
//Program 2: Set Implementation
//Due: February 17, 2015 @ 10:00 a.m.
//
//This program will take integer values from the user and
//store them into a hash table. WARNINGs will be displayed
//for bad input.
//**************************************************

#include <iostream>
#include <string>
#include <stdlib.h>	//for atoi
#include <vector>	//for holding bins
#include <list>		//acting as bins

using namespace std;

typedef list<int> BIN;		//I referenced Mark Short's example "STL_Bucket.cpp"
BIN::iterator 		itI; 	//inside
vector<BIN>::iterator 	itO; 	//outside

int com_enter	(string&, int);
int hashKey	(int);
void hashAdd	(vector<BIN>&, int, int);
void hashDel	(vector<BIN>&, int, int);
void hashSearch	(vector<BIN>&, int, int);
void hashShow	(vector<BIN>&);

int main()
{
	string com = "test";	//command the user wants to use
	int num;		//number the user wants to input
	int key;		//hash key

	vector<BIN> hash(7);	//creating a vector of 7 bins (using linked lists)

	for(;;)
	{
			num = com_enter(com, num);
			key = hashKey(num);

			if((com == "add") && (num != -1))
				hashAdd(hash, num, key);
                	else if((com == "delete") && (num != -1))
				hashDel(hash, num, key);
                	else if((com == "search") && (num != -1))
				hashSearch(hash, num, key);
                	else if(com == "show")
				hashShow(hash);
               	 	else if(com == "quit")
				return 0;
			else
				cout << "WARNING: invalid command" << endl;
	}
}

int com_enter(string& com, int num)
{
	string input;
	string temp;

	com.clear();		//clears com because of append method
	num = -1;		//resets num in case of no input

	cout << ">set ";
	getline(cin, input);	//did not need char[] for some reason

	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] == ' ')
		{
			com.append(input.substr(0, i));
			temp.append(input.substr(i + 1, input.length() - 1));
			num = atoi(temp.c_str());
			break;
		}
		else if(i == input.length() - 1)
		{
			com = input;
			return -1;
		}
	}

	if(num < 0)	//did not need limits because atoi reduces
			//strings to value of 0
	{
		cout << "WARNING: needs positive integer" << endl;
		return -1;
	}
	return num;
}

int hashKey(int num)
{
	return (num * num)%7;
}

void hashAdd(vector<BIN>& hash, int num, int key)
{
	itO = hash.begin();	//sets iterator to the first bin of the table
	advance(itO, key);	//advances iterator so for-loop only needs to check
			  	//through the bin, where it will add a number, for duplicate
	for(itI = itO->begin(); itI != itO->end(); ++itI)
	{
		if(*itI == num)
		{
			cout << "WARNING: duplicate number: " << num << endl;
			return;
		}
	}
	itO->push_back(num);
}

void hashDel(vector<BIN>& hash, int num, int key)
{
	itO = hash.begin();
	advance(itO, key);

	for(itI = itO->begin(); itI != itO->end(); ++itI)
	{
		if(*itI == num)
		{
			itO->erase(itI);
			return;
		}
	}
	cout << "WARNING: target value not found: " << num << endl;
}

void hashSearch(vector<BIN>& hash, int num, int key)
{
	itO = hash.begin();
	advance(itO, key);

	for(itI = itO->begin(); itI != itO->end(); ++itI)
	{
		if(*itI == num)
		{
			cout << "true" << endl;
			return;
		}
	}
	cout << "false" << endl;
}

void hashShow(vector<BIN>& hash)
{
	for(itO = hash.begin(); itO != hash.end(); ++itO)
	{
		cout << "(";
		for(itI = itO->begin(); itI != itO->end(); ++itI)
		{
			if(itI == --(itO->end())) cout << *itI;
			else if((itO->begin()) == (itO->end())) cout << *itI;
			else cout << *itI << ", ";
		}
		if(itO == --(hash.end())) cout << ")" << endl;
		else cout << ")-";
	}
}
