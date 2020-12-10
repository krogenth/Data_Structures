#pragma once
/*
Name: Daniel Kelley
Date:  11/13/2019

Purpose: To create robo-intern workers
Assumptions: That you read this documentation

Error Handling: Ensure minimal exceptions can be thrown, and pass all work off to class user

Summary of Functions:
WorkerClass();						creates a default Worker object
~WorkerClass();						to kill a living Worker object
size_t getJobsDone();				returns the global amount of jobs done
size_t getbreakTime();				returns the amount of break time this worker has taken
size_t getOnClock();				returns the amount of time this worker has been on the clock
bool HaveCall();					to determine of the worker is already handling a call/job(only useful for technicians)
bool Update();						to update the worker's call/job status(updates all relevant data)
void AddJob(ItemType item_);		to give the worker a call/job to handle
bool RemoveJob(ItemType &item_);	to take away the worker's call/job
*/
#include "ItemType.h"

#define TIME_INTERVAL 900;	//seconds in 15 minutes

class WorkerClass {
public:
	//Purpose:	creates a default Worker object
	//Pre:		nothing
	//Post:		a Worker object is born
	WorkerClass();
	//Purpose:	to kill a living Worker object
	//Pre:		the Worker object exists
	//Post:		the Worker object no longer exists
	~WorkerClass();

	//Purpose:	returns the global amount of jobs done
	//Pre:		a Worker object exists
	//Post:		the global call/job counter is returned
	size_t getJobsDone();
	//Purpose:	returns the amount of break time this worker has taken
	//Pre:		a Worker object exists
	//Post:		the worker's amount of break time is returned
	size_t getbreakTime();
	//Purpose:	returns the amount of time this worker has been on the clock
	//Pre:		a Worker object exists
	//Post:		theworker's amount of clock-in time is returned
	size_t getOnClock();

	//Purpose:	to determine of the worker is already handling a call/job(only useful for technicians)
	//Pre:		a Worker object exists
	//Post:		returns true if the worker has a call/job, false otherwise
	bool HaveCall();
	//Purpose:	to update the worker's call/job status(updates all relevant data)
	//Pre:		a Worker object exists
	//Post:		returns true if the worker completed the call/job, false otherwise
	bool Update();

	//Purpose:	to give the worker a call/job to handle
	//Pre:		a Worker object exists
	//Post:		the worker now has a call/job
	void AddJob(ItemType item_);
	//Purpose:	to take away the worker's call/job
	//Pre:		a Worker object exists
	//Post:		the worker now has no call/job
	bool RemoveJob(ItemType &item_);

protected:
	ItemType *item = nullptr;	//holds whatever call/job this worker is working on
	size_t onClock = 0;			//holds whatever this worker's clock time has been
	size_t breakTime = 0;		//holds whatever this worker's brea time has been
	static size_t jobsDone;		//global counter for the amount of jobs done

	WorkerClass *this_ptr = nullptr;

};

