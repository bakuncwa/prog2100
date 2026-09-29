//Support: Practice Exceptions Lab
//
// Does the order of the catch statements matter?
// Try mixing up the order of the catch statements what happens? why?
// Try and 'rethrow' the exception (in catch of E1). Does 'throw E1' or 'throw e1' or just 'throw' work? If not, why?
// How may you still catch the error?
// If a language has a finally catch (... in c++), why does this get called regardless?

//Example using structures
#include <iostream>
#include <exception>
using namespace std;


struct E1
{
    const char* message;
    E1() : message("Struct E1"){}
};


struct E2
{
    const char* message;
    E2() : message("Struct E2"){}
};


void f()
{
    try
    {
        cout << "In try block of f()" << endl;
        cout <<"Throwing exception of type E1" << endl;
        E1 e1;
        E2 e2;
        throw e1;// programmer thrown
        //throw e2;
    }//end try
    catch(E1 e1)
    {
        cout << e1.message << endl;
    }
    catch(E2 e2)
    {
        cout << e2.message << endl;
    }

    catch(...)// or use exception e
    {
        cout << "An unknown error happened" << endl;
    }

}//end function f


int main(){

    try{
        f();
    }
    catch(...)
    {
        cout << "Cought you anyway" << endl;
    }
    cin.get();
    return 0;
}//end main
