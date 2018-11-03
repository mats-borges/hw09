// Matts Borges
// ITP 165 Fall 2018
// hw 09
// mdborges@gmail.com

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

struct Person
{
	string name;
	string* likes; // array of names of Persons of the opposite sex
	string spouse; // =="" if none
	bool female = true; // true===female, false===male

	//getter functions
	string getName()
	{return name;}
	string getLikes()
	{return* likes;}
	string getSpouse()
	{return spouse;}
	bool getFemale()
	{return female;}

};

		const string menNames[10] = { "a", "b", "c", "d", "e", "f", "g" ,"h" ,"i", "j" };
		const string womenNames[10] = { "1", "2", "3", "4", "5", "6","7", "8", "9", "0" };
		const string allNames[20] = { "a", "b", "c", "d", "e", "f", "g" ,"h" ,"i", "j", "1", "2", "3", "4", "5", "6","7", "8", "9", "10" };

//prototypes
void Sublist(const string bigList[], const int bigNum, string smallList[], const int smallNum);
void pick(string men[], string women[], Person which[], int N);
void displayStrings(string *s, int size);
void display(Person town[], int size);
void displayp(Person *p, int size);


int main()
{
	srand(time(NULL));
	//variables
	int userNum;
	int rNum = rand()%10;
	string smallist[3];
	int smalnum = 3;

	//propmt
	cout << "Enter number of couples: ";
	cin >> userNum;
	

	Sublist(menNames, userNum, smallist, smalnum);//vtc
	//displayStrings(smallist, smalnum);//variables to change

	//keep open
	int x;
	cin >> x;



    return 0;

}

void Sublist(const string bigList[], const int bigNum, string smallList[], const int smallNum)
{
	int* arrpoint = NULL;
	
	// MEN big
	arrpoint = new int[bigNum];
	for (int i = 0; i < bigNum; i++)
	{
		arrpoint[i] = rand() % bigNum;
		cout << bigList[arrpoint[i]];
	}
	cout << endl;


	//MEN small
	for (int j = 0; j < smallNum; j++)
	{
		smallList[j] = bigList[arrpoint[rand()%bigNum]];
		cout << smallList[j];
	}
	cout << endl;



	delete[] arrpoint;
	arrpoint = NULL;
}

void pick(string men[], string women[], Person which[], int N)
{

}

void displayStrings(string *s, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << s[i];
	}
}

void display(Person town[], int size)
{

}

void displayp(Person *p, int size)
{
	string gender;
	if (p->female)
	{
		gender = "female";
	}
	else
	{
		gender = "male";
	}

	//cout display
	cout  << " is a " << gender << " who likes: " << ". Spouse: " << p->spouse;

	
}