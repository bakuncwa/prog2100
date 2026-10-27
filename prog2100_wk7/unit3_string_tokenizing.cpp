//Topic: Tokenizing
//There are many ways to parse a string. You can use technologies
//such as tolkenizers or the more modern 'split' functions.
//A delimiter is used to split a string into tolkens.
//eg "bob,loblaw" could be split into a first name and lastname
//token using the ',' as the delimeter.
//In c++ you can use the <ctype> library for individual character
//functionality such as 'toupper', 'isalpha', etc.


#define _SCL_SECURE_NO_WARNINGS // these pre-processor directives tell VT not to flag certain "errors" that are not
#define _CRT_SECURE_NO_WARNINGS // necessarily errors but are often not VS specific usage
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
using namespace std;


//prototypes
void strtokExample();
void chartokExample(string str);

int main()
{
string s = "Hello $";

cout << "Launch string token example" << endl;
strtokExample();
cout << "Launch character token example" << endl;
chartokExample(s);
return 0;
}

//strtok example
void strtokExample()
{
int numT = 0;//token counter

char str[] = "hello,world";//string to be tokenized
char* pch = NULL;
printf("Splitting string \"%s\" into tokens:\n\n", str);
pch = strtok(str, " ,.-");
while (pch != NULL)
{
printf("%s\n", pch);
pch = strtok(NULL, " ,.-");
numT++;
}
cout << "\nTotal tokens: \n" << numT << endl;
cout << "press any key for next example\n\n" << endl;
_getch();

}//end method strtokExample

//chartoExample
void chartokExample(string strIn)
{
char dol;
cout << "Parsing string: ""Hello"" $ into tokens \n"<< endl;
char cArray[20];//create a char array size 20
strIn.copy(cArray, 20);//copy string into char array
for (int i = 0; i < 20; i++)
{
if (cArray[i] == '$')
dol = cArray[i];
}
cout << dol << endl;
_getch();

}//end method chartoExample
