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
	{
		return name;
	}
	string getLikes()
	{
		return*likes;
	}
	string getSpouse()
	{
		return spouse;
	}
	bool getFemale()
	{
		return female;
	}

};

const int numOfMenOrWomen = 10;
const string menNames[10] = { "aiden", "blake", "caden", "duncan", "ethan", "fabio", "gerry" ,"hunkithan" ,"ian", "jack" };
const string womenNames[10] = { "ally", "barbara", "cammy", "dana", "elsa", "fabia", "gabriella", "hermione", "isabelle", "jen" };

//prototypes
void Sublist(const string bigList[], const int bigNum, string smallList[], const int smallNum);
void pick(string men[], string women[], Person which[], int N);
void displayStrings(string *s, int size);
void display(Person town[], int size);
void displayp(Person *p, int size);


int main()
{
	srand(time(0));
	//variables
	int userNum;
	int rNum = rand() % 10;

	//propmt
	cout << "Enter number of couples: ";
	cin >> userNum;

	string *menInTown; // declare a pointer of type string for the men names in town
	menInTown = new string[userNum]; // dynamically allocate memory using keyword new

	string *womenInTown; // declare a pointer of type string for the women names in town
	womenInTown = new string[userNum]; // dynamically allocate memory using keyword new

	Person *peopleInTown; // declare a pointer of type Person for the total people in town
	peopleInTown = new Person[userNum * 2]; // dynamically allocate memory using keyword new of size 2 * userNum


	Sublist(menNames, numOfMenOrWomen, menInTown, userNum);
	Sublist(womenNames, numOfMenOrWomen, womenInTown, userNum);

	cout << "Men in Town: ";
	displayStrings(menInTown, userNum);
	cout << endl;

	cout << "Women in Town: ";
	displayStrings(womenInTown, userNum);
	cout << endl;

	pick(menInTown, womenInTown, peopleInTown, userNum);

	display(peopleInTown, userNum * 2);

	//displayStrings(smallist, smalnum);//variables to change

	//keep open
	int x;
	cin >> x;


	return 0;

}

void Sublist(const string bigList[], const int bigNum, string smallList[], const int smallNum)
{

	// small
	for (int i = 0; i < smallNum; i++)
	{
		string temp = bigList[rand() % bigNum];

		for (int j = 0; j < smallNum; j++) { // search through smallList for duplicate entry
			if (temp == smallList[j]) { // if one exists,
				temp = bigList[rand() % bigNum]; // then create a new random temp,
				j = -1; // and reset the loop
			}
		}
		smallList[i] = temp;
		//cout << smallList[i] << " ";
	}
	//cout << endl;

}

void pick(string men[], string women[], Person which[], int N)
{
	for (int i = 0; i < N; i++) {
		which[i].name = men[i];
		which[i].female = false;
		which[i].spouse = "";
		which[i].likes = new string[3];
		
		Sublist(women, N, which[i].likes, 3);
	}
	cout << endl;
	for (int i = 0; i < N; i++) {
		which[N + i].name = women[i];
		which[N + i].female = true;
		which[N + i].spouse = "";
		which[N + i].likes = new string[3];

		Sublist(men, N, which[N + i].likes, 3);
	}
}

void displayStrings(string *s, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << s[i];
		if (i < size - 2) cout << ", ";
		else if (i == size - 2) cout << ", and ";
	}
}

void display(Person town[], int size)
{
	for (int i = 0; i < size; i++) {
		Person *p = new Person;
		p = &(town[i]);
		displayp(p, 3);
		cout << endl;
	}
}

void displayp(Person *p, int size)
{
	string gender;
	string spouse;

	if (p->female)
	{
		gender = "female";
	}
	else
	{
		gender = "male";
	}
	if (p->spouse == "") spouse = "Nobody";
	else spouse = p->spouse;

	//cout display
	cout << p->name << " is a " << gender << " who likes ";
	displayStrings(p->likes, size);

	cout << ". Spouse: " << spouse;


}