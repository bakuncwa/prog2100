//Timers in C++

#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <ratio>
#include <ctime>
#include <cstdlib>
using namespace std;

void threadSleepExample();
void timerExample();//there are other timers in chrono class too
void ctimeClockExample(); //common method pre 11

int main()
{
//threadSleepExample();
//timerExample();
ctimeClockExample();

}//end main


void threadSleepExample(){
cout << "Thread Sleep Example - No Timer" << endl;
while(true)//always true endless loop
{
this_thread::sleep_for(1s);
cout << "tick" << endl;
}

}//end method

void timerExample(){
cout << "Thread Sleep Example - With Timer" << endl;
chrono::seconds interval( 1 ) ; // 1 second
for( int i = 0 ; i < 10 ; ++i )
{
cout << "tick!\n" << flush ;
this_thread::sleep_for( interval ) ;
}
}//end method

void ctimeClockExample(){ //source www.cplusplus.com
double counter = 0;
double pauseInterval = 1;
clock_t startTime = clock();
clock_t previousTime = startTime;


while(true){
startTime = clock();
counter += startTime - previousTime;
previousTime = startTime;
if(counter>pauseInterval * CLOCKS_PER_SEC)
{
counter -= pauseInterval * CLOCKS_PER_SEC;
cout << "tick" << endl;
}
}

} //end method
