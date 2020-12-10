//Daniel Kelley
//File: source.cpp
//Date: 11/13/2019
//Purpose: To do all the crazy stuff to finish this project :)

#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <stdlib.h>
#include <fstream>

#include "StackClass.h"
#include "QueueClass.h"
#include "ItemType.h"
#include "WorkerClass.h"

//we are working in seconds, so we need these conversions
const size_t SEC_IN_HOUR = 3600;
const size_t SEC_IN_MIN = 60;

//Purpose:	to print out completed calls/jobs to the results.txt file
//Pre:		the call/job was completed
//Post:		the call/job is outputted to results.txt
void printJob(ItemType &item_);

size_t main() {

	std::ofstream output("results.txt");
	output.close();

	//look, it wanted Monday at 8:00AM, so I am giving it Monday at 8:00AM
	time_t beginTime = 1573459200;	// 11/11/2019 @ 8:00am (UTC)
	time_t currTime = beginTime;

	ItemType call;
	size_t callCount = 0;
	size_t numCalls = 4;
	size_t currReps = 0;

	Stack callStack;
	QueueClass callQueue;
	QueueClass completeCalls;

	WorkerClass reps[3];
	WorkerClass tech;

	std::srand(123);

	//Begin creating initial calls/jobs
	for (size_t i = 0; i < numCalls; i++) {

		call.key = ++callCount;
		call.startTime = currTime;

		size_t callType = std::rand() % 10;

		if (callType < 6) {

			call.level = CallLevelEnum::TIER1;
			call.remainingTime = (std::rand() % 15 + 10) * SEC_IN_MIN;

		}
		else if (callType < 9) {

			call.level = CallLevelEnum::TIER2;
			call.remainingTime = (std::rand() % 25 + 20) * SEC_IN_MIN;

		}
		else {

			call.level = CallLevelEnum::TIER3;
			call.remainingTime = (std::rand() % 180 + 60) * SEC_IN_MIN;

		}

		call.requiredTime = call.remainingTime;
		callQueue.EnQueue(call);

	}

	//we need to get the current UTC time, we use gmtime to get the formatted date/time(for start of simulation)
	tm *dateTime = gmtime(&currTime);

	for (size_t i = 0; i < 432; i++) {

		//check what hour in the day it is to determine how many calls have happened in this iterations(15 mins)
		if (dateTime->tm_hour >= 9 && dateTime->tm_hour < 16)
			numCalls = std::rand() % 3 + 1;
		else
			numCalls = std::rand() % 2;

		//create the number of calls just calculated
		for (size_t j = 0; j < numCalls; j++) {

			call.key = ++callCount;
			call.startTime = currTime;
				
			size_t callType = std::rand() % 10;

			if (callType < 6) {

				call.level = CallLevelEnum::TIER1;
				call.remainingTime = (std::rand() % 15 + 10) * SEC_IN_MIN;

			}
			else if (callType < 9) {

				call.level = CallLevelEnum::TIER2;
				call.remainingTime = (std::rand() % 25 + 20) * SEC_IN_MIN;

			}
			else {

				call.level = CallLevelEnum::TIER3;
				call.remainingTime = (std::rand() % 180 + 60) * SEC_IN_MIN;

			}

			call.requiredTime = call.remainingTime;
			callQueue.EnQueue(call);

		}

		//we need to check the technician first, because any iteration that would result in a tier 3 going to the stack, means that iteration is already over.
		if (!tech.HaveCall() && callStack.Top(call)) {

			tech.AddJob(call);
			callStack.Pop();

		}

		//update the technician
		if (tech.Update()) {

			//remove the tech's call/job, give the call/job it's end time, and throw it around to completedness
			tech.RemoveJob(call);
			call.endTime = currTime + TIME_INTERVAL - call.remainingTime;
			completeCalls.EnQueue(call);
			printJob(call);

		}

		//check what time of day it is again, to see how many reps we have right now
		if (dateTime->tm_hour >= 8 && dateTime->tm_hour < 18)
			currReps = 3;
		else
			currReps = 2;

		//begin running through the reps
			//we must grab each reps call/job first, THEN update all reps
		for (size_t j = 0; j < currReps; j++) {

			try {

				reps[j].AddJob(callQueue.Retrieve());
				callQueue.DeQueue();

			}
			catch (const std::exception &e) {



			}

		}

		//now we update each rep
		for (size_t j = 0; j < currReps; j++) {

			if (!reps[j].Update()) {

				if (reps[j].RemoveJob(call)) {

					if (call.level == CallLevelEnum::TIER3) {
						try {

							//attempt to put the tier 3 on the stack, if no-go, throw into the queue
							callStack.Push(call);

						}
						catch (const std::exception &e) {

							callQueue.EnQueue(call);

						}

					}
					else
						callQueue.EnQueue(call);

				}

			}
			else {

				//remove the rep's call/job, give the call/job it's end time, and throw it around to completedness
				reps[j].RemoveJob(call);
				call.endTime = currTime + TIME_INTERVAL - call.remainingTime;
				completeCalls.EnQueue(call);
				printJob(call);

			}

		}

		//update the simulation timing
		currTime += TIME_INTERVAL;

		//regrab the formatted timing
		dateTime = gmtime(&currTime);

	}

	//we need a bunch of variables to store some data about the calls/jobs, and the interns too I guess
	size_t jobsComplete[3] = {};
	size_t jobsIncomplete[3] = {};
	time_t jobsAverageTime[3] = {};
	
	float repProductivity = 0.0f;
	float techProductivity = 0.0f;

	//begine reading all the completed jobs data and sort accordionly
	try {

		while (true) {

			call = completeCalls.Retrieve();
			
			switch (call.level) {

			case CallLevelEnum::TIER1: jobsComplete[0]++; jobsAverageTime[0] += (call.endTime - call.startTime); break;
			case CallLevelEnum::TIER2: jobsComplete[1]++; jobsAverageTime[1] += (call.endTime - call.startTime); break;
			case CallLevelEnum::TIER3: jobsComplete[2]++; jobsAverageTime[2] += (call.endTime - call.startTime); break;

			}

			completeCalls.DeQueue();

		}

	}
	catch (const std::exception &e) {



	}

	//calculate the average time for the call/job severity tiers
	for (size_t i = 0; i < 3; i++)
		jobsAverageTime[i] /= jobsComplete[i];

	//attempt to read all the jobs incompleted in the queue
	try {

		while (true) {

			call = callQueue.Retrieve();

			switch (call.level) {

			case CallLevelEnum::TIER1: jobsIncomplete[0]++; break;
			case CallLevelEnum::TIER2: jobsIncomplete[1]++; break;
			case CallLevelEnum::TIER3: jobsIncomplete[2]++; break;

			}

			completeCalls.DeQueue();

		}

	}
	catch (const std::exception &e) {



	}

	//attempt to read all the jobs incompleted in the stack
	while (callStack.Top(call)) {

		jobsIncomplete[2]++;
		callStack.Pop();

	}

	//output all the statistics
	std::cout << "Jobs completed: " << tech.getJobsDone() << '\n';
	for (size_t i = 0; i < 3; i++) {

		std::cout << "\tTier " << (i + 1) << ": ";
		
		if (tech.getJobsDone() == 0)
			std::cout << "0%\n";
		else
			std::cout << (((float)jobsComplete[i] * 100) / (float)tech.getJobsDone()) << "%\n";

	}

	std::cout << "Jobs incomplete: " << (jobsIncomplete[0] + jobsIncomplete[1] + jobsIncomplete[2]) << '\n';
	for (size_t i = 0; i < 3; i++) {

		std::cout << "\tTier " << (i + 1) << ": ";
		
		if ((jobsIncomplete[0] + jobsIncomplete[1] + jobsIncomplete[2]) == 0)
			std::cout << "0%\n";
		else
			std::cout << (((float)jobsIncomplete[i] * 100) / ((float)jobsIncomplete[0] + (float)jobsIncomplete[1] + (float)
				jobsIncomplete[2])) << '\n';

	}

	for (size_t i = 0; i < 3; i++) {

		std::cout << "Job Severity " << (i + 1) << " average time: " << (jobsAverageTime[i] / SEC_IN_HOUR) << ':';
		if (((jobsAverageTime[i] - ((jobsAverageTime[i] / SEC_IN_HOUR) * SEC_IN_HOUR)) / SEC_IN_MIN) < 10)
			std::cout << '0';
		std::cout << ((jobsAverageTime[i] - ((jobsAverageTime[i] / SEC_IN_HOUR) * SEC_IN_HOUR)) / SEC_IN_MIN) << '\n';

	}

	for (size_t i = 0; i < 3; i++)
		repProductivity += (((reps[i].getOnClock() - reps[i].getbreakTime()) * 100) / reps[i].getOnClock());
	repProductivity /= 3;

	std::cout << "Representivity productivity: " << repProductivity << "%\n";
	std::cout << "Technician productivity: " << (((tech.getOnClock() - tech.getbreakTime()) * 100) / tech.getOnClock()) << "%\n";

	std::cin.get();

	return EXIT_SUCCESS;

}

void printJob(ItemType &item_) {

	//we need to output everything at the end, so open in appending
	std::ofstream output("results.txt", std::ios::app);

	tm *dateTime;

	output << "Job #" << item_.key << '\n';

	dateTime = gmtime(&item_.startTime);
	output << "Job submitted at: " << (((dateTime->tm_wday - 1) * 24) + dateTime->tm_hour) << ':';
	if (dateTime->tm_min < 10)
		output << '0';
	output << dateTime->tm_min << '\n';

	output << "Job severity: " << item_.level << '\n';

	dateTime = gmtime(&item_.endTime);
	output << "Job completed at: " << (((dateTime->tm_wday - 1) * 24) + dateTime->tm_hour) << ':';
	if (dateTime->tm_min < 10)
		output << '0';
	output << dateTime->tm_min << '\n';

	output << "Job worked on " << (((float)item_.requiredTime * 100) / ((float)item_.endTime - (float)item_.startTime)) << "% of the time.\n";
	output << "Job idled on " << (((((float)item_.endTime - (float)item_.startTime) - (float)item_.requiredTime) * 100) / ((float)item_.endTime - (float)item_.startTime)) << "% of the time.\n\n";

}