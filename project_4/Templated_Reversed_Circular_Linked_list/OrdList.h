//*************************************************************************************************
//										SPECIFICATION FILE
/*
Date: 
Author: 
Project: Reverse-Linked Circular Recursive List
Filename: OrdList.h
Purpose: This file contains the specification for an ascending Ordered List Class. The list is implemented 
		 with a reverse-linked structure, and uses recursion to access and modify elements in the list.
		 Insert, Delete, Clear, Retrieve, Print, and PrintReverse, are wrapper methods for their
		 recursive counterparts. The class containts 8 public methods, 3 overloaded operators, 7 protected methods, 
		 copy constructor and destructor.
		 
Assumptions: 1) KeyType is defined as the a programmer defined data type and is used to order the list. 
			 2) Relational operators are defined on the primitive datatype that is typedefined as KeyType
		 	 3) ItemType is defined to contain a field named key which is defined of type KeyType
			 4) The list cannot hold elements with duplicate keys.
			 5) The list is sorted in ascending order.
			 
Exceptions Thrown: DuplicateKeyException -- Thrown when client tries to insert an already existing key.
				   OutOfMemoryException -- Thrown when client tries to insert and there is no
										  memory remaining.
				   KeyNotThereException -- Thrown when client tries to delete or retrieve a non-existent key.

//*************************************************************************************************
//										Summary of Methods
public:
	OrdListClass() -- Default Constructor. Points head to nullptr.
	~OrdListClass() -- Destructor. Calls Clear().
	OrdListClass(const OrdListClass& orig) -- Copy Constructor. Instantiates an OrdList object as a
			deep copy of orig.
	bool IsFull() -- Determines if the list is full.
	bool IsEmpty() -- Determines if the list is empty
	void Insert(ItemType newItem) -- Wrapper method for rInsert().
	void Delete(KeyType target) -- Wrapper method for rDelete().
	void Clear() -- Wrapper method for rClear().
	ItemType Retrieve(KeyType target) -- Wrapper method for rRetrieve().
	void Print() -- Wrapper method for rPrint().
	void PrintReverse() -- Wrapper method for rPrintRev().
	virtual void operator =(const OrdListClass& orig) -- Performs a deep copy of orig.
	virtual OrdListClass operator +(const OrdListClass& rtOp) -- Returns an OrdList object containing 
			the union of rtOp and the applying object. 
	virtual OrdListClass operator -(const OrdListClass& rtOp) -- Returns an OrdList object containing
			all elements in the applying object that are not in rtOp.
	
protected:
	node* Allocate() -- Allocates memory for a new node in the list.
	void rPrint(const node* trav) -- Recursively prints the list in ascending order.
	void rPrintRev(const node* trav) -- Recursively prints the list in descending order.
	void rClear(node* trav) -- Uses recursion to remove every element from the list.
	void rDelete(node* trav, KeyType target) -- Recursively finds target, deleting it from the list.
	void rInsert(node* trav, ItemType newItem) -- Recursively finds the position to place new item and
			inserts it in the list.
	void rRetrieve(node* trav, ItemType tbr) -- Recursively finds the requested item and copies it into tbr.
*/
//*************************************************************************************************
#include <iostream>		// For Print and PrintRev.

#include "Exceptions.h" // Exceptions encountered in OrdList methods.

#include "ItemType.h"	// Struct for element data.
#include "Node.h"

template<typename T>
class OrdListClass
{
	public: 
	
// ------------------------------------------------------------------------------------------------
// |																							  |
// |								Constructors & Destructors									  |
// |																							  |
// ------------------------------------------------------------------------------------------------
		
		// O(1)			Default Constructor
		OrdListClass();
		/*
		Purpose: Instantiates a new class object.
		Pre: n/a
		Post: Object has been instantiated and head points to nullptr.
		*/

		// O(N)			Destructor
		~OrdListClass();
		/*
		Purpose: Frees the dynamic memory allocated during the life of the object.
		Pre: Object exists.
		Post: All nodes have been deleted and head points to nullptr.
		*/

