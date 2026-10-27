//Demo - Custom String Class – “rule of three”
//Please see additional support resource for a version that uses “char * buf” as the strMem instead of the
//Library “string” class and implements move constructors (post C++ 11 “rule of five”)

#define _CRT_SECURE_NO_WARNINGS // when using depricated library functions e.g. pre 11
#include <iostream>
#include <cstdio>
#include <string.h> //for testing purposes - see toString()
using namespace std;

class String //strMem is the Member, strIn is a parameter
{

private:
char *strMem;
public:
String()//default
{
cout << "default constructor fired" << endl;
this->strMem = NULL; //*** breaks += overload ***//
//this->strMem = new char[0];
}

String(const char *strIn)//one arg constructor
{
cout << "one arg constructor fired" << endl;
int len = strlen(strIn);//len of incoming str
this->strMem = new char[len + 1];//new local array
strcpy(this->strMem,strIn);//depricated
//strcpy_s(this->strMem,sizeof(this->strMem),strIn);

}
String(const String& strIn)//copy constructor
{
cout << "copy constructor fired" << endl;
int len = strlen(strIn.strMem);//len of incoming str
this->strMem = new char[len + 1];//new local array
strcpy(this->strMem,strIn.strMem);//depricated
//strcpy_s(this->strMem,sizeof(this->strMem),strIn.strMem);
}

~String() ///default destructor causes mem leak because it does not deallocate array
{
cout << "destructor fired" << endl;
if (this->strMem != NULL)
{
delete [] this->strMem;//[] tells that it is dealing with an array
}
}

String operator= (const String& strIn)//overloaded =op
{
cout << "overloaded = fired" << endl;
int len = strlen(strIn.strMem);//len of incoming str
this->strMem = new char[len+1];//new local array
strcpy(this->strMem,strIn.strMem);//depricated
//strcpy_s(this->strMem,sizeof(this->strMem),strIn.strMem);
return *this;

}

String operator+= (const String& strIn)//overloaded +=op
{
cout << "overloaded += fired" << endl;

char* temp = this->strMem;//story copy of prop

int len = strlen(this->strMem) + strlen(strIn.strMem);//calc size of new larger array
this->strMem = new char[len + 1];//destroy prop and create bigger one
strcpy(this->strMem,temp);//depricated
//strcpy_s(this->strMem,sizeof(this->strMem),temp);
strcat(this->strMem, strIn.strMem);
this->strMem[len] = '\0';
delete [] temp;//prevent leak
return *this;//for cascades
}

friend ostream& operator<<(ostream& output, String& strIn)
{
output << strIn.strMem;
return output;//return an ostream
}

};//end String class


int main()
{
cout << "Begin tests of custom string class" << endl << endl;

cout << "Begin test one" << endl;
String fullName;
String firstName("Bob");//test of constructor with argument
String lastName(" Loblaw");//test of constructor with argument
fullName = "";
fullName+=firstName;//test of += operator
fullName+=lastName;//test of += operator
cout << "Full Name: " << fullName << endl << endl;

cout << "Begin test two" << endl;
String name1("Bob");
String name2("Loblaw");
cout << "Name1: " << name1 << endl;
cout << "Name2: " << name2 << endl;
name1=name2;//test of = operator
cout << "Name1: " << name1 << endl;
cout << "Name2: " << name2 << endl;

cout << "Tests complete" << endl;

return 0;
}//end main
