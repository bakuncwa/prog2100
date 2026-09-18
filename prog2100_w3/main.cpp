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

cout << phrase1 << endl;
cout << phrase2 << endl;
cout << phrase3 << endl;
cout << phrase4 << endl; // ESC sequence for new line is included in the string literal, or

//address of phrase1 variable
cout << &phrase1 << endl; // returns hex code

// error: cannot dereference a string literal/cannot dereference a non-pointer variable
//cout << *phrase1 << endl;

string *p1; // declare a pointer using * declarative operator
string *p2;
string *p3;

p1 = &phrase1; // assign address to pointer var
p2 = &phrase2;
p3 = &phrase3;
string *p4 = &phrase4; // declare and assign at same time

cout << p1 << endl; // value inside pointer e.g., what is points to
cout << *p1 + *p2 + *p3 + *p4 << endl; // dereferences the pointers to get the string values and concatenates them (overload), or
cout << *p1 << *p2 << *p3 << *p4 << endl;
// dereference happens first, then all becomes a single string literal, then concatenation happens
cout << *p1 << endl; // deref - gets what is pointed to
cout << &p1 << endl; // returns address of pointer variable, not the value
// string x = p1 + p2; // error trying to add memory (hex) addresses
string y = *p1 + *p2; // concat operation of two strings; overload

// 2 pointers point to the same variable
cout << p1 <<endl; // value that is address of poem line 1
cout << p2 <<endl; // line 2
p1 = p2; // reassign pointer to point to phrase2, so p2 value is now the same as p1 value, which is the address of phrase2
cout << p1 <<endl; // value that is address of poem line 1
cout<< p2 <<endl; // line 2
cout << *p1 << endl; //value that is address of poem line2
cout << *p2 << endl; //value that is address of poem line2

//a nameless variable
//heap - free store - dynamic memory allocation = not dynamic, dynamic variable
//use `new` to allocate memory on the heap
int *pNless; // declare integer pointer variable
pNless = new int; // pointing to memory in the heap
*pNless = 3; // dereference the pointer and assign a value to the memory location it points to
cout << *pNless << endl; // dereference the pointer to get the value stored in the heap memory location

int *pN2 = new int(7); // declare and assign at the same time
cout << *pN2 << endl; // dereference the pointer to get the value stored
// delete pNless; // free the memory allocated on the heap
}