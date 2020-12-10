//Daniel Kelley
//File: OrdList.cpp
//Date: 10/21/2019
//Purpose: To define the inheriting OrdList class from ABCListClass

#include "OrdList.h"

OrdListClass::OrdListClass() {

	SetLength(0);
	SetCurrPos(0);
	SetSize(INITIAL_SIZE);

	SetListPtr(new ItemType[INITIAL_SIZE]);

}

OrdListClass::OrdListClass(const OrdListClass &orig) {

	//We overloaded those operators, so we're gonna use 'em!
	*this = orig;

}

OrdListClass::~OrdListClass() {

	Clear();

}

void OrdListClass::NextPosition() {

	if (GetCurrPos() < (GetLength() - 1))
		SetCurrPos(GetCurrPos() + 1);
	else
		throw std::out_of_range("Somehow the currPos was out of range.\n");

}

bool OrdListClass::IsFull() const {

	return (GetLength() == GetSize());

}

bool OrdListClass::EndOfList() const {

	bool isEnd = false;
	if (GetCurrPos() == GetLength() - 1)
		isEnd = true;
	return isEnd;

}

bool OrdListClass::Find(/* in */KeyType key) {

	bool found = false;

	int floor = 0;
	int ceiling = GetLength();

	while (true) {

		//Quick ((ceiling + floor) / 2)
		SetCurrPos((ceiling + floor) >> 1);

		//we want to exhaust all possible elements, so floor must be <= ceiling
		if (floor <= ceiling) {

			if (GetListPtr()[GetCurrPos()].key > key)
				ceiling = GetCurrPos() - 1;
			else if (GetListPtr()[GetCurrPos()].key < key)
				floor = GetCurrPos() + 1;
			else {

				//If the key was found, great, we're done
				found = true;
				break;

			}

		}
		else {

			//We didn't find the key, so we check to see if we're at the end of the list, if so, we use the floor value, not ((ceiling + floor) / 2)
			if(floor < GetLength())
				SetCurrPos(floor);
			found = false;
			break;

		}

	}

	return found;

}

void OrdListClass::Insert(/* in */ ItemType target) {

	//Clear is a dependency for ~OrdListClass, but clear is also public, so it can be called at any time
		//So, if Clear was called, we need to initialize a new list to use
	if (!GetListPtr())
		SetListPtr(new ItemType[INITIAL_SIZE]);
	else {

		if (IsFull())
			Expand();

	}

	if (!Find(target.key)) {

		for (int i = GetLength(); i > GetCurrPos(); i--)
			GetListPtr()[i] = GetListPtr()[i - 1];

		SetLength(GetLength() + 1);

	}

	GetListPtr()[GetCurrPos()] = target;

}

void OrdListClass::Delete() {

	//Ensure that currPos is within the legal range(no FBI, plz)
	if ((GetCurrPos() >= 0) && (GetCurrPos() <= (GetLength() - 1))) {

		for (int i = GetCurrPos(); i < GetLength() - 1; i++)
			GetListPtr()[i] = GetListPtr()[i + 1];

		SetLength(GetLength() - 1);

		if ((GetSize() * OCCUPANCY_TRIGGER) > GetLength())
			Contract();

	}

}

void OrdListClass::Clear() {

	SetCurrPos(0);
	SetLength(0);
	SetSize(INITIAL_SIZE);

	if(GetListPtr())
		delete[] GetListPtr();
	SetListPtr(nullptr);

}

void OrdListClass::Print(int base) {

	//Need a char array to be able to properly return the converted base-n character array
		//base is a default parameter, set to 10, so it will output base-10 unless told otherwise
	char result[100];

	if (base > 36)
		base = ceil(base / 36) + 1;

	for (int i = 0; i < GetLength(); i++)
		std::cout << "Position " << i << " is: " << std::baseConv::FromDecimal(result, GetListPtr()[i].key, base) << std::endl;

}

bool OrdListClass::operator==(/* in */const OrdListClass& rtOp) const {

	bool equals = true;

	if (GetLength() != rtOp.GetLength())
		equals = false;
	else {

		for (int i = 0; i < GetLength(); i++)
			if (GetListPtr()[i].key != rtOp.GetListPtr()[i].key) {

				equals = false;
				break;

			}

	}

	return equals;

}

bool OrdListClass::operator!=(/* in */const OrdListClass& rtOp) const {

	return (!(*this == rtOp));

}

OrdListClass OrdListClass::operator*(/* in */const OrdListClass& rtOp) const {

	OrdListClass temp;

	int floor = 0;
	int ceiling = rtOp.GetLength();
	int check = 0;

	for (int i = 0; i < GetLength(); i++) {

		floor = 0;
		ceiling = rtOp.GetLength();
		check = 0;

		while (true) {

			check = (ceiling + floor) >> 1;

			if (floor <= ceiling) {

				if (rtOp.GetListPtr()[check].key > GetListPtr()[i].key)
					ceiling = check - 1;
				else if (rtOp.GetListPtr()[check].key < GetListPtr()[i].key)
					floor = check + 1;
				else {

					temp.Insert(GetListPtr()[i]);
					break;

				}

			}
			else
				break;

		}

	}

	return temp;

}

OrdListClass OrdListClass::operator+(/* in */const OrdListClass& rtOp) const {

	OrdListClass temp(rtOp);

	for (int i = 0; i < GetLength(); i++)
		temp.Insert(GetListPtr()[i]);

	return temp;

}

void OrdListClass::operator=(/* in */const OrdListClass& orig) {

	SetLength(orig.GetLength());
	SetCurrPos(orig.GetCurrPos());
	SetSize(orig.GetSize());

	if(GetListPtr())
		delete[] GetListPtr();
	SetListPtr(new ItemType[GetSize()]);

	for (int i = 0; i < GetLength(); i++)
		GetListPtr()[i] = orig.GetListPtr()[i];

}

//implementation of PVF's
void OrdListClass::Expand() {

	SetSize(GetSize() << 1);
	ItemType *temp = new ItemType[GetSize()];

	for (int i = 0; i < GetLength(); i++)
		temp[i] = GetListPtr()[i];

	delete[] GetListPtr();
	SetListPtr(temp);

}

void OrdListClass::Contract() {

	if ((GetSize() * CONTRACTION_FACTOR) <= INITIAL_SIZE)
		return;

	SetSize(GetSize() * CONTRACTION_FACTOR);
	ItemType *temp = new ItemType[GetSize()];

	for (int i = 0; i < GetLength(); i++)
		temp[i] = GetListPtr()[i];

	delete[] GetListPtr();
	SetListPtr(temp);

}

bool OrdListClass::NoRoom() {
	
	return (GetLength() == GetSize());

}