/*
Name: Daniel Kelley
Date:  10/2/2019

Purpose: To handle all functionality of a sheep on the field
Assumptions: an x and y position was eventually passed to the object

Error Handling: position boundaries with respect to the field dimensions

Summary of Functions:
public AnimalInterface()						creates a default AnimalInterface object
public ~AnimalInterface()						to kill a living AnimalInterface

public setPos(int32_t x, int32_t y)				to set the x and y coordinates of the AnimalInterface derived object within the field dimensions
public typesEnum getType()						to return the type this object is(unknown)
public void setStatusFlag(flagsEnum status)		to set a specific flag of an AnimalInterface derived object's bitflag(see flagsEnum)
public removeStatusFlag(flagsEnum status)		removes a specific flag of an AnimalInterface derived object's bitflag(see flagsEnum)
public uint32_t getStatusFlag()					returns the current bitflag of the AnimalInterface derived object
public int32_t getXPos()						returns the AnimalInterface dervied object's x position
public int32_t getYPos()						returns the AnimalInterface dervied object's y position
public virtual void update(field *fieldData)	to update the AnimalInterface derived object, if possible
*/
#pragma once
#include <cinttypes>
#include <cstdlib>

class field;

//Purpose:	To give the AnimalInterface dervied objects a named value for their bitflags
enum flagsEnum {
	Stuck    = 0b00000001,
	Catching = 0b00000010,
	Rescued  = 0b00000100,
	Moved    = 0b00001000,
	Aligning = 0b00010000
};

class AnimalInterface {

public:
	//Purpose:	creates a default AnimalInterface object
	//Pre:		nothing
	//Post:		an AnimalInterface is born
	AnimalInterface();
	//Purpose:	to kill a living AnimalInterface
	//Pre:		the AnimalInterface exists
	//Post:		the AnimalInterface no longer exists
	~AnimalInterface();

	//Purpose:	to set the x and y coordinates of the AnimalInterface dervied object within the field dimensions
	//Pre:		nothing
	//Post:		a sheep is born
	void setPos(int32_t /*IN*/x, int32_t /*IN*/y);

	//Purpose:	to return the type this object is(unknown)
	//Pre:		an AnimalInterface derived object exists
	//Post:		the object type is returned
	virtual typesEnum getType() = 0;

	//Purpose:	to set a specific flag of an AnimalInterface derived object's bitflag(see flagsEnum)
	//Pre:		an AnimalInterface derived object exists
	//Post:		nothing
	void setStatusFlag(flagsEnum /*IN*/status);
	//Purpose:	removes a specific flag of an AnimalInterface derived object's bitflag(see flagsEnum)
	//Pre:		an AnimalInterface derived object exists
	//Post:		nothing
	void removeStatusFlag(flagsEnum /*IN*/status);
	//Purpose:	returns the current bitflag of the AnimalInterface derived object
	//Pre:		an AnimalInterface derived object exists
	//Post:		the current bitflag is returned
	uint32_t getStatusFlag();

	//Purpose:	returns the AnimalInterface dervied object's x position
	//Pre:		an AnimalInterface derived object exists
	//Post:		the current x position is returned
	int32_t getXPos();
	//Purpose:	returns the AnimalInterface dervied object's y position
	//Pre:		an AnimalInterface derived object exists
	//Post:		the current y position is returned
	int32_t getYPos();

	//Purpose:	to update the AnimalInterface derived object, if possible
	//Pre:		an AnimalInterface dervied object exists
	//Post:		nothing
	virtual void update(field /*IN*/*fieldData) = 0;

protected:
	int32_t statusFlag = 0;		//stores the bitflags of the AnimalInterface dervied object
	int32_t xPos = 0, yPos = 0;

};