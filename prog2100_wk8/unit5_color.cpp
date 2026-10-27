//Using Color in you C++ Console Applications Demo

#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void Col(int);

int main() {
Col(12);
cout << "RED" << std::endl;
Col(7);
cout << "WHITE" << std::endl;
Col(3);
cout << "BLUE" << std::endl;
_getch();
return 0;
}

void Col(int c)
{
HANDLE hConsole;
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, c);
return;
}
