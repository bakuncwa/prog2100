//How to Shuffle a Vector Demo
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

void print(vector<int> const &v); //prototype

int main() {
vector<int> v = {1,2,3,4,5,6};//populate vector
unsigned seed = chrono::system_clock::now().time_since_epoch().count();//create random seed using system clock
shuffle(v.begin(),v.end(),default_random_engine(seed));
print(v);//call print method below
return 0;
}

void print(vector<int> const &v)
{
for(int i=0;i<v.size();i++)
{
//for(int i: v) {
cout << v[i] << endl;
}
}
