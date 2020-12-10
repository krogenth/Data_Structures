//Daniel Kelley
//File: BinaryTree.tpp
//Date: 12/19/2019
//Purpose: To define the implementation of the templated BinaryTree class

#include <iostream>
#include <fstream>
//#include <math.h>
#include <cinttypes>
#include <string>

#include "Exceptions.h"

template <class T>
BinaryTree<T>::BinaryTree() {



}

template <class T>
BinaryTree<T>::~BinaryTree() {

	if(!this->IsEmpty())
		this->Clear();

}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree& orig) {

	*this = orig;

}

template <class T>
void  BinaryTree<T>::FirstPosition() const {

	if (this->IsEmpty())
		return;

	this->prevPos = currPos;
	this->currPos = root;

	while (this->currPos->left)
		this->currPos = this->currPos->left;

}

template <class T>
void  BinaryTree<T>::NextPosition() const {

	if (this->IsEmpty())
		return;

	this->prevPos = this->currPos;

	if(this->EndofList())
		this->currPos = nullptr;
	else
		this->currPos++;

}

template <class T>
void BinaryTree<T>::PrevPosition() const {

	if (this->IsEmpty())
		return;

	this->prevPos = this->currPos;

	if(this->StartOfList())
		this->currPos = nullptr;
	else
		this->currPos--;

}

template <class T>
void  BinaryTree<T>::LastPosition() const {

	if (this->IsEmpty())
		return;

	this->prevPos = this->currPos;
	this->currPos = root;

	while (this->currPos->right)
		this->currPos = this->currPos->right;

}

template <class T>
bool  BinaryTree<T>::IsEmpty() const {

	return !this->root;

}

template <class T>
bool  BinaryTree<T>::IsFull() {

	return !true;

}

template <class T>
bool  BinaryTree<T>::EndofList() const {

	if (this->IsEmpty())
		return true;

	node<T> *temp = this->root;

	while (temp->right)
		temp = temp->right;

	return temp == this->currPos;

}

template <class T>
bool  BinaryTree<T>::StartOfList() const {

	if (this->IsEmpty())
		return true;

	node<T> *temp = this->root;

	while (temp->left)
		temp = temp->left;

	return temp == this->currPos;

}

template <class T>
ItemType BinaryTree<T>::Retrieve() {

	if(this->IsEmpty())
		throw new RetrieveOnEmptyException;

	if (currPos)
		return this->currPos->item;
	else
		throw new RetrieveOnNULLException;

}

template <class T>
bool BinaryTree<T>::Find(KeyType target) {

	if (this->IsEmpty())
		return false;

	node<T> *temp = this->currPos;
	int64_t floor = 0;
	int64_t ceiling = 0;
	size_t firstPos = 0;

	node<T> *mid;

	this->LastPosition();
	ceiling = (size_t)this->currPos;
	this->FirstPosition();
	ceiling -= (size_t)this->currPos;
	ceiling /= sizeof(node<T>);

	firstPos = (size_t)this->currPos;

	this->currPos = temp;

	while (floor <= ceiling) {

		mid = (node<T>*)(firstPos + (((ceiling + floor) >> 1) * sizeof(node<T>)));

		if (mid->item.key == target) {

			this->currPos = mid;
			break;

		}
		else if (mid->item.key > target)
			ceiling = ((ceiling + floor) >> 1) - 1;
		else
			floor = ((ceiling + floor) >> 1) + 1;

	}

	this->prevPos = temp;

	if (!this->currPos || currPos->item.key != target) {

		this->currPos = nullptr;
		return false;

	}

	return true;

}

template <class T>
void BinaryTree<T>::Insert(T newItem) {

	if (this->IsEmpty()) {

		this->root = this->Allocate();
		this->root->item = newItem;
		return;

	}

	BinaryTree<T> right;
	right.root = right.Allocate();
	right.root->item = newItem;

	*this = *this + right;

}

