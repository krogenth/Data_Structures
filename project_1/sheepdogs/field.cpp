/*
Name:  Daniel Kelley
Class: CIS243
Date:  10/2/2019
*/
#include "field.h"
#include "AnimalInterface.h"
#include "Sheep.h"
#include "Sheepdog.h"

field::field(int32_t x, int32_t y) {

	width = x;
	height = y;

	//create a new dynamic array for the field
	fieldMap = new fieldStruct[x * y];

}

field::~field() {

	delete[]fieldMap;

}

int32_t field::getWidth() {

	return width;

}

int32_t field::getHeight() {

	return height;

}

void field::setTypeFlag(int32_t x, int32_t y, typesEnum type) {

	fieldMap[x + (width * y)].typeFlags |= type;

}

uint32_t field::getTypeFlags(int32_t x, int32_t y) {

	return fieldMap[x + (width * y)].typeFlags;

}

AnimalInterface * field::getOccupier(int32_t x, int32_t y) {

	return fieldMap[x + (width * y)].occupier_ptr;

}

void field::setAnimal(AnimalInterface *animal) {

	//add's occupier type to new field tile's bitflag, add the occupier's pointer
	fieldMap[animal->getXPos() + (width * animal->getYPos())].typeFlags |= animal->getType();
	fieldMap[animal->getXPos() + (width * animal->getYPos())].occupier_ptr = animal;

}

void field::removeAnimal(AnimalInterface *animal) {

	//remove occupier type from field tile's biflag, remove the occupier's pointer
	fieldMap[animal->getXPos() + (width * animal->getYPos())].typeFlags &= ~fieldMap[animal->getXPos() + (width * animal->getYPos())].occupier_ptr->getType();
	fieldMap[animal->getXPos() + (width * animal->getYPos())].occupier_ptr = nullptr;

}

void field::update(int32_t x, int32_t y) {

	AnimalInterface *temp = fieldMap[x + (width * y)].occupier_ptr;

	//remove occupier type from field tile's biflag, remove the occupier's pointer
	fieldMap[x + (width * y)].typeFlags &= ~fieldMap[x + (width * y)].occupier_ptr->getType();
	fieldMap[x + (width * y)].occupier_ptr = nullptr;

	//add's occupier type to new field tile's bitflag, add the occupier's pointer
	fieldMap[temp->getXPos() + (width * temp->getYPos())].typeFlags |= temp->getType();
	fieldMap[temp->getXPos() + (width * temp->getYPos())].occupier_ptr = temp;

	outputMap();

}

void field::outputMap() {

	std::ofstream outFile;
	outFile.open("results.txt", std::ios::app);

	for (int32_t i = 0; i < height; i++) {

		for (int32_t j = 0; j < width; j++) {

			//check if there are any type flags set for the current field tile
			if (fieldMap[j + (width * i)].typeFlags) {

				//check if there is an AnimalInterface derived object in the current field tile
				if (fieldMap[j + (width * i)].occupier_ptr) {

					//check if the AnimalInterface derived object in the current field tile is a sheep
					if (fieldMap[j + (width * i)].occupier_ptr->getType() == typesEnum::SheepType) {

						//check if there is a hazard at the current field tile
						if (fieldMap[j + (width * i)].typeFlags & typesEnum::hazardType)
							outFile << '$';
						else
							outFile << 'S';

					}
					else
						//it was actually a doggo
						outFile << 'D';

				}
				else
					//there was no AnimalInterface dervied object, so it is only a hazard
					outFile << 'H';

			}
			else
				outFile << ' ';

		}

		outFile << '\n';

	}

	outFile << "\n\n";

	outFile.close();

}