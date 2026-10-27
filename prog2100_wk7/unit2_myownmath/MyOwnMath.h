// MyOwnMath header file
// This is the interface for the MyOwnMath class
// It contains two methods square() and int() returning ints
// Created by W0068332 on 9/2/2020.

#ifndef MYOWNMATH_MYOWNMATH_H//if not defined
#define MYOWNMATH_MYOWNMATH_H //then define otherwise don't dupe
using namespace std;

class MyOwnMath{
public:
    MyOwnMath(void);//default constructor
    virtual ~MyOwnMath(void);//virtual destructor
    int square(int);
    int add(int,int);

};//end class MyOwnMath

#endif //MYOWNMATH_MYOWNMATH_H
