#include "exceptions.h"
#include "StackClass.h"

Stack::Stack() {


}

Stack::Stack(const Stack &stack_) {

	*this = stack_;

}

Stack::~Stack() {

	this->Clear();

}

void Stack::Clear() {

	while (!IsEmpty())
		this->Pop();

}

bool Stack::Top(ItemType &item_) {

	if (!this->head)
		return false;

	item_ = this->head->item;
	return true;

}

void Stack::Pop() {

	node *temp = this->head;

	if (!IsEmpty()) {

		this->head = this->head->next;
		delete temp;
		this->size--;

	}

}

void Stack::Push(ItemType item_) {

	//We are limited to 4 elements, so, make sure there are only 4 elements.
	if (size == SIZE_LIMIT)
		throw std::bad_exception();

	node *temp = nullptr;

	temp = Allocate();

	temp->item = item_;
	temp->next = this->head;
	this->head = temp;
	this->size++;

}

bool Stack::IsEmpty() const {

	return !this->head;

}

void Stack::operator=(const Stack& stack_) {

	node *temp;
	node *oldTemp = stack_.head;

	//clear current Stack object because we don't need it anymore #YOLO
	this->Clear();

	this->head = Allocate();

	//begin writing stack_'s data to the current Stack object
	this->size = stack_.size;
	this->head->item = oldTemp->item;
	temp = this->head;
	oldTemp = oldTemp->next;

	while (oldTemp) {

		temp->next = Allocate();
		temp->next->item = oldTemp->item;
		temp = temp->next;
		oldTemp = oldTemp->next;

	}

}

bool Stack::operator==(const Stack& stack_) const {

	if (this->size != stack_.size)
		return false;

	node *leftNode = this->head, *rightNode = stack_.head;

	while (leftNode) {

		if (leftNode->item.key != rightNode->item.key)
			return false;

		leftNode = leftNode->next;
		rightNode = rightNode->next;

	}

	return true;

}

bool Stack::operator!=(const Stack& stack_) const {

	return !(*this == stack_);

}

node * Stack::Allocate() {

	return new node;

}