template <class T>
void BinaryTree<T>::Delete() {

	BinaryTree<T> right;
	right.root = right.Allocate();
	right.root->item = this->currPos->item;

	*this = *this - right;

}

template <class T>
void BinaryTree<T>::Clear() {

	if (this->IsEmpty())
		return;

	this->FirstPosition();
	delete[] this->currPos;

	this->root = nullptr;
	this->currPos = nullptr;
	this->prevPos = nullptr;

}

template <class T>
int BinaryTree<T>::ReturnLength() const {

	node<T> *currentPos = this->currPos;

	this->LastPosition();
	int length = reinterpret_cast<intptr_t>(this->currPos);

	this->FirstPosition();
	length -= reinterpret_cast<intptr_t>(this->currPos);

	this->currPos = currentPos;

	return (length / sizeof(node<T>)) + 1;

}

template <class T>
bool BinaryTree<T>::IsBalanced() {

	return true;

}

template <class T>
void BinaryTree<T>::operator= (const BinaryTree& orig) {

	this->Clear();

	if (orig.IsEmpty())
		return;

	orig.LastPosition();
	size_t length = (size_t)orig.currPos;
	size_t rightFirstPosition = 0;

	orig.FirstPosition();
	rightFirstPosition = (size_t)orig.currPos;
	length -= (size_t)orig.currPos;
	length /= sizeof(node<T>);
	++length;

	node<T> *nodes = new node<T>[length];

	for (size_t i = 0; i < length; i++) {

		nodes[i].item = orig.currPos->item;
		if(orig.currPos->left)
			nodes[i].left = &nodes[0] + (((size_t)orig.currPos->left - rightFirstPosition) / sizeof(node<T>));
		if(orig.currPos->right)
			nodes[i].right = &nodes[0] + (((size_t)orig.currPos->right - rightFirstPosition) / sizeof(node<T>));
		orig.NextPosition();

	}

	orig.FirstPosition();

	this->root = &nodes[0] + (((size_t)orig.root - (size_t)orig.currPos) / sizeof(node<T>));
	if(orig.currPos)
		this->currPos = &nodes[0] + (((size_t)orig.currPos - (size_t)orig.currPos) / sizeof(node<T>));
	if(orig.prevPos)
		this->prevPos = &nodes[0] + ((size_t)orig.prevPos - (size_t)orig.currPos) / sizeof(node<T>);

}

template <class T>
BinaryTree<T> BinaryTree<T>::operator+ (const BinaryTree<T>& rtOp) const {

	BinaryTree<T> temp;

	node<T> *arr = new node<T> [this->ReturnLength() + rtOp.ReturnLength()]{};
	size_t arrCount = 0;

	this->FirstPosition();
	rtOp.FirstPosition();

	//we need to merge sort the two trees
	while (this->currPos && rtOp.currPos) {

		if (this->currPos->item.key < rtOp.currPos->item.key) {

			arr[arrCount].item = this->currPos->item;
			arrCount++;
			this->NextPosition();

		}
		else if (this->currPos->item.key > rtOp.currPos->item.key) {

			arr[arrCount].item = rtOp.currPos->item;
			arrCount++;
			rtOp.NextPosition();

		}
		else {

			arr[arrCount].item = this->currPos->item;
			arrCount++;
			this->NextPosition();
			rtOp.NextPosition();

		}

	}

	//ensure neither one has remaining nodes to insert
	while (this->currPos) {

		arr[arrCount].item = this->currPos->item;
		arrCount++;
		this->NextPosition();

	}

	while (rtOp.currPos) {

		arr[arrCount].item = rtOp.currPos->item;
		arrCount++;
		rtOp.NextPosition();

	}


	//fix the array size so we're not wasting memory :)
	node<T> *arrFixed = new node<T> [arrCount]();
	for (size_t i = 0; i < arrCount; i++)
		arrFixed[i].item = arr[i].item;

	delete[] arr;

	temp.MakeTree(arrFixed, arrCount);
	return temp;

}

