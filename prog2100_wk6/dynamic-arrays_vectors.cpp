//Topic: dynamic arrays, use of const modifier
//Note: Dynamic means declared on heap not size changing

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//int main() {
// int size = 4;
// int myArray[size];//error variable size
// int myArray2[10];//fixed size
// const int SIZE=10;
// int myArray3[SIZE];//use of const modifier

// const int MAX=3;
// int nonD[MAX];
// int c=0;
//
// //read into the above array
// cout<<"Enter an Integer: " << endl;
//
// while(cin>>nonD[c])//if it reads the return as true
// {
// c++;
// if(c<MAX)
// cout<<c<<" elements used "<<"max is: "<<MAX<<endl;
// else
// cout<<"at max - next will exceed array size"<<endl;
//
// for(int i=0;i<MAX;i++)
// {
// cout<<nonD[i]<<endl;
// }
//
// cout<<"Enter an Integer: "<<endl;
// }//end while
//notice that the above will allow you to exceed array bounds

//"Dynamic Array" as in declared in dynamic memory,
//not that its size can change
//This program starts with a small array an then
//adds more space by declaring a new array that is larger.

// int max=3;//note not a const value
// int *dynArray = new int[max];//declare array in dynamic (heap) memory
// int c = 0;
//
// cout<<"Enter an Integer: " << endl;
// while(cin>>dynArray[c])
// {
// c++;
// if(c>=max)//test if array is full and make larger if it is
// {
// max=max*2;//double size of array max var
// int *temp = new int[max];//create temp array to hold data
// for(int i=0;i<c;i++)
// {
// temp[i]=dynArray[i];//copy original into larger temp
// }
//
// //delete dynArray;//mem leak - deletes the first element of array
// delete []dynArray;//tell compiler it is dealing with an array
//
// dynArray = temp;//
//
// cout << "array size is: "<< max <<" "<< max-c <<" now available"<<endl;
//
// }
//
// cout<<"Enter an Integer: " << endl;
// }//end while
//return 0;
//}//end main

//A vector is like an array in many ways, but it is dynamic.
//Operators such as [] may be used to access elements, but you can
//can also access elements using a wide range of built in methods.

int main(){

// vector<float> v;
// cout << v.size() << endl;
// vector<float> v2(10);
// cout << v2.size() << endl;
// v2.resize(5);
// cout << v2.size() << endl;
vector<float> v3 = {11.11,22.22,3.33,4.44};
cout << "Size: " << v3.size() << endl;
v3.push_back(5.55);
cout << "Size: " << v3.size() << endl;

// for(int i=0;i<v3.size();i++)
// {
// cout << v3[i] << ",";
// }

// cout << v3.front()<< " " << v3.at(2) << " " << v3.back() << endl;

vector<float>::iterator iter;
// for(iter = v3.begin();iter!=v3.end();iter++)
// {
// cout << *iter <<endl;
// }

v3.pop_back();//drops last element

for(iter = v3.begin();iter!=v3.end();iter++)
{
cout << *iter <<endl;
}

return 0;
}//end main