		// O(N)			Copy Constructor
		OrdListClass(/*in*/ const OrdListClass& orig); // List to be copied.
		/*
		Purpose: Instantiates a new class object as a deep copy of orig.
		Pre: Both orig and applying object exist.
		Post: Applying object contains copies of all elements in orig.
		*/

// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Observer Predicators									  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		// O(1)
		bool IsFull() const;
		/*
		Purpose: Determines if the list is full.
		Pre: Object exists.
		Post: Returns false, as list will only be full if memory has filled.
		*/

		// O(1)
		bool IsEmpty() const;
		/*
		Purpose: Determines if list is empty.
		Pre: Object exists.
		Post: Returns true if head == nullptr, false otherwise.
		*/

// ------------------------------------------------------------------------------------------------
// |																							  |
// |										Mutators											  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		// O(N)
		void Insert(/*in*/ T newItem); // Item to be inserted.
		/*
		Purpose: Wrapper method for rInsert().
		Pre: List object exists.
		Post: rInsert() has been called.
		*/

		// O(N)
		void Delete(/*in*/ KeyType target); // Key of item to delete.
		/*
		Purpose: Wrapper method for rDelete().
		Pre: List Object exists.
		Post: if list is not empty, rDelete() is called. Otherwise, KeyNotThereException is thrown.
		Exceptions Thrown: KeyNotThereException.
		*/

		// O(N)
		void Clear();
		/*
		Purpose: Wrapper method for rClear().
		Pre: List object exists.
		Post: rClear() has been called.
		*/

// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Observer Accessor										  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		// O(N)
		T Retrieve(/*in*/ KeyType target) const; // Key of item to be returned.
		/*
		Purpose: Wrapper method for rRetrieve().
		Pre: List object exists.
		Post: rRetrieve() has been called if list is not empty. Otherwise, KeyNotThereException is thrown.
		Exceptions Thrown: KeyNotThereException.
		*/

// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Observer Summarizers									  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		// O(N)
		void Print() const;       
		/*
		Purpose: Wrapper method for rPrint().
		Pre: List object exists
		Post: rPrint() has been called.
		*/

		// O(N)
		void PrintReverse() const;
		/*
		Purpose: Wrapper method for rPrintRev().
		Pre: List object exists
		Post: rPrintRev() has been called.
		*/

// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Overloaded Operators									  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		// O(N)
		virtual void operator =(/*in*/ const OrdListClass& orig);	// List to be copied.
		/*
		Purpose: Performs a deep copy of orig, storing it in the applying object.
		Pre: Both objects have been instantiated.
		Post: the applying object will contain copies of all the elements in orig.
		*/

		// O(N + M)
		virtual OrdListClass operator +(/*in*/ const OrdListClass& rtOp) const; // List to be added to applying object.
		/*
		Purpose: Combines rtOp and the applying object. Any items that appear in both lists
				 only appear once in the returned list.
		Pre: Both objects exist.
		Post: The union of the two ordered lists will be returned. If the union of the two lists exceeds available memory,
			  an exception will be thrown.
		*/

		// O(N + M)
		virtual OrdListClass operator -(/*in*/ const OrdListClass& rtOp) const; // List to be subtracted from applying object.
		/*
		Purpose: Subtracts rtOp from applying object, removing all elements that appear
				 in both lists from the applying object.
		Pre: Both objects exist.
		Post: A list containing the result of the subtraction will be returned.
		*/

		

	private:	
		// PDM
		node<T> *head = nullptr;	

// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Recursive (Wrapped) Methods								  |
// |																							  |
// ------------------------------------------------------------------------------------------------

	protected:  
		// O(N)
		node<T> *Allocate();
		/*
		Purpose: Allocates a new node for the list.
		Pre: Object exists.
		Post: If memory is available, a newly allocated node will be returned. If not,
			  InsertFullException will be thrown.
		Exceptions Thrown: InsertFullException.
		*/
		
