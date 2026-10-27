#include <iostream>
#include <conio.h> //_getch for pause
#include <cstdlib>
#include <string>
using namespace std;

class Weapon{
public:
Weapon(){};//default constructor
double calcSwordDamage(){
return 5 + rand() % 20; //scaled to 5-20 dmg
}//end method
double calcFlameDamage(){
return 10 + rand() % 15;//scaled to 10-15 dmg
}//end method
};//end class Weapon

class CharacterClass{
private:
char charType;//k=knight, d=dragon
double health;
int dex;
int stren;
int armor;
Weapon weap;// aggregate member

public:
//Constructors
CharacterClass(){};//default constructor
CharacterClass(char ct,double hlth,int dx,int st,int arm)//knight
:charType(ct),health(hlth),dex(dx),stren(st),armor(arm)//initialization section
{}//empty body init section used instead
CharacterClass(char ct,double hlth,int dx,int st)//dragon
:charType(ct),health(hlth),dex(dx),stren(st)//initialization section
{}//empty body used instead

//Property Procedures
void setHealth(double health){this->health = health;}
double getHealth(){return this->health;}

//Attack, Def, Die methods
double calcDefense(){
if (charType=='k')
return dex+armor+rand()%11;//k def
else
return dex+rand()%16;//d def
}

double calcAttack(){
if (charType=='k')
return weap.calcSwordDamage()+dex+stren;//k att
else
return weap.calcFlameDamage()+dex+stren;//d att
}

string die(){
if (charType=='k')
return "Dragon won - Yea for evil!";//k died
else
return "Knight won - Hazzah for good!";//d died
}

};//end class CharacterClass

int main() {
int ran;
double defense, attack, damage;
//instance game characters - notice we did not use 'new'
CharacterClass Knight('k',300,30,20,20);
CharacterClass Dragon('d',300,20,10);

cout <<"The battle begins!"<<endl;
cout <<"Press any key to continue"<<endl;
_getch();//pause for get a character ie key press


//battle logic
do{
ran = rand()%2;//0=k 1=d
if (ran==0)//knight attacks
{
defense = Dragon.calcDefense();
attack = Knight.calcAttack();
damage = attack-defense;
if(defense>attack) //zombie test
damage=0;
Dragon.setHealth(Dragon.getHealth()-damage);
cout<<"Dragon was hit for "<<damage <<endl;
cout<<"Dragon has "<<Dragon.getHealth()<< " left" << endl;

}
else {//Dragon attacks
defense = Knight.calcDefense();
attack = Dragon.calcAttack();
damage = attack-defense;
if(defense>attack)//zombie test
damage=0;
Knight.setHealth(Knight.getHealth()-damage);
cout<<"Knight was hit for "<<damage <<endl;
cout<<"Knight has "<<Knight.getHealth()<< " left" << endl;
}


}while (Knight.getHealth()>0 && Dragon.getHealth()>0);

if(Knight.getHealth()<=0)//zombie test
cout<<Knight.die()<<endl;
else
cout<<Dragon.die()<<endl;

cout << "Battle Ended"<<endl;

return 0;
}//end main
