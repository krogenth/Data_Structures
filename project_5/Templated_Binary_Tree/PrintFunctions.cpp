//Daniel Kelley
//File: PrintFunctions.cpp
//Date: 12/19/2019
//Purpose: To implement some silly function pointer printing functionality in BinaryTree

#include <iostream>

#include "PrintFunctions.h"
#include "ItemType.h"
#include "BinaryTree.h"

void PrintToScreen(BinaryTree<ItemType> tree) {

	tree.FirstPosition();

	while (!tree.EndofList()) {

		std::cout << tree.Retrieve().key << '\t';
		tree.NextPosition();

	}

	std::cout << tree.Retrieve().key << '\n';

}

void PrintToScreenReverse(BinaryTree<ItemType> tree) {

	tree.LastPosition();

	while (!tree.StartOfList()) {

		std::cout << tree.Retrieve().key << '\t';
		tree.PrevPosition();

	}

	std::cout << tree.Retrieve().key << '\n';

}

void PrintToFile(BinaryTree<ItemType> tree) {

	tree.FirstPosition();

	while (!tree.EndofList()) {

		std::cout << tree.Retrieve().key << '\t';
		tree.NextPosition();

	}

	std::cout << tree.Retrieve().key << '\n';

}

void PrintAsExists(BinaryTree<ItemType> tree) {



}