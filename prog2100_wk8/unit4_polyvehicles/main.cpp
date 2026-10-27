//Demonstration Driver for Vehicle and its sub classes
#include <iostream>
#include <conio.h>
#include "Vehicle.h"
#include "Boat.h"
#include "Bicycle.h"
using namespace std;

//prototypes
void withoutCasting();
void sliceExample();
void upCasting();
void downCasting();
void typeIDExample();
void polyExample();

int main() {
//    withoutCasting();
//    sliceExample();
//    upCasting();
//    downCasting();
//    typeIDExample();
//    polyExample();

    return 0;
}//end main

//Method implementations
void withoutCasting(){
    Bicycle myBike;//instantiation of classes
    Boat myBoat;
    cout << myBike.BlowHorn() << endl; //early bind
    cout << myBoat.BlowHorn() << endl; //early bind
}

void sliceExample(){
    Bicycle myBike;
    //Vehicle v1 = myBike;//implicit
    Vehicle v1 = (Vehicle)myBike;//explicit upcast
    cout << v1.BlowHorn() << endl;
    //solution is to use pointers and dynamic variables so that
    //we may treat v1 as a Bike at runtime and not slice it.
}

void upCasting(){
    Vehicle *pV = new Vehicle;//declared on heap ie dynamic
    Bicycle *pBic = new Bicycle;
    Boat *pBoat = new Boat;
    pV = pBic;//up cast
    cout << pV->BlowHorn()<<endl;
}

void downCasting(){
    cout << "upcast Boat to Vehicle pointer:"<<endl;
    Vehicle *pV = new Boat;//upcast boat
    Bicycle *pBic = dynamic_cast<Bicycle*>(pV);
    cout << "pBic = " << pBic << endl;//wrong type returns NULL
    Boat *pBoat = dynamic_cast<Boat*>(pV);
    cout << "pBoat = " << pBoat << endl;//correct type returns an address
}

void typeIDExample(){
    Vehicle *pV = new Boat;//upcast
    if(typeid(Bicycle)== typeid(*pV))
        cout << "pV points to a Bicycle" << endl;
    else
        cout << "pV points to a Boat" << endl;
}

void polyExample(){ //late binding routine
    Vehicle *pV = new Vehicle; // on heap
    Bicycle *pBic = new Bicycle;
    Boat *pBoat = new Boat;

    //Vehicle *pVArray[2];//declared on stack
    Vehicle **pVArray = new Vehicle*[2];//declared on heap
    //** because an array is a pointer in C++ and its contents are pointers

    pVArray[0] = (Vehicle*)pBic; //expl upcast
    pVArray[1] = (Vehicle*)pBoat;//expl upcast

    for(int i=0;i<2;i++)
    {
        cout << pVArray[i]->BlowHorn()<<endl;//late bind
    }

}

