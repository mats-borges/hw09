// Matts Borges
// ITP 165 Fall 2018
// hw 09
// mdborges@gmail.com

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <sstream>

using namespace std;

struct Person
{
	string name;
	string* likes; // array of names of Persons of the opposite sex
	int numLikes;
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
void displayStrings(string *s, int size, string sp);
void display(Person town[], int size);
string toUpperCase(string s);
string toLowerCase(string s);
string capitalize(string s);
void displayp(Person *p);
bool marry(Person*, Person*);
void divorce(Person* p, Person town[], int base);
Person* findPerson(Person town[], int base, string target);
bool stable(Person town[], int base);
bool cheats(Person *p, Person town[], int base);
bool howBoutIt(Person* g, string dj);

int main()
{
	srand(time(0));
	//variables
	int userNum;

	//prompt the user to enter the number of couples they wish to create
	cout << "Enter number of couples (1 - " << numOfMenOrWomen << "): ";
	cin >> userNum;
	std::cin.clear();
	std::cin.ignore(10000, '\n');

	// keep the number of couples created within a safe range
	if (userNum > numOfMenOrWomen) userNum = numOfMenOrWomen;
	else if (userNum < 0) userNum = 0;

	//dynamically allocate array which will store the names of men in our town
	string* menInTown = new string[userNum];

	//dynamically allocate array which will store the names of women in our town
	string* womenInTown = new string[userNum];

	// dynamically allocate array of Person structs with size of userNum * 2, to have space for both the men and women
	Person* peopleInTown = new Person[userNum * 2];


	// create random assortment of men in our town based off our complete list of men names
	Sublist(menNames, numOfMenOrWomen, menInTown, userNum);
	// create random assortment of women in our town based off our complete list of women names
	Sublist(womenNames, numOfMenOrWomen, womenInTown, userNum);

	cout << "Men in Town: ";
	displayStrings(menInTown, userNum, "");
	cout << endl;

	cout << "Women in Town: ";
	displayStrings(womenInTown, userNum, "");
	cout << endl;

	pick(menInTown, womenInTown, peopleInTown, userNum);

	while (stable(peopleInTown, userNum) != true) {
		Person* female;
		Person* male;

		display(peopleInTown, userNum);

		while (true) { // infinite loop that will only break once user has specified correct names
			string inputNames;
			cout << "Enter two names to marry, list the woman first: ";
			getline(cin, inputNames);

			istringstream nameStream(inputNames);
			string name;

			nameStream >> name; // grab first name from the stream we created from user's inputted names
			female = findPerson(peopleInTown, userNum, name); // find the person in the town with the name that we just grabbed

			nameStream >> name; // grab second name from the stream we created from user's inputted names
			male = findPerson(peopleInTown, userNum, name); // find the person in the town with the name that we just grabbed

			if (female != NULL && male != NULL) {
				if (marry(female, male) == true) break; // try to marry the two people, and break the infinite loop if successful
			}
			else cout << "One or both of the people you gave us were not found in the town, please try again." << endl;
		}

		cout << "-----------------------------" << endl;

	}

	cout << "Congratulations, Everyone is happy!";

	//keep open
	int x;
	cin >> x;


	return 0;

}

void Sublist(const string bigList[], const int bigNum, string smallList[], const int smallNum)
{
	// loop through smallList[]
	for (int i = 0; i < smallNum; i++)
	{
		string temp = bigList[rand() % bigNum]; // store a random name from bigList[]

		for (int j = 0; j < smallNum; j++) { // loop through smallList[] to search for duplicate entry
			if (temp == smallList[j]) { // if one exists,
				temp = bigList[rand() % bigNum]; // then grab a new random name from bigList[]
				j = -1; // and reset the loop, to redo the check through smallList with the new random name (we set it to -1 because the loop will increment it to 0)
			}
		}
		smallList[i] = temp;
	}
}

void pick(string men[], string women[], Person which[], int N)
{
	for (int i = 0; i < N; i++) {
		which[i].name = men[i];
		which[i].female = false;
		which[i].spouse = "";
		which[i].likes = new string[3];
		which[i].numLikes = 3;
		
		Sublist(women, N, which[i].likes, 3);
	}
	cout << endl;
	for (int i = 0; i < N; i++) {
		which[N + i].name = women[i];
		which[N + i].female = true;
		which[N + i].spouse = "";
		which[N + i].likes = new string[3];
		which[N + i].numLikes = 3;

		Sublist(men, N, which[N + i].likes, 3);
	}
}

void displayStrings(string *s, int size, string sp)
{
	for (int i = 0; i < size; i++)
	{
		if( s[i] != sp ) cout << capitalize(s[i]); // if s[i] doesnt match sp, then just print out s[i], with the first letter capitalized
		else cout << toUpperCase(s[i]); // otherwise, print out s[i] in all uppercase

		if (i < size - 2) cout << ", ";
		else if (i == size - 2) cout << ", and ";
	}
}

void display(Person town[], int base)
{
	int townSize = base * 2;
	// dynamically allocate an array of pointers to a Person struct
	Person** p = new Person*[townSize];

	for (int i = 0; i < townSize; i++) { // loop through each person in the town
		p[i] = &(town[i]); // point each pointer in the array of pointers to the memory address of each person in the town
	}
	for (int i = 0; i < townSize; i++) { // loop through the array of pointers that now point to each person in the town
		displayp(p[i]); // and display information about each person
		cout << endl;
	}

	delete p; // delete array of pointers on heap
	p = nullptr; // and remove address from pointer p
}

string toUpperCase(string s) {
	for (int i = 0; i < s.size(); i++)
	{
		// change character in string to upper case character
		s[i] = toupper(s[i]);
	}

	return s;
}
string toLowerCase(string s) {
	for (int i = 0; i < s.size(); i++)
	{
		// change character in string to upper case character
		s[i] = tolower(s[i]);
	}

	return s;
}
string capitalize(string s) {
	s = toLowerCase(s);
	s[0] = toupper(s[0]);
	return s;
}

void displayp(Person *p)
{
	string gender;

	if (p->female) gender = "(F)";
	else gender = "(M)";

	if (p->spouse != "") cout << '\t'; // print a tab if this person has a spouse

	//cout display
	cout << capitalize(p->name) << ' ' << gender << " likes ";
	displayStrings(p->likes, p->numLikes, p->spouse);
}

// marry p1 (female) with p2 (male)
//p1 MUST BE FEMALE and P2 MUST BE MALE
//return true if the genders are in that order
bool marry(Person* p1, Person* p2) {
	if (p1->female && !(p2->female)) {
		if (p1->spouse == "" && p2->spouse == "") {
			p1->spouse = p2->name;
			p2->spouse = p1->name;
		}
		return true; // p1 is female and p2 is male, the correct order
	}
	else if (p1->female && p2->female) {
		cout << endl << p1->name << " and " << p2->name << " are both women. Cannot marry, because our laws are ancient and wrong" << endl;
	}
	else if (p1->female == false && p2->female == false) {
		cout << endl << p1->name << " and " << p2->name << " are both men. Cannot marry, because our laws are ancient and wrong" << endl;
	}
	else if (p1->female == false && p2->female == true) {
		cout << endl << "Cannot marry, you must specify the woman's name first and then the man's. We are strangely progressive in this respect!" << endl;
	}

	return false; // was not able to marry p1 and p2
}

void divorce(Person* p, Person town[], int base) {

	if (p->spouse != "") { // check if person p is married first
		Person* p2 = findPerson(town, base, p->spouse); // find spouse and set their memory address to pointer p2

		// if p2 is indeed married to p, then we can divorce them
		if (p2->spouse == p->name) {
			p->spouse = "";
			p2->spouse = "";
		}
	}
}

//Search the town(will be base * 2 Persons) and return the person who has the name 'target'
//(or else return NULL).
Person* findPerson(Person town[], int base, string target) {
	Person* p = new Person; // create pointer to hold the memory address of the target person we want to find in the town

	for (int i = 0; i < base*2; i++) { // search through town
		if (toLowerCase(target) == toLowerCase(town[i].name)) { // if the spouse's name matches someone in the town, use toLowerCase to remove caps-sensitivity
			p = &(town[i]); // set the pointer p to the address of that person
			return p; // we found them, so break out of the loop
		}
	}

	return NULL;
}

//Return true if no one cheats and everyone is married.
//base is half the size of the town, aka the number of men or the number of women in the town.
bool stable(Person town[], int base) {

	int townSize = base * 2;
	bool isNoCheaters = true;
	bool isEveryoneMarried = true;

	// dynamically allocate an array of pointers to a Person struct
	Person** p = new Person*[townSize];

	// point each pointer in the array of pointers to the memory address of each person in the town
	for (int i = 0; i < townSize; i++) {
		p[i] = &(town[i]);
	}

	// loop through the array of pointers that now point to each person in the town, and check if any of them are cheating
	for (int i = 0; i < townSize; i++) {
		if (cheats(p[i], town, base) == true) { isNoCheaters = false; break; } // if we find a cheater, then we mark isNoCheaters as false
	}

	// loop through the array of pointers that now point to each person in the town, and check if they all have a spouse
	for (int i = 0; i < townSize; i++) {
		if (p[i]->spouse == "") { isEveryoneMarried = false; break; } // if we find someone in the town without a spouse, mark isEveryoneMarried as false
	}

	delete p; // delete array of pointers on heap
	p = nullptr; // and remove address from pointer p

	if(isNoCheaters && isEveryoneMarried) return true; // town is stable if there are no cheaters and everyone is married
	else return false; // otherwise, unstable

}

//This should return whether or not this person can cheat. If they are not married, they
//cannot cheat(by definition). If they ARE married, poll the people in this persons
//'likes' list, the ones BEFORE their current spouse.
bool cheats(Person *p, Person town[], int base) {
	if (p->spouse == "") return false;
	else {
		int spouseIndex = 0;
		int numLikes = p->numLikes;

		for (int i = 0; i < numLikes; i++) { // search through Person p's likes list to figure out location of their spouse in the list
			if (p->spouse == p->likes[i]) { // if we found their spouse in the list
				spouseIndex = i; // set the spouseIndex to i
				break; // break out of the loop since we found the spouse
			}
		}

		if (spouseIndex == 0) return false; // if spouse is first person on their likes list, they will not cheat

		for (int i = 0; i < spouseIndex; i++) { // loop through the likes list up to and before the married spouse and ask them if they'll cheat with Person p
			Person* potentialCheater = findPerson(town, base, p->likes[i]); // find the potential Person who will cheat with Person p, set their memory address to pointer

			if (howBoutIt(potentialCheater, p->name) == true)
			{
				cout << p->name << " cheats with " << potentialCheater->name << endl; // notify user that Person p will cheat with the name of our potentialCheater
				return true; // if any potential cheaters wants to cheat with our Person p, then return true (Person p will cheat with potentialCheater)
			}
		}
	}
}

//Will Person 'g' hook up with 'dj' ? If 'g' is not married, yes. If 'g' IS married, see if dj
//(the name of the Person offering) appears on Person g's likes list BEFORE g's spouse. If so, it's ON!
bool howBoutIt(Person* g, string dj) {
	if (g->spouse == "") return true;
	else {
		int spouseIndex = 0;
		int numLikes = g->numLikes;

		for (int i = 0; i < numLikes; i++) { // search through Person g's likes list to figure out location of their spouse in the list
			if (g->spouse == g->likes[i]) { // if we found their spouse in the list
				spouseIndex = i; // set the spouseIndex to i
				break; // break out of the loop since we found the spouse
			}
		}

		if (spouseIndex == 0) return false; // if spouse is first person on their likes list, Person g will not hook up with dj

		for (int i = 0; i < spouseIndex; i++) { // loop through the likes list of Person g up to and before spouseIndex and see if dj is listed there
			if (g->likes[i] == dj) return true; // if dj is found, the two will hook up
		}
	}
}