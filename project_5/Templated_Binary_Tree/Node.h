//Daniel Kelley
//File: Node.h
//Date: 12/19/2019
//Purpose: To define the node structure used in the BinaryTree

#pragma once
#include "ItemType.h"

template<class T>
struct node {

	T item;
	node *left = nullptr;
	node *right = nullptr;

};