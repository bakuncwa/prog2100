// MyOwnMath.cpp
// This is the Implementation file
// More description goes here
// Created by W0068332 on 9/2/2020.

#include <iostream>
#include <conio.h>
#include "MyOwnMath.h" //programmer defined header
using namespace std;

//implementation ie code for all methods
MyOwnMath::MyOwnMath() {}//default constructor
MyOwnMath::~MyOwnMath() {}//default virtual destructor

int MyOwnMath::add(int num1, int num2) {
    return num1 + num2;
}

int MyOwnMath::square(int num) {
    return num*num;
}