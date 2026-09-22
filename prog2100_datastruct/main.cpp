 // Header for NumberList class
// Created by W0068332 on 9/5/2020.

#ifndef LINKEDLISTDEMO_NUMBERLIST_H
#define LINKEDLISTDEMO_NUMBERLIST_H

class NumberList {
private:
struct ListNode // holds doubles
{
double value;
struct ListNode *next;//pointer to next node
};

ListNode *head;//points to first node in the structure

public:
NumberList(){head=0;}
//list functions
void appendNode(double);
void insertNode(double);
void deleteNode(double);
void displayList()const;
};

#endif //LINKEDLISTDEMO_NUMBERLIST_H



// Implementation of NumberList – Numberlist.cpp
// Created by W0068332 on 9/5/2020.
// NodePtr points to where you are in the list

#include "NumberList.h"
#include <iostream>
using namespace std;

//Traverse and display values in list
void NumberList::displayList() const {
ListNode *nodePtr;//declare node pointer
nodePtr = head; //move node pointer to the head of the list

while(nodePtr)//while it points to a node - then traverse
{
cout << nodePtr->value<<endl;
nodePtr = nodePtr->next; //set nodePtr to the next struct on the list
}
}//end displayList



//Steps for APPENDING a node to the list:
//Create a new node and Store data into the new node
//If there are no nodes in the list, make the new node the first node.
//Else
//Traverse the list to find the last node.
//Add the node to the end of the list (i.e. append)

void NumberList::appendNode(double num) {
ListNode *newNode;//points to new node
ListNode *nodePtr;//for the traverse

//allocate a new node and store data in it
newNode = new ListNode;
newNode->value = num;
newNode->next = 0;

//If there are no nodes in list already make newNode the first node ie the head node
if (!head) //if head var is pointing to NULL
head = newNode;
else { //traverse for append ie look for node with NULL next pointer
nodePtr = head;
while (nodePtr->next) {
nodePtr = nodePtr->next;
}
nodePtr->next = newNode;//insert newNode as last node
}
}//end appendNode

//Steps for INSERTING a node to the list:
//Create and store data to a new node
//If there are no nodes in the list make the new node the first node.
//Else (its not the first node)
//Find the first node whose value is greater than or equal to the new nodes value,
//or you reach the end of the list.
//Insert the new node before the found node, or insert at the end of the list

void NumberList::insertNode(double num) {
ListNode *newNode;
ListNode *nodePtr;
ListNode *previousNode = 0;

//allocate a new node and store data in it
newNode = new ListNode;
newNode->value = num;

//if no nodes make newNode first in list
if (!head) {
head = newNode;
newNode->next = 0;
} else {//insert the new node
nodePtr = head; //where we are move to head
previousNode = 0;//no previous
//traverse and skip nodes whose values are less than num
while (nodePtr != 0 && nodePtr->value < num) {
previousNode = nodePtr;//where we were
nodePtr = nodePtr->next;//where we are
}
//If the new node is to be the first in the list
//insert it before all the other nodes
if (previousNode == 0) {
head = newNode;
newNode->next = nodePtr;
} else { //else insert after previous node
previousNode->next = newNode;
newNode->next = nodePtr;
}
}//end else
}//end insertNode

//Steps for DELETING a node
//Check that list is not empty and or that value exists
//Remove the node without breaking the chain
//Delete the node from memory

void NumberList::deleteNode(double num) {
ListNode *nodePtr; //used to traverse (ie where you are)
ListNode *previousNode = 0;

//if the list is empty - then do nothing
if(!head)
return;
//discover if it is the first node being deleted
if(head->value==num)
{
nodePtr=head->next;
delete head;
head=nodePtr;
}else{ //if target node being deleted is not the first
nodePtr=head;
while(nodePtr!=0 && nodePtr->value!=num)
{
previousNode = nodePtr;
nodePtr = nodePtr->next;
}
//if nodePtr is not at the end of the list, link the previous node
//to the node after nodePtr, then delete nodePtr
if(nodePtr)
{
previousNode->next=nodePtr->next;
delete nodePtr;
}
}//end else
}//end deleteNode



//Driver to test Linked List Demon NumberList – main.cpp

#include <iostream>
#include "NumberList.h"
using namespace std;

int main()
{
NumberList list;
cout << "Begin linked list demonstration"<<endl;

cout << "Test of APPEND function"<<endl;
list.appendNode(1.2); //append to begin
list.appendNode(3.4); //append to existing
list.appendNode(5.6); //append to existing
list.displayList();

cout << "Test of INSERT function"<<endl;
list.insertNode(1.0); // before first
list.insertNode(2.0); // between existing
list.insertNode(7.0); // at end
list.displayList();


cout << "Test of DELETE function"<<endl;
list.deleteNode(1.0); //del first node
list.deleteNode(2.0); //del node between nodes
list.deleteNode(7.0); //del node on end
list.displayList();
return 0;
}//end main