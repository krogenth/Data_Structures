#pragma once

#include <string>
using namespace std;

//DEFINE KEYTYPE : necessary for ordering of class
typedef int KeyType;

struct ItemType		
{					
	KeyType key = INT_MIN;		// ID which will be used to order the class.
  //string stuff		// Other elements in the list record will subsequently appear here. 
};
