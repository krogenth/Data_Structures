//*************************************************************************************************
/*									Struct Definition
Author: Daniel Kelley
Date: 12/3/2019
Project: Doubly Linked Recursive List
Filename: ItemType.h
Purpose: This file contains the struct ItemType and KeyType definitions for the OrdList Class.
*/
#pragma once

// Named Constants
const int MORE_MEMORY = 10;		// Size of the array to allocate more memory

// Type Definitions
typedef int KeyType;			// key used to order the list

typedef double MemArray[MORE_MEMORY];	// filler for record 

struct ItemType {

	KeyType key;				// The key used to find list elements.
	MemArray moreMem;


}; // End struct ItemType

//It is recommended to inherit from the ItemType, and add any required data
//OrdListClass uses the KeyType to determine what is what, so you need it
struct HusbandoType : public ItemType {

	std::string bodyType;

};

// note - increasing the size of the MORE_MEMORY constant will increase the size of each node, thereby allowing you to test the OutofMemoryException easier. 