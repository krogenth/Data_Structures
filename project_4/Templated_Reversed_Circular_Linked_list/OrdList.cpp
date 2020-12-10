//This file intentionally left for archaic purposes

/*#include "ItemType.h"
#include "Node.h"


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

	this->rPrint(head);

}

template<typename T>
void OrdListClass<T>::PrintReverse() const {

	this->rPrintRev(head);

}

template<typename T>
void OrdListClass<T>::operator=(const OrdListClass &orig) {

	this->Clear();

	if (!this->IsEmpty()) {

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

	if (!this->IsEmpty()) {

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

	if (!this->IsEmpty()) {

		tempClass.Insert(orig.head->item);
		node<T> *temp = orig.head->prev;

		while (temp != orig.head) {

			tempClass.Delete(temp->item.key);
			temp = temp->prev;

		}

	}

	return tempClass;

}*/