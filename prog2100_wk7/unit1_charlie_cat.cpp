//Note: Heap (Sometimes also known as the free store).
//Use may use the dot(.) operator to access properties of objects created
//locally. To access objects declared on the heap you first need to dereference
//a pointer to that object and then call the dot operator on the object pointed
//to by that pointer.
//
//To access getAge on the heap, you could write (*pCharlie).getAge();
//C++ uses a shorthand operator for indirect access: the points-to operator(->).


#include <iostream>
using namespace std;

class Cat{
private:
int itsAge;
public:
Cat(){itsAge=12;}//constructor
~Cat(){}//destructor
int getAge() const{return itsAge;}
void setAge(int age){itsAge = age;}
};//end class Cat;

int main() {
Cat otherCat = Cat();//local instanciation notice use of parenthesis
cout << "Othercat is " << otherCat.getAge();

Cat *pCharlie = new Cat;//note no parenthesis - new puts it into heap
cout << "Charlie is " << (*pCharlie).getAge();
//cout << "Charlie is " << pCharlie->getAge();//error Charlie on heap

pCharlie->setAge(13);
cout << "Charlie is " << pCharlie->getAge();
delete pCharlie;

return 0;
}//end main
