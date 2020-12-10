//Daniel Kelley
//File: Source.cpp
//Date: 12/3/2019
//Purpose: To test the OrdListClass's functionality

#include <iostream>

#include "Exceptions.h"
#include "ItemType.h"
#include "OrdList.h"

size_t main() {

	OrdListClass ordList, ordList1, ordList2;

	ItemType item;

	//throw a bunch of stuff into ordList1 to use
	for (size_t i = 100; i > 0; i--) {

		item.key = i;

		try {

			ordList1.Insert(item);

		}
		catch (const std::exception &e) {

			std::cout << e.what() << '\n';

		}

	}

	//throw a bunch of other stuff into ordList2 to use
	for (size_t i = 200; i > 100; i--) {

		item.key = i;

		try {

			ordList2.Insert(item);

		}
		catch (const std::exception &e) {

			std::cout << e.what() << '\n';

		}

	}

	//check to ensure IsEmpty() is working properly
	std::cout << "ordList.IsEmpty(): " << ordList.IsEmpty() << '\n';

	//check to ensure operator+ is working properly
	//operator= is used in this operation as well, so no testing is required
	std::cout << "\nCombining ordList1 and ordList2 into ordList...\n";
	ordList = ordList1 + ordList2;

	//check to ensure IsEmpty() is in fact working properly
	std::cout << "\nordList.IsEmpty(): " << ordList.IsEmpty() << '\n';

	//check to ensure Print() is working properly(and to print results from operator+ check)
	std::cout << "\nPrinting contents:\n";
	ordList.Print();

	//check to ensure operator- is working properly
	std::cout << "\nRemoving ordList1 from ordList:\n";
	ordList = ordList - ordList1;

	//check to ensure PrintReverse() is working properly(and to print results from operator- check)
	std::cout << "\nPrinting reversed contents:\n";
	ordList.PrintReverse();

	//check to ensure deleting works properly
	std::cout << "\nDeleting key '1'...\n";
	ordList.Delete(199);

	//print to prove Delete() works properly
	std::cout << "\nPrinting contents:\n";
	ordList.Print();

	//check retrieve to ensure it works properly
	std::cout << "\nRetrieving an item...\n";
	item = ordList.Retrieve(150);
	std::cout << "\n" << item.key << '\n';

	//check to ensure Clear() works properly
	std::cout << "\nClearing contents...\n";
	ordList.Clear();

	//print to prove Clear() works properly
	std::cout << "\nPrinting contents:\n";
	ordList.Print();

	//insert a key for further testing
	std::cout << "\nInserting key '1'...\n";
	item.key = 1;
	ordList.Insert(item);

	//print to prove it was inserted, for some reason
	std::cout << "\nPrinting contents:\n";
	ordList.Print();

	//check to ensure deleting with only 1 node works properly
	std::cout << "\nDeleting key '1'...\n";
	ordList.Delete(1);

	//print to prove 1 node deletion works properly
	std::cout << "\nPrinting contents:\n";
	ordList.Print();

	std::cin.get();

}