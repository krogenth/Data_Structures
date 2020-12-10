/*
Name: Jordan Barrett

Date:10/28/2019

Professor: Professor Strohmaier

Purpose: To create a circular link list that holds items of a specified key identifier

File name: QueueClass.h

Inputs: N/A

Outputs: N/A

Assumptions: That items put into the queue will have an id or key.

Error Checking: Makes sure multiple times throughout the class that when working with the list (deleting an item 
for example), that the list is not empty

Summary of Methods:

QueueClass(); -- Default constructor, initializes the pdms to default values

~QueueClass(); -- Deconstructor, deletes the list (calls Clear())

QueueClass(const QueueClass& otherQueue); -- Copy constructor, copies the contents of one queue into the current one

void Clear(); -- Deletes all items in the list

bool IsEmpty(); -- Returns true if size is 0, else returns false

void EnQueue(Item newItem); -- Inserts an item into the list at the end

void DeQueue(); -- Deletes the item at the front of the list

node* Allocate(); -- Allocates new space for some new pointer

Item Retrieve(); -- Returns the item at the front of the queue
*/

#ifndef QUEUECLASS
#define QUEUECLASS
#include<iostream>
#include"ItemType.h"
#include"Node.h"
#include"Exceptions.h"

class QueueClass
{
public:
	/*
	Pre: N/A
	Post: Pdms will be initialized
	Purpose: Initializes all pdms to some default values
	*/
	QueueClass();

	/*
	Pre: N/A
	Post: The list of some object will be deleted
	Purpose: Deletes the list of some object to not leave memory leaks
	*/
	~QueueClass();

	/*
	Pre: N/A
	Post: Copies some list into the current one
	Purpose: Copies the contents of some list into the current list
	*/
	QueueClass(/*IN*/const QueueClass& otherQueue);

	/*
	Pre: N/A
	Post: The list will be deleted
	Purpose: Deletes all items in the queue
	*/
	void Clear();

	/*
	Pre: N/A
	Post: Returns true if size is 0, else returns false
	Purpose: Determines if the list is empty
	*/
	bool IsEmpty();

	/*
	Pre: Some item with a key must be passed to it
	Post: The item will be inserted at the end of the list
	Purpose: Inserts an item at the end of the list
	*/
	void EnQueue(/*IN*/ItemType newCall);

	/*
	Pre: N/A
	Post: Deletes the front item in the list
	Purpose: Deletes whatever item is at the front of the list or throws
	an exception if the list is empty
	*/
	void DeQueue();

	/*
	Pre: N/A
	Post: Returns the item at the front of the list or throws an exception
	Purpose: Either returns the item at the front of the queue or,
	if the queue is empty, throws an exception so the user knows that nothing
	could be retrieved
	*/
	ItemType Retrieve();

private:
	node* tail = nullptr;	//Tail or end of the list
	int size;	//Total size of the list

	/*
	Pre: N/A
	Post: Returns new allocated space
	Purpose: Returns new allocated space for some pointer
	*/
	node* Allocate();
};

#endif