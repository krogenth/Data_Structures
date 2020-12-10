/*
Name:  Daniel Kelley
Class: CIS243
Date:  10/2/2019
*/
#include "field.h"
#include "AnimalInterface.h"
#include "Sheep.h"

uint32_t Sheep::totalSheep = 0;
uint32_t Sheep::sheepLeft = 0;

Sheep::Sheep() {

	totalSheep++;
	sheepLeft++;

}

Sheep::Sheep(int32_t x, int32_t y) {

	xPos = x;
	yPos = y;
	totalSheep++;
	sheepLeft++;

}

Sheep::~Sheep() {

	//decrement the total number of sheep
	totalSheep--;

	//check if this sheep has been rescued, if not, decrement the number of sheep left
	if (!(statusFlag & flagsEnum::Rescued))
		sheepLeft--;

}

uint32_t Sheep::getNumSheep() {

	return totalSheep;

}

uint32_t Sheep::getSheepLeft() {

	return sheepLeft;

}

typesEnum Sheep::getType() {

	return type;

}

void Sheep::removeSheep(field *fieldData) {

	//decrement the amount of sheep left, and remove the sheep pointer from the field
	sheepLeft--;
	fieldData->removeAnimal(this);

}

void Sheep::update(field *fieldData) {

	//store the current position before updating, to allow for faster field updating
	int32_t oldXPos = xPos, oldYPos = yPos;

	if (!(statusFlag & (flagsEnum::Stuck + flagsEnum::Rescued))) {

		if ((std::rand() % 3) == 0) {

			switch (std::rand() % 4) {

			//check which direction to move, and ensure the direction is not out of bounds, set moved flag if sucessfully moved
			case 0: if ((xPos < fieldData->getWidth() - 1) && !(fieldData->getTypeFlags(xPos + 1, yPos))) xPos++; statusFlag |= flagsEnum::Moved; break;
			case 1: if ((yPos > 0) && !(fieldData->getTypeFlags(xPos, yPos - 1))) yPos--; statusFlag |= flagsEnum::Moved; break;
			case 2: if ((xPos > 0) && !(fieldData->getTypeFlags(xPos - 1, yPos))) xPos--; statusFlag |= flagsEnum::Moved; break;
			case 3: if ((yPos < fieldData->getHeight() - 1) && !(fieldData->getTypeFlags(xPos, yPos + 1))) yPos++; statusFlag |= flagsEnum::Moved; break;

			}

			//check if the current position is in the field contains a hazard, set stuck flag if so
			if (fieldData->getTypeFlags(xPos, yPos) & typesEnum::hazardType)
				statusFlag |= flagsEnum::Stuck;

		}

		//update field to ensure the most up-to-date information is available
		fieldData->update(oldXPos, oldYPos);

	}

}