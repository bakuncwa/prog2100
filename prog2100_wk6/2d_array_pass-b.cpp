//Note: there are three main ways to pass a 2D array to a function:
//1) The parameter is a 2D array
//2) The parameter is an array containing pointers
//3) The parameter is a pointer to a pointer

//1) The parameter is a 2D array
//int array[10][10];
//void passFunc(int a[][10])
//{...}
//passFunc(array)

//2) The parameter is an array containing pointers
//int *array[10];
//for(int i=0;i<10;i++){
// array[i] = new int[10];
//}
//void passFunc(int *a[10])
//{...}
//passFunc(array);

//3) The parameter is a pointer to a pointer
//int **array;
//array = new int *[10];
//for(int i=0;i<10;i++){
// array[i] = new int[10];
//}
//void passFunc(int **a)
//{...}
//passFunc(array);


#include <iostream>
#include <conio.h>
using namespace std;

//method prototypes
void oneDexample();
void twoDexample();
void mod1Darray(int *p, int);
void mod2Darray(int p[][3], int, int);

int main()
{
//oneDexample();
twoDexample();
_getch();
return 0;
}

void oneDexample()
{
int numArray[] = { 1, 2, 3, 4, 5 };
//int sizeOfNumArray = sizeof(numArray);//20 or 40 if double
//int sizeOfNumArray = sizeof(numArray) / sizeof(numArray[0]);
int sizeOfNumArray = sizeof(numArray) / sizeof(int);
//cout << sizeOfNumArray << endl;

cout << "1D array before modification" << endl;
for (int row = 0; row < sizeOfNumArray; row++)
{
cout << numArray[row] << endl;
}

mod1Darray(numArray,sizeOfNumArray);

cout << "1D array after modification" << endl;
for (int row = 0; row < sizeOfNumArray; row++)
{
cout << numArray[row] << endl;
}


}//end oneDexample

void twoDexample()//example passing 2d array to method
{
int twoDnumArray[][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
int rowSize = sizeof(twoDnumArray) / sizeof(twoDnumArray[0]);
int colSize = 3;

cout << "2d array before modification" << endl;
for (int row = 0; row < rowSize; row++){
for (int col = 0; col < colSize; col++)
{
if (col < colSize)
cout << twoDnumArray[row][col];
else
cout << ",";
}//end for
cout << endl;
}//end for

mod2Darray(twoDnumArray, rowSize, colSize);

cout << "2d array after modification" << endl;
for (int row = 0; row < rowSize; row++){
for (int col = 0; col < colSize; col++)
{
if (col < colSize)
cout << twoDnumArray[row][col] << ",";
}
cout << endl;
}
}//end twoDexample