#pragma once

#include"ItemType.h"

struct node {

	//Some item that was inserted:
	ItemType item;

	//Next item in the list:
	node* next;

};