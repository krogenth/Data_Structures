//Daniel Kelley
//File: Node.h
//Date: 12/3/2019
//Purpose: To define the node structure used in the OrdListClass
#pragma once

#include "ItemType.h"


struct node {

	ItemType item;
	node *prev = nullptr;

};