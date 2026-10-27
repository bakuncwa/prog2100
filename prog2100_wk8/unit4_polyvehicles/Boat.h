//Boat.h - header file for Boat class
// Created by W0068332 on 9/4/2020.

#ifndef POLYVEHICLES_BOAT_H
#define POLYVEHICLES_BOAT_H
#include <string>
#include "Vehicle.h"


class Boat : public Vehicle //inherits
{
    public:
        Boat(void);//default constructor
        virtual ~Boat(void);
        virtual string BlowHorn();
};

#endif //POLYVEHICLES_BOAT_H
