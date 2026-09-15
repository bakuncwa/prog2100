// The postal code is a six-character uniformly structured, alphanumeric code in the form "ANA NAN"
// where "A" is an alphabetic character and "N" is a numeric character.
// Two segments make up a postal code: Forward Sortation Area (FSA) and Local Delivery Unit (LDU).
//The FSA is a combination of three characters (alpha-numeric-alpha). It identifies a major geographic area in an urban or a rural location.
// The LDU is a combination of three characters (numeric-alpha-numeric). It identifies the smallest delivery unit in an FSA.
// Reference: https://www.canadapost-postescanada.ca/cpc/en/support/articles/addressing-guidelines/postal-codes.page

#include <iostream>
#include <regex> //regex library for validating input = chevron referencing <<
#include <string>

using
namespace
std;

//Sentinel-controlled input using recursion instead of a while loop.
//The function calls itself after each entry until the sentinel value "q" is entered.
void getPostalCode()
{

//Regex for a Canadian postal code in the form ANA NAN
//[A-NP-VX-Ya-np-vx-y] = first character: any letter except O, W and Z;
//O is never used anywhere in a postal code, and W/Z never start one
//(Canada Post addressing guidelines)
//[A-NP-Za-np-z] = the other two letter positions: any letter except O
//[0-9] = numeric character (N)
//[ -]? = optional single space OR hyphen between the FSA and LDU segments;
//dots and any other punctuation are not permitted
regex postal_expr("^[A-NP-VX-Ya-np-vx-y][0-9][A-NP-Za-np-z][ -]?[0-9][A-NP-Za-np-z][0-9]$");

string input;

cout << "Enter a postal code (q to quit): ";

//getline is used instead of cin>> so a space between the FSA and LDU
//(e.g. "B3S 1G5") is captured as part of the input instead of splitting it
getline(cin,input);

if(!cin) return;

//Sentinel value: entering q stops the recursion (acts like the while loop's exit condition)
if(input=="q")

return;

if(regex_match(input,postal_expr))

cout<<"Input is a valid postal code"<<endl;

else

cout<<"Invalid input: Not a valid postal code"<<endl;

//Recursive call replaces the while loop; the sentinel check above ends the recursion
getPostalCode();

}

int main()

{

getPostalCode();

return 0;

}