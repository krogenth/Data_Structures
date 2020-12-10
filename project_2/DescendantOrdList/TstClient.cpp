//Daniel Kelley
//File: TstClient.cpp
//Date: 10/21/2019
//Purpose: To test and ensure the OrdList works properly

#include <iostream>

#include "OrdList.h"

//BE SURE TO DOCUMENT THE TEST CLIENT FULLY, Design tests for each method independently , then integration test
int main()
{
		
	//Testing constructor
	OrdListClass myList, yourList, theirList; 
	ItemType item;

	std::cout << "myList\tGetlength(): " << myList.GetLength() << "\tIsEmpty(): " << myList.IsEmpty() << "\tIsFull(): " << myList.IsFull() << "\n";
	std::cout << "yourList\tGetlength(): " << yourList.GetLength() << "\tIsEmpty(): " << yourList.IsEmpty() << "\tIsFull(): " << yourList.IsFull() << "\n";
	std::cout << "theirList\tGetlength(): " << theirList.GetLength() << "\tIsEmpty(): " << theirList.IsEmpty() << "\tIsFull(): " << theirList.IsFull() << "\n\n";

	//Insert items into myList
	for (int i = 0; i < 8; i++) {

		item.key = i;
		myList.Insert(item);

	}

	//Insert items into yourList
	for (int i = 0; i < 10; i++) {

		item.key = i;
		yourList.Insert(item);

	}

	//Check if the class keys are equal: they should not be
	if (myList == yourList)
		std::cout << "They are equal\n\n";

	//Check if the class keys are not equal: they should not be
	if (yourList != theirList)
		std::cout << "They are not equal\n\n";

	//Output the contents of myList and yourList
	std::cout << "myList:\n";
	myList.Print();
	std::cout << "\n\nyourList:\n";
	yourList.Print();
	std::cout << "\n\n";

	//Intersect myList and yourList into theirList, then output
	std::cout << "Intersecting myList and yourList into theirList:\n";
	theirList = myList * yourList;
	std::cout << "theirList\tGetlength(): " << theirList.GetLength() << "\tIsEmpty(): " << theirList.IsEmpty() << "\tIsFull(): " << theirList.IsFull() << "\n";
	theirList.Print();
	std::cout << "\n\n";

	//Clear theirList to ensure clear works properly
	std::cout << "Clearing theirList:\n";
	theirList.Clear();
	std::cout << "theirList\tGetlength(): " << theirList.GetLength() << "\tIsEmpty(): " << theirList.IsEmpty() << "\tIsFull(): " << theirList.IsFull() << "\n";
	theirList.Print();
	std::cout << "\n\n";

	//Merge myList and yourList into theirList, then output
	std::cout << "Merging myList and yourList into theirList:\n";
	theirList = myList + yourList;
	std::cout << "theirList\tGetlength(): " << theirList.GetLength() << "\tIsEmpty(): " << theirList.IsEmpty() << "\tIsFull(): " << theirList.IsFull() << "\n";
	theirList.Print();
	std::cout << "\n\n";

	//Go to first position, then begin deleting each and every element
	std::cout << "Deleting sequentially from theirList:\n";
	theirList.FirstPosition();
	for (;theirList.GetLength() > 0;) {

		theirList.Delete();
		std::cout << "theirList\tGetlength(): " << theirList.GetLength() << "\tIsEmpty(): " << theirList.IsEmpty() << "\tIsFull(): " << theirList.IsFull() << "\n";
		theirList.Print();
		std::cout << '\n';

	}

	//Merge myList and yourList into theirList, then output
	std::cout << "\nMerging myList and yourList into theirList:\n";
	theirList = myList + yourList;
	std::cout << "theirList\tGetlength(): " << theirList.GetLength() << "\tIsEmpty(): " << theirList.IsEmpty() << "\tIsFull(): " << theirList.IsFull() << "\n";
	theirList.Print();
	std::cout << "\n\n";

	//Go to first position, then begin deleting elements from 4 to 9
	std::cout << "Attempting to delete so values from theirList:\n";
	theirList.FirstPosition();

	for (int i = 4; i < 10; i++) {

		if (theirList.Find(i)) {

			theirList.Delete();
			std::cout << "theirList\tGetlength(): " << theirList.GetLength() << "\tIsEmpty(): " << theirList.IsEmpty() << "\tIsFull(): " << theirList.IsFull() << "\n";
			theirList.Print();
			std::cout << '\n';

		}

	}

	std::cout << "Press enter to continue...\n";
	std::cin.get();

	return EXIT_SUCCESS;

}


