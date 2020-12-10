//Daniel Kelley
//File: Node.h
//Date: 12/3/2019
//Purpose: To define the node structure used in the OrdListClass
#pragma once

#include "ItemType.h"

template<typename T>
struct node {

	T item;
	node<T> *prev = nullptr;

};