//This is a demonstration driver for MyOwnMath class

#include <iostream>
#include <conio.h>
#include "MyOwnMath.h"//prog defined
using namespace std;

int main() {
    int ans1=0;
    int ans2=0;
    int input=0;
    MyOwnMath myOwnMathObj;

    cout << "Enter an int 1-9" << endl;
    cin >> input;
    ans1 = myOwnMathObj.square(input);
    ans2 = myOwnMathObj.add(input,input);
    cout << "Your number squared is: "<<ans1<<endl;
    cout << "Your number added to self is: "<<ans2<<endl;

    return 0;
}