template <class T>
BinaryTree<T> BinaryTree<T>::operator-(const BinaryTree<T>& rtOp) const {

	/*	OLD VERSION, SIGNIFICANTLY SLOWER AT HIGHER ELEMENT COUNTS
	BinaryTree<T> temp;
	BinaryTree<T> left(*this), right(rtOp);

	left.FirstPosition();

	while (!left.EndofList()) {

		if (!right.Find(left.currPos->item.key))
			temp.Insert(left.currPos->item);

		left.NextPosition();

	}

	if (!right.Find(left.currPos->item.key))
		temp.Insert(left.currPos->item);

	return temp;
	*/

	BinaryTree<T> temp;
	BinaryTree<T> left(*this), right(rtOp);

	node<T>* arr = new node<T>[this->ReturnLength()]{};
	size_t arrCount = 0;

	left.FirstPosition();

	while (!left.EndofList()) {

		if (!right.Find(left.currPos->item.key)) {

			arr[arrCount].item = left.currPos->item;
			arrCount++;

		}

		left.NextPosition();

	}

	if (!right.Find(left.currPos->item.key)) {

		arr[arrCount].item = left.currPos->item;
		arrCount++;

	}

	//fix the array size so we're not wasting memory :)
	node<T>* arrFixed = new node<T>[arrCount]{};
	for (size_t i = 0; i < arrCount; i++)
		arrFixed[i].item = arr[i].item;

	delete[] arr;

	if (arrCount == 1)
		temp.Insert(arrFixed[0].item);
	else if (arrCount > 1)
		temp.MakeTree(arrFixed, arrCount);

	return temp;

}

template <class T>
bool BinaryTree<T>::operator== (const BinaryTree<T>& rtOp) const {

	BinaryTree<T> left(*this);
	BinaryTree<T> right(rtOp);

	left.FirstPosition();
	right.FirstPosition();

	if (left.ReturnLength() != right.ReturnLength())
		return false;

	while (!left.EndofList()) {

		if (left.currPos->item.key != right.currPos->item.key)
			return false;

		left.NextPosition();
		right.NextPosition();

	}

	return true;

}

template <class T>
bool BinaryTree<T>::operator!= (const BinaryTree<T>& rtOp) const {

	return !(*this == rtOp);

}

template <class T>
void BinaryTree<T>::PrintScreen(void (*func)(BinaryTree<T>)) {

	std::cout << "Printing:\n";

	if (this->IsEmpty())
		return;

	(*func)(*this);

}

template <class T>
void BinaryTree<T>::PrintFile(void (*func)(BinaryTree<T>)) {

	std::string fileName = "output.txt";
	std::streambuf *backupCout;			//We need to make a backup of std::cout's stream buffer
	std::ofstream coutFile(fileName, std::ios::app);

	if (this->IsEmpty())
		return;

	backupCout = std::cout.rdbuf();		//Grab std::cout's stream buffer and store it
	std::cout.rdbuf(coutFile.rdbuf());	//Set std::cout's stream buffer to be the std::ofstream's

	(*func)(*this);

	std::cout.rdbuf(backupCout);

	std::cout << "Tree printed to: " << fileName << '\n';

}

template <class T>
void BinaryTree<T>::PrintReverse(void (*func)(BinaryTree)) {

	std::cout << "Printing:\n";

	if (this->IsEmpty())
		return;

	(*func)(*this);

}

template <class T>
void BinaryTree<T>::PrintAsExists(void (*func)(BinaryTree)) {



}

template <class T>
node<T> * BinaryTree<T>::Allocate() {

	try {

		return new node<T>;

	}
	catch (const std::exception &e) {

		throw new OutOfMemoryException;

	}

}

