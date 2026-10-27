//Header for class Bicycle
// Created by W0068332 on 9/4/2020.


#ifndef POLYVEHICLES_BICYCLE_H
#define POLYVEHICLES_BICYCLE_H
#include <string>
#include "Vehicle.h"


class Bicycle : public Vehicle //inherits
{
public:
    Bicycle(void);//default constructor
    virtual ~Bicycle(void);
    virtual string BlowHorn();
};

#endif //POLYVEHICLES_BICYCLE_H
