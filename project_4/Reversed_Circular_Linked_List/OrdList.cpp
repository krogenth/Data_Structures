//Daniel Kelley
//File: OrdList.cpp
//Date: 12/3/2019
//Purpose: To define the methods of OrdListClass(very important)

#include <iostream>		// For Print and PrintRev.

#include "Exceptions.h" // Exceptions encountered in OrdList methods.
#include "ItemType.h"	// Struct for element data.
#include "Node.h"
#include "OrdList.h"

OrdListClass::OrdListClass() {



}

OrdListClass::~OrdListClass() {

	this->Clear();

}

OrdListClass::OrdListClass(const OrdListClass& orig) {

	*this = orig;

}

bool OrdListClass::IsFull() const {

	return false;

}

bool OrdListClass::IsEmpty() const {

	return !this->head;

}

void OrdListClass::Insert(ItemType newItem) {

	this->rInsert(head, newItem);

}

void OrdListClass::Delete(KeyType target) {

	if (!this->IsEmpty())
		this->rDelete(head, target);
	else
		throw new KeyNotThereException;

}

void  OrdListClass::Clear() {

	if (!this->IsEmpty())
		this->rClear(head);

	head = nullptr;

}

ItemType OrdListClass::Retrieve(KeyType target) const {

	if (!this->IsEmpty()) {

		ItemType temp;
		this->rRetrieve(head, temp, target);

		return temp;

	}
	else
		throw new KeyNotThereException;

}

void OrdListClass::Print() const {

	if(!this->IsEmpty())
		this->rPrint(head->prev);

}

void OrdListClass::PrintReverse() const {

	if (!this->IsEmpty())
		this->rPrintRev(head->prev);

}

void OrdListClass::operator=(const OrdListClass &orig) {

	this->Clear();

	//if the orig is not empty, begin attempting to insert data into this
	if (!orig.IsEmpty()) {

		this->Insert(orig.head->item);
		node *temp = orig.head->prev;

		while (temp != orig.head) {

			this->Insert(temp->item);
			temp = temp->prev;

		}

	}

}

OrdListClass OrdListClass::operator+(const OrdListClass &orig) const {

	OrdListClass tempClass;
	tempClass = *this;

	//if the orig is not empty, begin attempting to insert data into tempClass
	if (!orig.IsEmpty()) {

		tempClass.Insert(orig.head->item);
		node *temp = orig.head->prev;

		while (temp != orig.head) {

			tempClass.Insert(temp->item);
			temp = temp->prev;

		}

	}

	return tempClass;

}

OrdListClass OrdListClass::operator-(const OrdListClass &orig) const {

	OrdListClass tempClass;
	tempClass = *this;

	//if the orig is not empty, begin attempting to delete what exists in orig from tempClass
	if (!orig.IsEmpty()) {

		tempClass.Delete(orig.head->item.key);
		node *temp = orig.head->prev;

		while (temp != orig.head) {

			tempClass.Delete(temp->item.key);
			temp = temp->prev;

		}

	}

	return tempClass;

}

node * OrdListClass::Allocate() {

	try {
		return new node;
	}
	catch (const std::exception &e) {

		throw new OutOfMemoryException;

	}

}

void OrdListClass::rInsert(node *trav, ItemType newItem) {

	if (this->IsEmpty()) {

		head = Allocate();
		head->item = newItem;
		head->prev = head;

		return;

	}
	else if (trav->prev->item.key < newItem.key) {

		node *temp = Allocate();
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

		node *temp = Allocate();
		temp->item = newItem;
		temp->prev = this->head->prev;
		this->head->prev = temp;

		head = temp;

	}

}

void OrdListClass::rDelete(node *trav, KeyType target) {

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

		node *temp = trav->prev;
		trav->prev = trav->prev->prev;
		delete temp;

	}
	else if (trav->prev->prev != this->head->prev)
		this->rDelete(trav->prev, target);
	else
		throw new KeyNotThereException;

}

void OrdListClass::rClear(node *trav) {

	if (trav->prev != this->head)
		this->rClear(trav->prev);

	delete trav;

}

void OrdListClass::rRetrieve(node *trav, ItemType &tbr, KeyType target) const {

	if (trav->prev->item.key == target)
		tbr = trav->prev->item;
	else if (trav->prev->prev != this->head->prev)
		rRetrieve(trav->prev, tbr, target);
	else
		throw new KeyNotThereException;

}

void OrdListClass::rPrint(const node *trav) const {

	if (trav->prev != head->prev)
		rPrint(trav->prev);

	std::cout << trav->item.key << '\n';

}

void OrdListClass::rPrintRev(const node *trav) const {

	std::cout << trav->item.key << '\n';

	if (trav->prev != head->prev)
		rPrintRev(trav->prev);

}