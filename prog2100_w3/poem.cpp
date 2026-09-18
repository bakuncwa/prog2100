//Pointer Basics

#include <iostream>

#include <string>


using namespace std;







int main()

{

//pointer terminology

// use * to declare a pointer variable

// also use * as the dereference operator

// use & as the 'address of' operator

// use -> as the ‘points to’ operator




string phrase1 = "I woz here. ";

string phrase2 = "Here I woz. ";

string phrase3 = "Woz I here? ";

string phrase4 = "Yes I woz!";




cout << phrase1 + phrase2 + phrase3 + phrase4 << endl;

// regular use of variable names




cout << &phrase1 << endl;

//cout << *phrase1 << endl;




string *p1; //declare a pointer using * declarative operator

string *p2;

string *p3;




p1 = &phrase1; //assign address to pointer var

p2 = &phrase2;

p3 = &phrase3;




string *p4 = &phrase4; //declare and assign at same time




cout << p1 << endl; // address ie value inside p1

cout << *p1 + *p2 + *p3 + *p4 << endl; // shows epic poem

cout << *p1 << endl; //what is pointed to

cout << p1 << endl;//value inside pointer

cout << &p1 << endl;//address of the pointer variable




//string x = p1 + p2; //error trying to add mem addresses

string y = *p1 + *p2; //concat operation of two strings




cout << p1 << endl;

cout << p2 << endl;

p2 = p1; // assignes content/value of p1 (an address) to p2

cout << p1 << endl;

cout << p2 << endl;




//how to make a "nameless" variable (aka dynamic variable)

int *pNless; // declare an integer pointer

pNless = new int; // pointer to a dynamic var (aka nameless)

*pNless = 3;//assign an int value to nameless mem location

cout << *pNless << endl;




int *pN2 = new int(7); //nameless on one line


cin.get();

return 0;

}