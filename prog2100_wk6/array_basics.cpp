//Note: Please see support document: Passing & Returning Arrays C++

//Note: For clarity, use array notation when passing arrays to functions

#include <iostream>
#include <array>
using namespace std;

//prototypes
void addTen(int *p, int);//p points to where array begins in mem, int will be # of elements

int main() {
// //1d array
// int a[3];
// a[0]=0;
// a[1]=1;
// a[2]=2;
//
// int b[] = {0,1,2};// declare and fill - initializer
// array<int,6>myArray={0,1,2};
//
// for(int i=0;i<6;i++)
// {
// cout << myArray[i];
// }

//2d array demo
//int my2Darray[][3] ={{0,100,200},{1,300,400},{2,500,600}};//initalize
//
//for(int row=0;row<3;row++){
// for(int col=0;col<3;col++){
// cout<<my2Darray[row][col];
// if(col<2)
// cout << ", ";
// else
// cout << endl;
// }
//}

//Arrays and pointers demo
int a[] = {1,2,3};
int *p; //declare a pointer
p = a; //make pointer point to array. Notice we did not use &

addTen(a,3);
for(int row=0;row<3;row++){
cout<<a[row] << endl;
}

//Calculating the size of an arry for use in loop statements
int numArray[] = { 1, 2, 3, 4, 5 };
//int sizeOfNumArray = sizeof(numArray);//20 as int 40 as double
//int sizeOfNumArray = sizeof(numArray) / sizeof(numArray[0]);
int sizeOfNumArray = sizeof(numArray) / sizeof(int);
cout << sizeOfNumArray;



return 0;
}//end main

//method definition
//void addTen(int a[], int)
//{
// for(int row=0;row<3;row++)
// {
// a[row]+=10;
// }
//}

void addTen(int *p, int) //pass this way - ie by pointer
{
for(int row=0;row<3;row++)
{
p[row]+=10;
}
}