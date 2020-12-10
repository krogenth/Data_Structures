/*
Name:  Daniel Kelley
Class: CIS243
Date:  10/2/2019
*/

#include "field.h"
#include "AnimalInterface.h"



AnimalInterface::AnimalInterface() {



}


AnimalInterface::~AnimalInterface() {



}

void AnimalInterface::setPos(int32_t x, int32_t y) {

	xPos = x;
	yPos = y;

}

void AnimalInterface::setStatusFlag(flagsEnum status) {

	statusFlag |= status;

}

void AnimalInterface::removeStatusFlag(flagsEnum status) {

	statusFlag &= ~status;

}

uint32_t AnimalInterface::getStatusFlag() {

	return statusFlag;

}

int32_t AnimalInterface::getXPos() {

	return xPos;

}

int32_t AnimalInterface::getYPos() {

	return yPos;

}