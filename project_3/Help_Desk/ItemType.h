#pragma once

#include <ctime>

typedef size_t KeyType;

//enum to handle the different call severities
enum CallLevelEnum {

	TIER1 = 0x01,
	TIER2 = 0x02,
	TIER3 = 0x03

};

//Struct that contains contents for an item:
struct ItemType
{
	//The key identifier of an item:
	KeyType key = 0;

	CallLevelEnum level = CallLevelEnum::TIER1;

	time_t remainingTime = 0;
	time_t requiredTime = 0;
	time_t startTime = 0;
	time_t endTime = -1;

};
