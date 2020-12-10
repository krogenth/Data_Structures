//Daniel Kelley
//File: WorkerClass.cpp
//Date: 11/13/2019
//Purpose: To define the Worker class to handle the calls/jobs

#include "WorkerClass.h"

size_t WorkerClass::jobsDone = 0;

WorkerClass::WorkerClass() {

	this_ptr = this;

}


WorkerClass::~WorkerClass() {

	if (item) {

		delete item;
		item = nullptr;

	}

}

size_t WorkerClass::getJobsDone() {

	return jobsDone;

}

size_t WorkerClass::getbreakTime() {

	return breakTime;

}

size_t WorkerClass::getOnClock() {

	return onClock;

}

bool WorkerClass::HaveCall() {

	return item;

}

bool WorkerClass::Update() {

	//update the worker's clock-in time
	onClock += TIME_INTERVAL;

	//worker has no call/job, so nothing to do here
	if (!item)
		return false;

	//since the worker has a call/job, update that call/job's time remaining
	item->remainingTime -= TIME_INTERVAL;

	//check to see if the call/job is complete
	if (item->remainingTime <= 0) {

		breakTime -= item->remainingTime;
		++jobsDone;

		return true;

	}

	//call/job was not completed :(
	return false;

}

void WorkerClass::AddJob(ItemType item_) {

	if(!item)
		item = new ItemType;

	*item = item_;

}

bool WorkerClass::RemoveJob(ItemType &item_) {

	//worker has no call/job, so do nothing
	if (!item)
		return false;

	//copy call/job data over to be handled by user
	item_ = *item;
	delete item;
	item = nullptr;

	return true;

}