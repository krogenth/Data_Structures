//Daniel Kelley
//File: TstClient.cpp
//Date: 10/21/2019
//Purpose: Test the ABCListClass.obj file to determine what is wrong

#include "ABCListClass.h"
#include <iostream>

//BE SURE TO DOCUMENT THE TEST CLIENT FULLY, Design tests for each method independently , then integration test
void main()
{

	//Testing constructor
	ListClass myList;
	std::cout << "Classes instantiated successfully\n";

	//Grab base parameters, see what everything is
	std::cout << "getLength(): " << myList.GetLength() << "\tisFull(): " << myList.IsFull() << "\tisEmpty(): " << myList.IsEmpty() << "\tendOfList(): " << myList.EndOfList() << '\n';
	std::cout << "retrieve(): " << myList.Retrieve().key << "\n\n";

	//Attempt to clear, see what it does: successful
	std::cout << "Clearing: \n\n";
	myList.Clear();

	//Grab everything after attempting to clear, see what it does
	std::cout << "getLength(): " << myList.GetLength() << "\tisFull(): " << myList.IsFull() << "\tisEmpty(): " << myList.IsEmpty() << "\tendOfList(): " << myList.EndOfList() << '\n';
	std::cout << "retrieve(): " << myList.Retrieve().key << "\n\n";

	ItemType item;

	//If you call NextPosition without calling LastPosition, positioning will be off by 1
	/*for (int i = 0; i < 4; i++) {

		std::cout << "retrieve(): " << myList.Retrieve().key << '\n';

		myList.NextPosition();
		item.key = i;
		myList.Insert(item);

		std::cout << "getLength(): " << myList.GetLength() << "\tisFull(): " << myList.IsFull() << "\tisEmpty(): " << myList.IsEmpty() << "\tendOfList(): " << myList.EndOfList() << '\n';
		std::cout << "retrieve(): " << myList.Retrieve().key << "\n\n";

	}*/

	//Begin Inserting elements into the ABCListClass
	myList.LastPosition();
	std::cout << "Inserting Test #1: \n";

	for (int i = 0; i < 4; i++) {

		//Grab the current key
		std::cout << "retrieve(): " << myList.Retrieve().key << '\n';

		//Set to next position, and Insert new ItemType
		myList.NextPosition();
		item.key = i;
		myList.Insert(item);

		//Grab updated information from ABCListClass object
		std::cout << "getLength(): " << myList.GetLength() << "\tisFull(): " << myList.IsFull() << "\tisEmpty(): " << myList.IsEmpty() << "\tendOfList(): " << myList.EndOfList() << '\n';
		std::cout << "retrieve(): " << myList.Retrieve().key << "\n\n";

	}

	//Begin going through the list to ensure everything was stored correctly
	myList.FirstPosition();
	std::cout << "\nChecking List: \n";

	for (int i = 0; i < 4; i++) {

		std::cout << "i: " << i << "\tretrieve(): " << myList.Retrieve().key << '\n';

		myList.NextPosition();

	}

	//Attempt to clear the list again: successful
	std::cout << "\nClearing: \n\n";
	myList.Clear();

	myList.LastPosition();
	std::cout << "Inserting Reverse Test #1: \n";

	for (int i = 3; i >= 0; i--) {

		//Grab the current key
		std::cout << "retrieve(): " << myList.Retrieve().key << '\n';

		//Set to next position, and Insert new ItemType
		myList.NextPosition();
		item.key = i;
		myList.Insert(item);

		//Grab updated information from ABCListClass object
		std::cout << "getLength(): " << myList.GetLength() << "\tisFull(): " << myList.IsFull() << "\tisEmpty(): " << myList.IsEmpty() << "\tendOfList(): " << myList.EndOfList() << '\n';
		std::cout << "retrieve(): " << myList.Retrieve().key << "\n\n";

	}

	//Begin going through the list to ensure everything was stored correctly
	myList.FirstPosition();
	std::cout << "\nChecking Reversed List: \n";
	for (int i = 0; i < 4; i++) {

		std::cout << i << '\t';

		if (myList.Find(i)) {

			std::cout << "getLength(): " << myList.GetLength() << "\tisFull(): " << myList.IsFull() << "\tisEmpty(): " << myList.IsEmpty() << "\tendOfList(): " << myList.EndOfList() << '\n';
			std::cout << "retrieve(): " << myList.Retrieve().key << '\n';

		}

		std::cout << "\n";

	}

	//Attempt to clear the list again: successful
	std::cout << "\nClearing: \n\n";
	myList.Clear();

	//Start Inserting data again: this will go out of bounds of the list, which is limited to 4 elements
	myList.FirstPosition();
	std::cout << "Inserting Test #2: \n";
	myList.LastPosition();

	for (int i = 0; i < 20; i++) {

		//Grab the current key
		std::cout << i << "\tretrieve(): " << myList.Retrieve().key << '\n';

		//Set to next position, and Insert new ItemType
		myList.NextPosition();
		item.key = i;
		myList.Insert(item);

		//Size never changes, list does not expand/contract
		std::cout << "getLength(): " << myList.GetLength() << "\tisFull(): " << myList.IsFull() << "\tisEmpty(): " << myList.IsEmpty() << "\tendOfList(): " << myList.EndOfList() << '\n';
		std::cout << "retrieve(): " << myList.Retrieve().key << "\n\n";

	}

	//See what happens when you go past lastPosition
	myList.LastPosition();
	myList.NextPosition();

	std::cout << "\nTest what exists beyond the bounds of the list: \n";
	std::cout << "getLength(): " << myList.GetLength() << "\tisFull(): " << myList.IsFull() << "\tisEmpty(): " << myList.IsEmpty() << "\tendOfList(): " << myList.EndOfList() << '\n';
	std::cout << "retrieve(): " << myList.Retrieve().key << "\n\n\n";

	//Attempt to find all values within the list: this works perfectly fine
	std::cout << "Attempting to find values 0 through 20...: \n";
	for (int i = 0; i < 20; i++) {

		std::cout << i << '\t';

		if (myList.Find(i)) {

			std::cout << "getLength(): " << myList.GetLength() << "\tisFull(): " << myList.IsFull() << "\tisEmpty(): " << myList.IsEmpty() << "\tendOfList(): " << myList.EndOfList() << '\n';
			std::cout << "retrieve(): " << myList.Retrieve().key << '\n';

		}

		std::cout << "\n";

	}

	std::cout << "\n";

	//Attempt to remove ItemType's from the list
	//If NexPosition was called before Insert, but LastPosition was not called first
	//Then Find will be unable to find N elements at the end(N = number of NextPosition called before Insert)
	std::cout << "Removing: \n";

	for (int i = 0; i < 20; i++) {

		std::cout << i << '\t';

		if (myList.Find(i)) {

			//Grab the current key
			std::cout << "retrieve(): " << myList.Retrieve().key << '\n';

			//Delete the key we found
			myList.Delete(myList.Retrieve().key);

			std::cout << "getLength(): " << myList.GetLength() << "\tisFull(): " << myList.IsFull() << "\tisEmpty(): " << myList.IsEmpty() << "\tendOfList(): " << myList.EndOfList() << '\n';
			std::cout << "retrieve(): " << myList.Retrieve().key << '\n';

		}

		std::cout << "\n";

	}

	std::cout << "\nPress enter to crash...\n";
	std::cin.get();

	//Attempt to clear and see what happens: hint, it breaks to a heap corruption error because it never expands
	std::cout << "Clearing: \n";
	std::cout << "getLength(): " << myList.GetLength() << "\tisFull(): " << myList.IsFull() << "\tisEmpty(): " << myList.IsEmpty() << "\tendOfList(): " << myList.EndOfList() << '\n';
	myList.Clear();
	std::cout << "getLength(): " << myList.GetLength() << "\tisFull(): " << myList.IsFull() << "\tisEmpty(): " << myList.IsEmpty() << "\tendOfList(): " << myList.EndOfList() << '\n';

	std::cin.get();

}