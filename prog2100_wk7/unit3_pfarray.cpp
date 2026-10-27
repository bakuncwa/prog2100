//Topic – Rule of Three Demonstration using a class representing a partially filled array
//Class PFArray – A class for a partially filled array of doubles. An object of this class can be accessed
//using the square brackets just like an ordinary array, but also keeps track of how much of the array
//is in use.
//Main – a driver to demonstrate the PFArrray class
#include <iostream>
using namespace std;
class PFArray{
private:
double *a;//array of double
int capacity;//size of array
int used;//amount of size used
public:
PFArray();
PFArray(int capacityValue);
PFArray(const PFArray& pfaObj);//copy constructor
void addElement(double element);
bool full() const {return(capacity==used);}
int getCapacity() const {return capacity;}
int getUsed() const {return used;}
void emptyArray(){used=0;}
double& operator[](int index);
PFArray& operator = (const PFArray& rightSide);//assignment
~PFArray();//destructor
};//end class
PFArray::PFArray() :capacity(50),used(0)
{
cout << "Default Constructor called" << endl;
a=new double[capacity];
}
PFArray::PFArray(int size) :capacity(size),used(0)
{
cout << "One Arg Constructor called" << endl;
a=new double[capacity];
}
PFArray::PFArray(const PFArray &rightSide)//copy constructor
:capacity(rightSide.getCapacity()),used(rightSide.getUsed())
{
cout << "Copy Constructor called" << endl;
if(capacity != rightSide.capacity)
{
delete []a;
a = new double[rightSide.capacity];
}
capacity = rightSide.capacity;
used = rightSide.used;
for(int i=0;i<used;i++)
{
a[i] = rightSide.a[i];
}
}
void PFArray::addElement(double element) //append content to array
{
cout << "Add Element called" << endl;
if(used >= capacity)
{
cout << "Attempt to exceed bounds";
exit(0);
}
a[used] = element;
used++;
}
double& PFArray::operator[](int index)
{
cout << "Overloaded [] called" << endl;
if(index >= used)
{
cout << "illegal index" << endl;
exit(0);
}
return a[index];
}
PFArray& PFArray::operator=(const PFArray &rightSide)
{
cout << "Assignment called" << endl;
if(capacity != rightSide.capacity)
{
delete []a;
a = new double[rightSide.capacity];
}
capacity = rightSide.capacity;
used = rightSide.used;
for(int i=0;i<used;i++)
{
a[i] = rightSide.a[i];
}
return *this;
}
PFArray::~PFArray() {
cout << "Destructor called" << endl;
delete []a;//to avoid leaks
a=NULL;// so you have a known state that you can test later
}
//Rule of 5 means move methods are also taken into consideration (not coded in this example)
void testPFArray();
int main()
{
cout << "This program tests the class PFArray" << endl;
char ans;
do
{
testPFArray();
cout << "Test again? (y/n) ";
cin >> ans;
}while ((ans=='y') || (ans=='Y'));
return 0;
}//end main
void printCapacity(const PFArray PFA)//to demo copy constructor
{
cout << "printCapacity method called" << endl;
cout << PFA.getCapacity() << endl;
}
void testPFArray()
{
int cap;
cout << "Enter capacity of this super array: ";
cin >> cap;
PFArray pfaObj(cap);
cout << "Enter up to " << cap << " nonnegative numbers.\n";
cout << "Place a negative number at the end.\n";
double next;
cin >> next;
while((next >= 0) && (!pfaObj.full()))
{
pfaObj.addElement(next);
cin >> next;
}
if(next>=0)
{
cout << "Could not read all numbers" << endl;
//clear the unread input
while(next >= 0)
cin >> next;
}
int count = pfaObj.getUsed();
cout << "The following " << count << " numbers read and stored:" << endl;
int index;
for(index = 0; index < count; index++)
cout << pfaObj[index] << " "; //use of overloaded [] operator
cout << endl;
PFArray PFAone = PFArray(3);
PFArray PFTwo = PFArray(12);
PFAone = PFTwo;
cout << PFAone.getCapacity() << endl;
cout << "Passing a PFA to the printCapacity method fires the CC" << endl;
cout << "so that the method will have its own autonomous (deep)copy" << endl;
printCapacity(PFAone);
}
