// Character Validation as a String Example
/*
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {

bool rejected = false;

string name;

while(true)

{

cout << "Enter your name:";

getline(cin,name);

for(int i=0;i<name.length()&&!rejected;i++)

{

if(isalpha(name[i])) //if the character is a letter, accept it

continue;

if(name[i]==' ')

continue;

rejected = true;
//otherwise reject

}
//end for

if(!rejected)
//input valid

{

cout << "Input is valid";

break;

}else{

cout << "Input is NOT valid"<<endl;

rejected = false;
//reset

}

}
//end while
return 0;

}
*/

// -------------------------------------------

// Numeric Validation as a String Example
/*
#include <iostream>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

int main() {

string strAge;

int age;

stringstream ss;

bool valid = true;

while(1){

cout << "Enter your age:";

cin >> strAge; // for pointers with no spacing e.g., integers

for(int i=0;i<strAge.length();i++){

if(!isdigit(strAge[i]))

{

valid=false;

cout <<"Input is NOT valid"<<endl;

break;
//out of for loop

}

ss << strAge; // ss for conversion operation to avoid conversion error from string to int
//convert str to int

ss >> age;

}
//end for

if(valid)

{

cout << "Age is valid: " << age << endl;

break;
//out of while loop

}else{

valid=true;

}

}
//end while

return 0;

}
*/

// -------------------------------------------

// Demo: Validation using Regex
// Use of regex to validate incoming data (an integer)

#include <iostream>
#include <regex> //regex library for validating input = chevron referencing <<
#include <string>

using
namespace
std;

int
main()

{

string input;

regex integer_expr("(\\+|-)?[[:digit:]]+"); //regex expression for an integer, replaces manual if-statements

//If input correct ask for another number

while(true)

{

cout<<"Enter the input: ";

cin>>input;

if(!cin) break;

//Exit when the user inputs q

if(input=="q")

break;

if(regex_match(input,integer_expr))

cout<<"Input is an integer"<<endl;

else

{cout<<"Invalid input: Not an integer"<<endl;}

}
}
