#pragma once
//FileName : ordlist.h 
//Author:Daniel Kelley
//Modifications:Daniel Kelley
//Date 10/21/2019
//Project OrdList 
//
//				BE SURE TO DOCUMENT THIS CLASS FULLY!!! 
//Purpose: This file contains the specification for an expandable/contractable ordered list(ascending)
//   class. It inherits basic properties and actions from the abstract base ListClass. Duplicates are
//	 not allowed to be inserted into the list.
//
//Assumptions: That my code isn't shit
//			   That the user supplies a working implementation of ItemType
//					And that the struct will contain some integral variable named 'key'
//
//Exception Handling: NextPosition cannot set CurrPos past (length - 1)	//the bounds of inserted elements in the list
//					  Duplicates are overwritten
//
//
//                         SUMMARY OF METHODS
/*
OrdListClass();														//initialized OrdListClass
OrdListClass(const OrdListClass &orig);								//to create a copy of an existing class object
~OrdListClass();													//to destroy the existing class object
void NextPosition();												//sets currPos to next element in list
bool IsFull() const;												//returns true if list is full, false otherwise
bool Find(KeyType key);												//finds position of key within the OrdList.
void Insert(ItemType target);										//inserts target into OrdList at position specified by PDM currPos. 
void Delete();														//deletes list entry specified by currPos
void Clear();														//clears the List
void Print(int base = 10);											//Allows users to print the contents of their struct in an appropriate manner
virtual bool operator==(const OrdListClass& rtOp) const;			//returns true if keys are equal false otherwise
virtual bool operator!=(const OrdListClass& rtOp) const;			//returns true if keys are not equal false otherwise
virtual OrdListClass operator*(const OrdListClass& rtOp) const;		//joins/intersects the contents of rtOp with that ListClass
virtual OrdListClass operator+(const OrdListClass& rtOp) const;		//Merges lists-- if duplicates encountered only 1 ends up in list, the other is discarded
virtual void operator=(const OrdListClass& orig);					//assigns orig to applying class object
virtual void Expand();												//creates a new list twice the size of the original and copies the
virtual void Contract();											//creates a new list half the size of the original and copies the
virtual bool NoRoom();												//returns true if list has no empty locations, false otherwise
*/


//  To provide the ability to order the list, the following functions must be 
//  OVERIDDEN 
/*
bool IsFull() const;
bool Find(KeyType key);
void Insert(ItemType target);
*/


// The following public methods have been added to the class to provide additional 
// functionality
/*
void Delete();
void Print(int base = 10);
*/


//The following methods are also implemented as required by the Abstract Base Class
/*
virtual void Expand();
virtual void Contract();
virtual bool NoRoom();
*/


// The following operators have been overloaded to provided added functionality
/*
virtual bool operator==(const OrdListClass& rtOp) const;
virtual bool operator!=(const OrdListClass& rtOp) const;
virtual OrdListClass operator*(const OrdListClass& rtOp) const;
virtual OrdListClass operator+(const OrdListClass& rtOp) const;
virtual void operator=(const OrdListClass& orig);
*/


// The following protected methods have been added to allow expansion and contraction.
/*
virtual void Expand();
virtual void Contract();
*/


#include <iostream>
#include <exception>

#include "ABCListClass.h"
#include "baseConversion.h"

// Class Declarations 
class OrdListClass : public ListClass			//uses ListClass as template for further derivations
{

public: 
	OrdListClass(); 
		//Purpose: initialized OrdListClass
		//Pre: List has been instantiated
		//Post: List has been initialized

	OrdListClass(const OrdListClass &orig);
		//Purpose: to create a copy of an existing class object
		//Pre: a class object exists
		//Post: a copy of the class object exists too

	~OrdListClass();
		//Purpose: to destroy the existing class object
		//Pre: the class object exists
		//Post: the class object no longer exists

	void Delete();
	//deletes list entry specified by currPos, 
	//Pre: currPos contains the location of the element to be deleted;
	//     where (O <= position < length) 
	//Post: element has been deleted from list. If deletion results in a the list
	//		being too small, list will contract

	void Print(int base = 10);
	//Allows users to print the contents of their struct in an appropriate manner
	//Pre: List exists
	//Post: The contents of the list(ItemType) has been printed.

	//OVERRIDDEN METHODS

	void NextPosition();
	//sets currPos to next element in list
	//Pre: List exists 
	//Post: currPos is set to next element in list 

	bool IsFull() const;
		// returns true if list is full, false otherwise
		// overridden to ensure functionality of existing client code, list now expands)
		//Pre: list has been instantiated
		//Post: false has been returned


	bool EndOfList() const;
	//returns true if currPos specifies end of List. 
	//Pre: List exists. 
	//Post: if currPos = length - 1, true is returned, otherwise false 


	bool Find(/* in */KeyType key);		// key to search for
		//finds position of key within the OrdList. 
		//Pre: target contains a keyType value to search OrdList for. 
		//Post: If target is found within the OrdList, true is returned and 
		//      currPos is set to the elements location in the list. If target is 
		//      not found, false is returned and currPos is set to the 
		//      location where the element would have appeared had it been in the 
		//      List. 



	void Insert(/* in */ ItemType target);				//target to insert
		//inserts target into OrdList at position specified by PDM currPos. 
		//Pre: currPos contains location at which to insert new element; 
		//			where (0 <= currPos <= length) 
		//Post: target has been inserted into the OrdList at the location specified by currPos. 
		//		if list was full prior to insertion, list will expand
		

	void Clear();
		//clears the List 
		//Pre: List exists. 
		//Post: List has been cleared and if necessary resized to INITIAL_SIZE.

		//NOTE: This is the implementation of the PVF in the Base ListCLass

		//overloaded operators
	virtual bool operator==(/* in */const OrdListClass& rtOp) const;			//right operand for operator
		//tests the contents of rtOp with that of applying ListClass for equality
		//returns true if keys are equal false otherwise
	
	virtual bool operator!=(/* in */const OrdListClass& rtOp) const;			//right operand for operator
		//tests the contents of rtOp with that of applying ListClass for equality
		//returns true if keys are not equal false otherwise


	virtual OrdListClass operator*(/* in */const OrdListClass& rtOp) const;		//right operand for operator
		//joins/intersects the contents of rtOp with that ListClass
		//--only keys appearing in both will appear in the resultant class
	
	virtual OrdListClass operator+(/* in */const OrdListClass& rtOp) const;	     //right operand for operator
		//Merges lists-- if duplicates encountered only 1 ends up in list, the other is discarded


	virtual void operator=(/* in */const OrdListClass& orig);					//original list
		//assigns orig to applying class object


protected: 
	virtual void Expand();
		// creates a new list twice the size of the original and copies the
		//info from the smaller list to the larger one.
		//Pre : List is full and needs to be enlarged
		//Post: List size has been increased by 50% 
		
	virtual void Contract();
		// creates a new list half the size of the original and copies the
		//info from the old list to the new one.
		//Pre : List has less than 33% occupancy
		//Post: List size has been reduced in size by 1/3
	
	virtual bool NoRoom();
		//	--returns true if list has no empty locations, false otherwise
		//Pre : List exists
		//Post: true is returned if list has no available locations, false otherwise


private:

};//end OrdListClass