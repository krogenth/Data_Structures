//Daniel Kelley
//File: Source.cpp
//Date: 12/19/2019
//Purpose: To test the templated BinaryTree's functionality

#include <iostream>

#include "PrintFunctions.h"
#include "BinaryTree.h"

size_t main() {


	BinaryTree<ItemType> check1, check2;
	ItemType item;

	for (size_t i = 0; i < 200; i++) {

		item.key = i;
		check1.Insert(item);
		check2.Insert(item);
		check1.PrintScreen(PrintToScreen);

	}

	if (check1 == check2)
		std::cout << "They are equivalent!\n";
	else
		std::cout << "Oh no, they aren't the same. :'(\n";

	std::cout << "Check1 has " << check1.ReturnLength() << " nodes in it.\n";

	for (int32_t i = 199; i >= 0; i--) {

		if(check1.Find(i))
			check1.Delete();
		check1.PrintScreen(PrintToScreen);

	}

	std::cout << "Check2, Printing reverse:\n";
	check2.PrintReverse(PrintToScreenReverse);
	check2.PrintFile(PrintToFile);

	if (check2.Find(15))
		std::cout << "Found " << check2.Retrieve().key << " in check2.\n";

	check2.Clear();

	check2.PrintScreen(PrintToScreen);

	std::cin.get();

	return 0;

}