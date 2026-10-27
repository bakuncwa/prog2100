#include <iostream>
#include <sstream>
using namespace std;
class ComplexNumber
{
private:
double real;
double imaginary;
public:
ComplexNumber()//default
:real(), imaginary(){}
ComplexNumber(double real, double imaginary)//const with args
:real(real), imaginary(imaginary){}
ComplexNumber(string s)//const with arg for string like "a+bi"
{
//parse routine goes here
this->real = 3; //hard coded stub for testing
this->imaginary = 8; //hard coded stub for testing
}
ComplexNumber operator+ (ComplexNumber &rightObj)
{
return ComplexNumber(this->real + rightObj.real,
this->imaginary + rightObj.imaginary);
}
//code other operators here
void print()// dont do it this way - dirty ie touches the UI
{
cout << this->real << " + " << this->imaginary << "i" << endl;
}
string toString()//clean
{
stringstream strStream;
string x, y;
//next 5 lines used to do conversions for double to str
strStream << this->real;//place prop in stream
strStream >> x;//rec it back converted to a string
strStream.clear();
strStream << this->imaginary;
strStream >> y;
//return a string representing the
//current value of this obj in a+bi format
return (x + "+" + y + "i");
}//end toString
friend void operator>> (istream &input, ComplexNumber &num);
friend ostream& operator<<(ostream &output, ComplexNumber &num);
};//end class ComplexNumber
//implementation of friend function
void operator>> (istream &input, ComplexNumber &num)
{
string str;
getline(input, str);//assign input to string var
num = ComplexNumber(str);//call to string constructor for "a+bi"
}
ostream& operator<<(ostream &output, ComplexNumber &num)
{
output << num.real << " + " << num.imaginary << "i";
return output; //returns an ostream obj
}
int main() {
cout << "test default constructor and print function"<< endl;
ComplexNumber cn1;//instances using default constructor
cn1.print(); //use of print - dirty
cout << "test constructor with arguments and print function"<< endl;
ComplexNumber cn2(4,8);// instances using constructor with arguments
cout << cn2.toString() << endl;//use of toString method
cout << "test string constructor and print function"<< endl;//note stubbed to 8 and 3
ComplexNumber cn3("9+9i");//instances using string constructor
cout << cn2.toString() << endl;//use of toString method
cout << "Test of + operator and toString method" << endl;
ComplexNumber cn4 = cn2 + cn3;
cout << cn2.toString() << " + " << cn3.toString() << " = " << cn4.toString() << endl;
cout << "Test of input operator" << endl;
//note: have the overloaded input call a validation method and
//execute a cin.fail if the string is not valid - loop and ask again
ComplexNumber cn5;
cout << "Enter a Complex Number in a+bi format - note stubbed" << endl;
cin >> cn5;
cout << cn5.toString() << endl;
cout << "Test complete" << endl;
return 0;
}
