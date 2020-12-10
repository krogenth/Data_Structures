/*
Name: Daniel Kelley
Date:  10/2/2019

Purpose: to read from a file, hopefully containing intergers, and determining if they are divisible by 3, even, or odd, and output a string in relation in the reverse order it was read.

Assumptions: None

Error Handling: File status checks

Summary of Functions:
public field(int32_t x, int32_t y)									creates a default field object
public ~field()														to kill a living field object

public int32_t getWidth()											returns the field's width
public int32_t getHeight()											returns the field's height
public void setTypeFlag(uint32_t x, uint32_t y, typesEnum type)		to set a specific bitflag for a field tile
public uint32_t getTypeFlags(uint32_t x, uint32_t y)				to set an AnimalInterface pointer and bitflag into a field tile
public AnimalInterface * getOccupier(int32_t x, int32_t y)			returns the pointer to a field tile's AnimalInterface object
public void setAnimal(AnimalInterface *animal)						to set an AnimalInterface pointer and bitflag into a field tile
public void removeAnimal(AnimalInterface *animal)					to remove an AnimalInterface pointer and bitflag from a field tile
public void update(int32_t x, int32_t y)							to update a specific AnimalInterface object's pointer and bitflag in the field
private void outputMap()
*/
#pragma once
#include <cinttypes>
#include <fstream>

class AnimalInterface;
class Sheep;
class Sheepdog;

//Purpose:	To give the field tiles a named value for their bitflags
enum typesEnum {

	SheepType = 0x01,
	SheepdogType = 0x02,
	hazardType = 0x04

};

//Purpose:	To contain the necessary information about a given field tile
struct fieldStruct {

	uint32_t typeFlags = 0;
	AnimalInterface *occupier_ptr = nullptr;

};

class field {

public:
	//Purpose:	creates a default field object
	//Pre:		nothing
	//Post:		a field is born
	field(int32_t /*IN*/x, int32_t /*IN*/y);
	//Purpose:	to kill a living field object
	//Pre:		a field object exists
	//Post:		the field object no longer exists
	~field();

	//Purpose:	returns the field's width
	//Pre:		a field object exists
	//Post:		the field's width is returned
	int32_t getWidth();
	//Purpose:	returns the field's height
	//Pre:		a field object exists
	//Post:		the field's height is returned
	int32_t getHeight();

	//Purpose:	to set a specific bitflag for a field tile
	//Pre:		a field object exists
	//Post:		nothing
	void setTypeFlag(int32_t /*IN*/x, int32_t /*IN*/y, typesEnum /*IN*/type);
	//Purpose:	returns a specific field tile's bitflag
	//Pre:		a field object exists
	//Post:		the field tile's bitflag is returned
	uint32_t getTypeFlags(int32_t /*IN*/x, int32_t /*IN*/y);

	//Purpose:	returns the pointer to a field tile's AnimalInterface object
	//Pre:		a field object exists
	//Post:		the field tile's AnimalInterface object pointer is returned
	AnimalInterface * getOccupier(int32_t /*IN*/x, int32_t /*IN*/y);

	//Purpose:	to set an AnimalInterface pointer and bitflag into a field tile
	//Pre:		a field object and AnimalInterface object exist
	//Post:		nothing
	void setAnimal(AnimalInterface /*IN*/*animal);
	//Purpose:	to remove an AnimalInterface pointer and bitflag from a field tile
	//Pre:		a field object and AnimalInterface object exist
	//Post:		nothing
	void removeAnimal(AnimalInterface /*IN*/*animal);
	//Purpose:	to update a specific AnimalInterface object's pointer and bitflag in the field
	//Pre:		a field object and AnimalInterface object exist
	//Post:		nothing
	void update(int32_t /*IN*/x, int32_t /*IN*/y);

private:
	//Purpose:	to output the current field tiles
	//Pre:		a field object exists and was updated
	//Post:		nothing
	void outputMap();

	int32_t width = 0, height = 0;
	fieldStruct *fieldMap = nullptr;

};