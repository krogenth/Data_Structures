#pragma once
/*
Name: Daniel Kelley
Date:  11/4/2019

Purpose: To handle all functionality of a sheep on the field
Assumptions: an x and y position was eventually passed to the object

Error Handling: position boundaries with respect to the field dimensions

Summary of Functions:
Stack();											//creates a default Stack object
Stack(const Stack &stack_);							//creates a copied Stack object
~Stack();											//to kill a living Stack object
void Clear();										//to remove all elements within the Stack object
bool Top(ItemType &item_);							//returns the current top of the Stack object
void Pop();											//removes the current top of the Stack object
void Push(ItemType item_);							//shoves a new item to the top of the Stak object
bool IsEmpty() const;								//checks if the Stack object has no elements
virtual void operator=(const Stack& orig);			//
virtual bool operator==(const Stack& rtOp) const;	//
virtual bool operator!=(const Stack& rtOp) const;	//
node * Allocate();									//allocates a new heap memory block for a node
*/

#include <fstream>
#include <iostream>

size_t SIZE_LIMIT = 4;

typedef size_t KeyType;

//contains all necessary data for items
struct ItemType {

	KeyType key;
	//Other shit

};


struct node {

	node *next = nullptr;
	ItemType item;

};

class Stack {

public:
	//Purpose:	creates a default Stack object
	//Pre:		nothing
	//Post:		a Stack object is born
	Stack();

	//Purpose:	creates a copied Stack object
	//Pre:		nothing
	//Post:		a Stack object is copied
	Stack(const Stack &stack_);

	//Purpose:	to kill a living Stack object
	//Pre:		the Stack object exists
	//Post:		the Stack object no longer exists
	~Stack();

	//Purpose:	to remove all elements within the Stack object
	//Pre:		the Stack object exists
	//Post:		the Stack object is empty
	void Clear();

	//Purpose:	returns the current top of the Stack object
	//Pre:		the Stack object exists
	//Post:		returns true, and item is written with top of Stack object data, if the Stack object is not empty, false otherwise
	bool Top(ItemType &item_);

	//Purpose:	removes the current top of the Stack object
	//Pre:		the Stack object exists
	//Post:		a new top of the Stack object is revealed
	void Pop();

	//Purpose:	shoves a new item to the top of the Stak object
	//Pre:		the Stack object exists
	//Post:		a new current top of the Stack object is revealed(or not, it only accepts 4 elements for whatever reason)
	void Push(ItemType item_);

	//Purpose:	checks if the Stack object has no elements
	//Pre:		the Stack object exists
	//Post:		returns true if empty, false otherwise
	bool IsEmpty() const;

	virtual void operator=(const Stack& orig);

	virtual bool operator==(const Stack& rtOp) const;

	virtual bool operator!=(const Stack& rtOp) const;

private:
	//Purpose:	allocates a new heap memory block for a node
	//Pre:		the Stack object exists
	//Post:		a new heap memory block is allocated for a node(hopefully)
	node * Allocate();

	node *head = nullptr;
	size_t size = 0;

};
