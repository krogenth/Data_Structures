/*
Name: Daniel Kelley
Date:  10/2/2019

Purpose: To handle all functionality of a sheepdog on the field
Assumptions: an x and y position, strength, and speed, were eventually passed to the object

Error Handling: position boundaries with respect to the field dimensions

Summary of Functions:
public Sheepdog()															creates a default sheepdog object
public ~Sheepdog()															to kill a living sheepdog

public void setName(std::string sheepdogName)								to set the name of the sheepdog
public std::string getName()												returns the name of the sheepdog
public void setStrength(int8_t str)											to set the strength turn amount of the sheepdog to rescue a sheep from a hazard
public void setSpeed(int8_t spd)											to set the amount of movements the sheepdog can perform per turn
public typesEnum getType()													to return the type this object is(sheepdog)
public uint32_t getSheepRescued()											returns the current number of sheep rescued by a sheepdog object
public void setSheep_ptr(Sheep *sheep)										to set the address of the sheep array for all sheepdog objects to reference
public virtual void update(field *fieldData)								to update the sheepdog object, if possible
private bool BFS(field *fieldData, std::pair<uint32_t, uint32_t> targetPos)	to create a list of paired coordinates for a sheepdog object to traverse to a targetted position
*/
#pragma once
#include <string>
#include <list>
#include <utility>
#include <fstream>
#include <assert.h>
#include <vector>

class field;
class AnimalInterface;
class Sheep;

//Purpose:	stores necessary information for BFS() to properly traverse the field, and recreate the path to the targetted location, if possible
struct pathStruct {

	bool visited = false;
	std::pair<uint32_t, uint32_t> from = { UINT32_MAX, UINT32_MAX };

};

class Sheepdog : public AnimalInterface {

public:
	//Purpose:	creates a default sheepdog object
	//Pre:		nothing
	//Post:		a sheepdog is born
	Sheepdog();
	//Purpose:	to kill a living sheepdog
	//Pre:		the sheepdog exists
	//Post:		the sheepdog no longer exists
	~Sheepdog();

	//Purpose:	to set the name of the sheepdog
	//Pre:		a sheepdog object exists
	//Post:		the sheepdog is given a name
	void setName(std::string /*IN*/sheepdogName);
	//Purpose:	returns the name of the sheepdog
	//Pre:		a sheepdog object exists
	//Post:		the sheepdog's name is returned
	std::string getName();

	//Purpose:	to set the strength turn amount of the sheepdog to rescue a sheep from a hazard
	//Pre:		a sheepdog object exists
	//Post:		nothing
	void setStrength(int8_t /*IN*/str);
	//Purpose:	to set the amount of movements the sheepdog can perform per turn
	//Pre:		a sheepdog object exists
	//Post:		nothing
	void setSpeed(int8_t /*IN*/spd);

	//Purpose:	to return the type this object is(sheepdog)
	//Pre:		a sheepdog object exists
	//Post:		the object type(sheep) is returned
	typesEnum getType();
	//Purpose:	returns the current number of sheep rescued by a sheepdog object
	//Pre:		a sheepdog object exists
	//Post:		the number of sheep rescued by a sheepdog object is returned
	uint32_t getSheepRescued();

	//Purpose:	to set the address of the sheep array for all sheepdog objects to reference
	//Pre:		a sheep object and sheepdog object exist
	//Post:		nothing
	void setSheep_ptr(Sheep /*IN*/*sheep);

	//Purpose:	to update the sheepdog object, if possible
	//Pre:		a sheepdog object exists
	//Post:		nothing
	virtual void update(field /*IN*/*fieldData);

protected:
	//Purpose:	to create a list of paired coordinates for a sheepdog object to traverse to a targetted position
	//Pre:		a sheepdog object exists, and has a targetted position within the field
	//Post:		a list of {x, y} tiles is rewritten for the sheepdog object to follow to targetted position
	bool BFS(field /*IN*/*fieldData, std::pair<uint32_t, uint32_t> /*IN*/targetPos);

	int8_t strength = 0, currStrength = 0;
	int8_t moveSpeed = 0, currMoveSpeed = 0;
	uint32_t sheepRescued = 0;
	typesEnum type = typesEnum::SheepdogType;
	Sheep *targetSheep = nullptr;					//stores the currently targetted sheep's pointer
	static Sheep *sheep_ptr;						//statically stores the pointer to the first sheep in the sheep array, so all sheepdog's can access the sheep array
	std::string name = "Bjorn";
	std::list<std::pair<uint32_t, uint32_t>> path;	//stores a list of paired x and y coordinates for the sheepdog to traverse to reach a specific location

};