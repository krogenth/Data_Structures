/*
Name: Daniel Kelley
Date:  10/2/2019

Purpose: To handle all functionality of a sheep on the field
Assumptions: an x and y position was eventually passed to the object

Error Handling: position boundaries with respect to the field dimensions

Summary of Functions:
public Sheep()								creates a default sheep object
public Sheep(int32_t x, int32_t y)			creates a non-default sheep object
public ~Sheep()								to return the total number of sheep there are/were

public uint32_t getNumSheep()				to return the total number of sheep there are/were
public uint32_t getSheepLeft()				to return the remaining number of sheep there are
public typesEnum getType()					to return the type this object is(sheep)
public void removeSheep(field *fieldData)	removes a sheep from play
public void update(field *fieldData)		to update the sheep object, if possible
*/
#pragma once

class field;
class AnimalInterface;

class Sheep : public AnimalInterface {

public:
	//Purpose:	creates a default sheep object
	//Pre:		nothing
	//Post:		a sheep is born
	Sheep();
	//Purpose:	creates a non-default sheep object
	//Pre:		there is an x and y to give the sheep
	//Post:		a sheep is born
	Sheep(int32_t /*IN*/x, int32_t /*IN*/y);
	//Purpose:	to kill a living sheep
	//Pre:		the sheep exists
	//Post:		the sheep no longer exists
	~Sheep();

	//Purpose:	to return the total number of sheep there are/were
	//Pre:		an instance of a sheep object exists
	//Post:		the total number of sheep is returned
	uint32_t getNumSheep();
	//Purpose:	to return the remaining number of sheep there are
	//Pre:		an instance of a sheep object exists
	//Post:		the remaining number of sheep is returned
	uint32_t getSheepLeft();

	//Purpose:	to return the type this object is(sheep)
	//Pre:		a sheep object exists
	//Post:		the object type(sheep) is returned
	typesEnum getType();

	//Purpose:	removes a sheep from play
	//Pre:		a sheep object exists
	//Post:		the sheep object is no longer in play
	void removeSheep(field /*IN*/*fieldData);

	//Purpose:	to update the sheep object, if possible
	//Pre:		a sheep object exists
	//Post:		nothing
	void update(field /*IN*/*fieldData);

protected:
	static uint32_t totalSheep;
	static uint32_t sheepLeft;
	typesEnum type = typesEnum::SheepType;

};