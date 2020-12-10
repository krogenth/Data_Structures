#include "QueueClass.h"

QueueClass::QueueClass()
{
	//Initialiazes tail to be null:
	tail = nullptr;

	//Initialiazes size to 0:
	size = 0;
}

QueueClass::~QueueClass()
{
	//Calls clear to deconstruct the list:
	Clear();
}

QueueClass::QueueClass(/*IN*/const QueueClass& otherQueue)
{
	//As long as the other queue isn't empty:
	if (otherQueue.tail != nullptr)
	{
		//temp gets the other queues front item:
		node* temp = otherQueue.tail->next;

		//Inserts that item into the list, and repeats until it resets back to the front of the list:
		do
		{
			EnQueue(temp->item);
			temp = temp->next;
		} while (temp != otherQueue.tail->next);
	}
}

void QueueClass::Clear()
{
	//While the list isn't empty, deletes the front item:
	while (!IsEmpty())
		DeQueue();
}

bool QueueClass::IsEmpty()
{
	//If tail is pointing to nullptr:
	return(size == 0);
}

void QueueClass::EnQueue(/*IN*/ItemType newCall)
{
	//If the list is empty:
	if(IsEmpty())
	{
		//Allocates space for tail:
		tail = Allocate();

		//Inserts the item into tail:
		tail->item = newCall;

		//Loops tail around:
		tail->next = tail;

		//Increaments size:
		size++;
	}
	else
	{
		//Allocates space for temp:
		node* temp = Allocate();

		//Temp gets the new item:
		temp->item = newCall;

		//Temp points to the tail's next position:
		temp->next = tail->next;

		//Tail points to temp:
		tail->next = temp;

		//Tail gets temp:
		tail = temp;

		//Increaments size:
		size++;
	}
}

void QueueClass::DeQueue()
{
	//Throws an exception if the queue is empty:
	if (IsEmpty())
		throw EmptyException();

	//If there is more than 1 item in the list:
	if (size > 1)
	{
		//Temp gets the front of the line:
		node* temp = tail->next;

		//Tail points to temp's pointer:
		tail->next = temp->next;

		//Deletes temp:
		delete temp;

		//Decreaments size:
		size--;
	}
	//Else if there is only 1 item in the list:
	else if(size == 1)
	{
		//Deletes the tail:
		delete tail;

		size--;

		//Sets tail to nullptr:
		tail = nullptr;
	}
}

node* QueueClass::Allocate()
{
	//Returns new space to be used:
	return(new node);
}

ItemType QueueClass::Retrieve()
{
	if (IsEmpty())
		throw EmptyException();

	return(tail->next->item);
}