		// O(N)
		void rPrint(/*in*/ const node<T> *trav) const; // Pointer to traversal node in ordList
		/*
		Purpose: Prints the list in ascending order, from head to tail.
		Pre: OrdList object exists.
		Post: List has been printed to the screen.
		*/

		// O(N)
		void rPrintRev(/*in*/ const node<T> *trav) const; // Pointer to traversal node in ordList
		/*
		Purpose: Prints the list in reverse order, from tail to head.
		Pre: OrdList object exists.
		Post: List has been printed to the screen.
		*/

		// O(N)
		void rClear(/*in*/ node<T> *trav); // Pointer to traversal node in ordList
		/*
		Purpose: Clears the list.
		Pre: OrdList object exists.
		Post: All elements have been deleted and head points to nullptr.
		*/

		// O(N)
		void rDelete(/*in*/ node<T> *trav,			// Pointer to traversal node in ordList
				 	 /*in*/ KeyType target);	// Target key to be deleted.
		/*
		Purpose: Deletes an item from the list.
		Pre: OrdList object exists.
		Post: If target item is found, it will be deleted. Otherwise, KeyNotThereException
			  will be thrown.
		Exceptions Thrown: KeyNotThereException
		*/

		// O(N)
		void rInsert(/*in*/ node<T> *trav,			// Pointer to traversal node in ordList
					 /*in*/ T newItem);	// Item to be inserted.
		/*
		Purpose: Inserts an item to the list object, maintaining order.
		Pre: OrdList object exists.
		Post: If item is not already in the list, it will be inserted in the correct position.
			  If it is already in the list, DuplicateKeyException will be thrown.
		Exceptions Thrown: DuplicateKeyException
		*/

		// O(N)
		void rRetrieve(/*in*/ node<T> *trav,				// Pointer to traversal node in ordList
					   /*in/out*/ T &tbr,		// Item to be returned.
					   /*in*/ KeyType target) const;	// Requested key to be retrieved.
		/*
		Purpose: Retrieves the requested element, specified by target.
		Pre: Object exists.
		Post: If the key is in the list, the item will be returned. Otherwise, KeyNotThereException
			  will be thrown. 
		Exceptions Thrown: KeyNotThereException
		*/

};

template<typename T>
void OrdListClass<T>::Insert(T newItem) {

	this->rInsert(head, newItem);

}

template<typename T>
void OrdListClass<T>::Delete(KeyType target) {

	if (!this->IsEmpty())
		this->rDelete(head, target);
	else
		throw new KeyNotThereException;

}

template<typename T>
T OrdListClass<T>::Retrieve(KeyType target) const {

	if (!this->IsEmpty()) {

		T temp;
		this->rRetrieve(head, temp, target);

		return temp;

	}
	else
		throw new KeyNotThereException;

}

template<typename T>
node<T> * OrdListClass<T>::Allocate() {

	try {
		return new node<T>;
	}
	catch (const std::exception &e) {

		throw new OutOfMemoryException;

	}

}

template<typename T>
void OrdListClass<T>::rInsert(node<T> *trav, T newItem) {

	if (this->IsEmpty()) {

		head = Allocate();

		head->item = newItem;
		head->prev = head;

		return;

	}
	else if (trav->prev->item.key < newItem.key) {

		node<T> *temp = Allocate();
		temp->item = newItem;
		temp->prev = trav->prev;
		trav->prev = temp;

		return;

	}
	else if (trav->prev->item.key == newItem.key)
		throw new DuplicateKeyException;

	if (trav->prev->prev != this->head->prev)
		this->rInsert(trav->prev, newItem);
	else {

		node<T> *temp = Allocate();
		temp->item = newItem;
		temp->prev = this->head->prev;
		this->head->prev = temp;

		head = temp;

	}

}