template <class T>
void BinaryTree<T>::MakeTree(node<T> *arr, size_t arrCount) {	//functional

	//We need to ensure the tree is complete, so there was a lot of math and calculations done to figure this out, this is the result:

	size_t fullDepthRequired = (uint32_t)std::floor(std::log2(arrCount)) - 1;		//We need to know how many levels(rows) in the tree there are, excluding the root and the very bottom row(regardless of if it is full or not)
	size_t fullTotal = (1 << (uint32_t)std::floor(std::log2(arrCount))) - 1;		//We need to know how many nodes there are that would make a "full" tree
	size_t totalBottom = arrCount - fullTotal;										//We need to know how many nodes are not contained within the "full" tree(the bottom level/row)
	
	node<T> **fullElements = new node<T> *[arrCount - totalBottom]{};				//We need an array of pointers to pointers so we do not have any nodes outside of the original array(we need things mapped out in memory)

	size_t i = 0;

	//We need to grab every other node to store(starting at position 0, and every other, is the very bottom row of the tree)
	for (; i < totalBottom - 1; i++)
		fullElements[i] = &arr[(i << 1) + 1];

	i = (i << 1) + 1;																//Since we were doing some manipulation previously, we need to set 'i' to be what would come next

	//We need to grab every remaining node in the array to make the "full" tree
	for (size_t j = ((i - 1) >> 1); i < arrCount; i++) {

		fullElements[j] = &arr[i];
		++j;

	}

	//We now need to deal with each level/row within the "full" tree, excluding the root
	for (size_t j = 0; j < fullDepthRequired; j++) {

		//We need to loop through all nodes that will be on that level/row( (1 << (fullDepthRequired - j)) gives us that answer)
		for (size_t k = 0; k < (1 << (fullDepthRequired - j)); k += 2) {

			//This requires a lot of explaination, and I don't think I can really do a bunch of pretty pictures to help illustrate it, so here goes:
				//We need to rebuild the tree to be complete, you can do this top-to-bottom or bottom-to-top, since bottom-to-top seemed easier, that was the route chosen.
					//((1 << (fullDepthRequired - (fullDepthRequired - j)))) - 1		//is the base positioning(furthest left node on that row)
					//(k * (2 << fullDepthRequired - (fullDepthRequired - j)))			//is the offset on the row(each row, the nodes are seperated by a power of 2(2, 4, 8, etc.))
					//((2 << fullDepthRequired - (fullDepthRequired - j)) >> 1)			//is the midpoint between the two nodes, to determine the parent node(the midpoint is always the offset / 2)

					//We now need to tell the parent node(s) of whatever level/row we are looking at who their children nodes are
			fullElements[((1 << (fullDepthRequired - (fullDepthRequired - j)))) - 1 + (k * (2 << (fullDepthRequired - (fullDepthRequired - j)))) + ((2 << (fullDepthRequired - (fullDepthRequired - j))) >> 1)]->left = 
				fullElements[((1 << (fullDepthRequired - (fullDepthRequired - j)))) - 1 + (k * (2 << (fullDepthRequired - (fullDepthRequired - j))))];
			fullElements[((1 << (fullDepthRequired - (fullDepthRequired - j)))) - 1 + (k * (2 << (fullDepthRequired - (fullDepthRequired - j)))) + ((2 << (fullDepthRequired - (fullDepthRequired - j))) >> 1)]->right = 
				fullElements[((1 << (fullDepthRequired - (fullDepthRequired - j)))) - 1 + ((k + 1) * (2 << (fullDepthRequired - (fullDepthRequired - j))))];

		}

	}

	//The root will always be in the middle of the "full" tree array
	this->root = fullElements[(arrCount - totalBottom) >> 1];

	//We now need to link the not "full" tree bottom nodes to their respective parent node(s)
	for (size_t j = 0; j < (totalBottom << 1); j += 4) {

		arr[j + 1].left = &arr[j];

		if((j + 2) < totalBottom << 1)
			arr[j + 1].right = &arr[j + 2];

	}

	delete[] fullElements;

}