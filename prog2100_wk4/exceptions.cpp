//Exceptions Demo 1) Standard, 2) Div by Zero, 3) Programmer Defined

//Notes:
// Unlike Java, C++ does not support the manual throwing of system errors.
// Examples like dividing by zero are logical errors, so you should not let
// them happen in the first place. In addition, catching exceptions is
// significantly more expensive than divisor checking would be.
// Always handle validation first programmatically, and then only use
// exceptions as a backup.

#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

//Prototypes
void StandardDemo();
void DivByZeroDemo();
void ProgDefinedDemo();

int main() {
    // cout << "Standard Exceptions Demo"<<endl;
    // StandardDemo();

    // cout << "Division by Zero Exception Demo"<<endl;
    // DivByZeroDemo();

    // cout << "Programmmer Defined Exceptions"<<endl;
    // ProgDefinedDemo();
    return 0;
}//end main

int compare(int a, int b) {
    if (a < 0 || b < 0) {
        throw invalid_argument("received negative value");
    }
}//end method compare

void StandardDemo(){
    try {
        compare(-1, 3);
    }
    catch (const invalid_argument& e) {
        cout << "exception fired" << endl;
    }
}//end method StandardDemo


double division(int a, int b)
{
    if (b == 0)
    {
        throw "Division by zero condition!";
    }
    return (a / b);
}//end method division

void DivByZeroDemo(){
    int x = 10;
    int y = 0;
    double z = 0;

    cout << "Numerator is: 10" << endl;
    cout << "Enter Denominator: ";
    cin >> y;

    try {
        z = division(x, y);
        cout << "Your answer is: " << z << endl;
    }
    catch (const char* msg) {
        cout << msg << endl;
    }
}//end method DivByZeroDemo



//note: The only difference between a struct and class in C++ is the default
// accessibility of member variables and methods. In a struct they are public;
// in a class they are private.
struct MyException : public exception
{
public:
    const string what()
    {
        return "My Exception Happend";
    }
};//end struct


void ProgDefinedDemo(){
    try
    {
        throw MyException();
    }
    catch (MyException& e)
    {
        cout << "MyException caught" << endl;
        cout << e.what() << endl;
    }
    catch (exception& e)
    {
        //Other errors
    }
    catch (...){
        //Other errors
    }
}//end method ProgDefinedDemo