template<typename T>
void OrdListClass<T>::rDelete(node<T> *trav, KeyType target) {

	//check if prev(next) item is the target
	if (trav->prev->item.key == target) {

		//check if the prev(next) item is also the head
		if (trav->prev == this->head) {

			//check if this item is also the head
			if (trav == this->head) {

				//just delete head and move on
				delete this->head;
				this->head = nullptr;
				return;

			}
			else
				this->head = trav;

		}

		node<T> *temp = trav->prev;
		trav->prev = trav->prev->prev;
		delete temp;

	}
	else if (trav->prev->prev != this->head->prev)
		this->rDelete(trav->prev, target);
	else
		throw new KeyNotThereException;

}

template<typename T>
void OrdListClass<T>::rRetrieve(node<T> *trav, T &tbr, KeyType target) const {

	if (trav->prev->item.key == target)
		tbr = trav->prev->item;
	else if (trav->prev->prev != this->head->prev)
		rRetrieve(trav->prev, tbr, target);
	else
		throw new KeyNotThereException;

}

template<typename T>
void OrdListClass<T>::rClear(node<T> *trav) {

	if (trav->prev != this->head)
		this->rClear(trav->prev);

	delete trav;

}

template<typename T>
void OrdListClass<T>::rPrint(const node<T> *trav) const {

	if (trav->prev != head->prev)
		rPrint(trav->prev);

	std::cout << trav->item.key << '\n';

}

template<class T>
void OrdListClass<T>::rPrintRev(const node<T> *trav) const {

	std::cout << trav->item.key << '\n';

	if (trav->prev != head->prev)
		rPrintRev(trav->prev);

}

/*
***************************************************************************************************************
*/

template<typename T>
OrdListClass<T>::OrdListClass() {



}

template<typename T>
OrdListClass<T>::~OrdListClass() {

	this->Clear();

}

template<typename T>
OrdListClass<T>::OrdListClass(const OrdListClass<T>& orig) {

	*this = orig;

}

template<typename T>
bool OrdListClass<T>::IsFull() const {

	return false;

}

template<typename T>
bool OrdListClass<T>::IsEmpty() const {

	return !this->head;

}

template<typename T>
void  OrdListClass<T>::Clear() {

	if (!this->IsEmpty())
		this->rClear(head);

	head = nullptr;

}

template<typename T>
void OrdListClass<T>::Print() const {

	if(!this->IsEmpty())
		this->rPrint(head->prev);

}

template<typename T>
void OrdListClass<T>::PrintReverse() const {

	if (!this->IsEmpty())
		this->rPrintRev(head->prev);

}

template<typename T>
void OrdListClass<T>::operator=(const OrdListClass &orig) {

	this->Clear();

	//if the orig is not empty, begin attempting to insert data into this
	if (!orig.IsEmpty()) {

		this->Insert(orig.head->item);
		node<T> *temp = orig.head->prev;

		while (temp != orig.head) {

			this->Insert(temp->item);
			temp = temp->prev;

		}

	}

}

template<typename T>
OrdListClass<T> OrdListClass<T>::operator+(const OrdListClass<T> &orig) const {

	OrdListClass tempClass;
	tempClass = *this;

	//if the orig is not empty, begin attempting to insert data into tempClass
	if (!orig.IsEmpty()) {

		tempClass.Insert(orig.head->item);
		node<T> *temp = orig.head->prev;

		while (temp != orig.head) {

			tempClass.Insert(temp->item);
			temp = temp->prev;

		}

	}

	return tempClass;

}

template<typename T>
OrdListClass<T> OrdListClass<T>::operator-(const OrdListClass<T> &orig) const {

	OrdListClass tempClass;
	tempClass = *this;

	//if the orig is not empty, begin attempting to delete what exists in orig from tempClass
	if (!orig.IsEmpty()) {

		tempClass.Delete(orig.head->item.key);
		node<T> *temp = orig.head->prev;

		while (temp != orig.head) {

			tempClass.Delete(temp->item.key);
			temp = temp->prev;

		}

	}

	return tempClass;

}

//#include "OrdList.cpp"

/*
https://stackoverflow.com/questions/36039/templates-spread-across-multiple-files
https://stackoverflow.com/questions/115703/storing-c-template-function-definitions-in-a-cpp-file
https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl

You can do it, but it's dumb
*/