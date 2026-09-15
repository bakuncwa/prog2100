//Demo of IO/Random/loop - Adjusted to VSCode IDE

#include <iostream> //for cin, cout, endl
#include <string> //for string class
#include <sstream> //for stringstream
#include <ctime> //for time()

using namespace std; // for cin, cout, endl, string, stringstream


// int main()
// {
// string name;
// cout << "Please enter you full name: ";
// getline(cin, name); // for reading a full line of text including spaces
// cout << "Hello " << name << ".\n";
// cin.get(); //_getch();
// return 0;
// }//end main; shows in Debug Console



// int main()
// {
// string mystr;
// float price = 0;
// int quantity = 0;

// cout << "Enter price: ";
// getline(cin, mystr);
// //price = mystr; //conversion error str to float
// stringstream(mystr) >> price;
// cout << "Enter quantity: ";
// getline(cin, mystr);
// stringstream(mystr) >> quantity;
// cout << "Total cost: " << price * quantity <<endl;
// cin.get(); //_getch();
// return 0;
// }//end main
// // integer x = 3; // tight wrapper
// // int x = 3; // loose wrapper, primitive


int main()
{
srand(time(0));//send srand (pseudorandom) the time as a seed value
for (int i = 0; i < 100; i++)
{
// cout << i + 1 << " " << rand() << endl;//not scaled 
cout << i + 1 << " " << 1 + rand() % 10 << endl; // scales with modulus operator to 1-10 (no base 0; 
// takes the remainder of the division of rand() by 10 and adds 1 to shift the range from 0-9 to 1-10)
}
cin.get();
return 0;
}//end main