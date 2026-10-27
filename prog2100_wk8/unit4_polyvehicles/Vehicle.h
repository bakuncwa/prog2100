//Vehicle.h - header file for Vehicle class
// Created by W0068332 on 9/4/2020.

#ifndef POLYVEHICLES_VEHICLE_H
#define POLYVEHICLES_VEHICLE_H
#include <string>
using namespace std;

class Vehicle {
public:
    Vehicle(void);//constructor
    virtual ~Vehicle(void);//virtal destructor
    //string BlowHorn();//regular
    virtual string BlowHorn();//virtual for late binding
    //virtual string BlowHorn() = 0;//pure virtual ie. abstract

};
#endif //POLYVEHICLES_VEHICLE_H
