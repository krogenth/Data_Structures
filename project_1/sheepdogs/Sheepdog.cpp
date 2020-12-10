/*
Name:  Daniel Kelley
Class: CIS243
Date:  10/2/2019
*/
#include "field.h"
#include "AnimalInterface.h"
#include "Sheep.h"
#include "Sheepdog.h"

Sheep *Sheepdog::sheep_ptr = nullptr;

Sheepdog::Sheepdog() {



}

Sheepdog::~Sheepdog() {



}

void Sheepdog::setName(std::string sheepdogName) {

	name = sheepdogName;

}

std::string Sheepdog::getName() {

	return name;

}

void Sheepdog::setStrength(int8_t str) {

	strength = str;
	currStrength = str;

}

void Sheepdog::setSpeed(int8_t spd) {

	moveSpeed = spd;

}

typesEnum Sheepdog::getType() {

	return type;

}

uint32_t Sheepdog::getSheepRescued() {

	return sheepRescued;

}

void Sheepdog::setSheep_ptr(Sheep *sheep) {

	sheep_ptr = sheep;

}

void Sheepdog::update(field *fieldData) {

	//store the current position before updating, to allow for faster field updating
	int32_t oldXPos = xPos, oldYPos = yPos;

	//check to ensure there is a targetted sheep, and if so, if the sheep has been rescued
	if (targetSheep && (targetSheep->getStatusFlag() & flagsEnum::Rescued)) {

		//reset sheepdog flag, remove the targetted sheep, reset the strength counter, and clear the sheepdog's path of traversals
		statusFlag &= ~flagsEnum::Catching;
		targetSheep = nullptr;
		currStrength = strength;
		path.clear();

	}

	//check if the sheepdog is not currently attempting to catch a stuck sheep
	if (!(statusFlag & flagsEnum::Catching)) {

		//check if there is no current targetted sheep, if not, start looking for one
		if (targetSheep == nullptr) {

			int32_t distance = INT32_MAX;
			//store the sheep array pointer to a local variable to be able to traverse the sheep array
			Sheep *currSheep = sheep_ptr;

			//loop through for the number of sheep that are in the array
			for (uint32_t i = 0; i < sheep_ptr->getNumSheep(); i++) {

				//check if the current sheep is not rescued, and that the current sheep's x position is closer than the currently stored distance
				if (!(currSheep->getStatusFlag() & flagsEnum::Rescued) && (distance > std::abs(currSheep->getXPos() - xPos))) {

					distance = std::abs(currSheep->getXPos() - xPos);
					targetSheep = currSheep;

				}

				//increment the current sheep pointer to the next sheep in the array
				currSheep++;

			}

			//check if there is not a sheep targetted, if true, exit the method, there are no sheep left
			if (targetSheep == nullptr)
				return;

			//call BFS() to search for the appropriate path to align the sheepdog's x position with the sheep's x position
			BFS(fieldData, { targetSheep->getXPos(), yPos });
			//set the sheepdog's bitflag to aligning
			statusFlag |= flagsEnum::Aligning;

		}
		//check if the aligning flag is not set, and if the currently targetted sheep's move flag has been set
		else if (!(statusFlag & flagsEnum::Aligning) && (targetSheep->getStatusFlag() & flagsEnum::Moved))
			//recall BFS() to recalculate the appropriate path to reach the targetted sheep
			BFS(fieldData, { targetSheep->getXPos(), targetSheep->getYPos() });

		//loop until the current speed counter is equal to the maximum speed counter of the sheepdog
		for (currMoveSpeed = 0; currMoveSpeed < moveSpeed; currMoveSpeed++) {

			//check if the sheepdog's aligning bitflag is set, and if the sheepdog's path is empty
			if ((statusFlag & flagsEnum::Aligning) && path.empty()) {

				//remove the aligning bitflag, the sheepdog has reached its alignment position
				statusFlag &= ~flagsEnum::Aligning;

				//call BFS() to calculate the appropriate path for the sheepdog to take to the currently targetted sheep, if no path could be calculated, exit the loop, the sheepdog has reached its target
				//yes, I realize this is a horrible idea
				if (!BFS(fieldData, { targetSheep->getXPos(), targetSheep->getYPos() }))
					break;

			}

			//check if the path is empty, if so, exit the loop, you have reached your destination
			if (path.empty())
				break;

			//grab the next field tile x and y coordinates for the sheepdog to move to in the path, remove that tile from the path
			xPos = path.front().first;
			yPos = path.front().second;
			path.pop_front();

		}

		//check if the current speed counter is not equal to the maximum speed counter
		if (currMoveSpeed != moveSpeed) {

			//check if the field tile the currently targetted sheep is in is a hazard
			if ((fieldData->getTypeFlags(targetSheep->getXPos(), targetSheep->getYPos()) & typesEnum::hazardType)) {

				//set the sheepdog's catching bitflag, and decrement the sheepdog's current strength counter
				statusFlag |= flagsEnum::Catching;
				currStrength--;

			}
			else {

				//set the targetted sheep's rescued bitflag, remove the targetted sheep from the field, remove the targetted sheep's pointer, and increment the amount of sheep rescued
				targetSheep->setStatusFlag(flagsEnum::Rescued);
				targetSheep->removeSheep(fieldData);
				targetSheep = nullptr;
				sheepRescued++;

			}

		}

	}
	else {

		//check if the current strength counter is 0
		if (currStrength == 0) {

			//set the targetted sheep's rescued bitflag, remove the sheepdog's catching bitflag, remove the targetted sheep from the field, remove the targetted sheep's pointer, and increment the amount of sheep rescued, and reset the current strength counter
			targetSheep->setStatusFlag(flagsEnum::Rescued);
			statusFlag &= ~flagsEnum::Catching;
			targetSheep->removeSheep(fieldData);
			targetSheep = nullptr;
			sheepRescued++;
			currStrength = strength;

		}
		else
			currStrength--;

	}

	//update field to ensure the most up-to-date information is available
	fieldData->update(oldXPos, oldYPos);

}

bool Sheepdog::BFS(field *fieldData, std::pair<uint32_t, uint32_t> targetPos) {

	//grab the field's width and height, mostly for the width, because it will be used a lot
	uint32_t fieldWidth = fieldData->getWidth(), fieldHeight = fieldData->getHeight();
	//clear the sheepdog's path, it was outdated, and it needs to be emptied to ensure there are no issues
	path.clear();

	//use a vector to store a field's worth of pathStruct's, to flag which have been visited and from which tile
	//this was originally a dynamic array, but it refused to assign values after so many iterations
	std::vector<pathStruct> visit(fieldWidth * fieldHeight);
	//create a queue to store visited tiles to check their adjacent tiles
	std::list<std::pair<uint32_t, uint32_t>> queue;

	//set the sheepdog's current position as visited, and visited from the sheepdog's position
	visit[xPos + (fieldWidth * yPos)].visited = true;
	visit[xPos + (fieldWidth * yPos)].from = { xPos, yPos };

	//add the sheepdog's position to the queue
	queue.push_back({ xPos, yPos });

	//loop while there are more tiles in the queue to check
	while (!queue.empty()) {

		//check if the current position in the queue is the targetted position, if so, exit the loop, we found 'em boys
		if (queue.front() == targetPos)
			break;

		//check to ensure there is a position to the west of the current position, and that that position has not been visited before
		if ((queue.front().first > 0) && !visit[(queue.front().first - 1) + (fieldWidth * queue.front().second)].visited) {

			//set the new position to visited, and from the current position in the queue
			visit[(queue.front().first - 1) + (fieldWidth * queue.front().second)].visited = true;
			visit[(queue.front().first - 1) + (fieldWidth * queue.front().second)].from = { queue.front().first, queue.front().second };

			//check if there is anything on that field tile, if so, avoid it, otherwise, add it to the queue
			if (!fieldData->getTypeFlags(queue.front().first - 1, queue.front().second))
				queue.push_back({ queue.front().first - 1, queue.front().second });

		}

		//check to ensure there is a position to the north of the current position, and that that position has not been visited before
		if ((queue.front().second > 0) && !visit[queue.front().first + (fieldWidth * (queue.front().second - 1))].visited) {

			//set the new position to visited, and from the current position in the queue
			visit[queue.front().first + (fieldWidth * (queue.front().second - 1))].visited = true;
			visit[queue.front().first + (fieldWidth * (queue.front().second - 1))].from = { queue.front().first, queue.front().second };

			//check if there is anything on that field tile, if so, avoid it, otherwise, add it to the queue
			if (!fieldData->getTypeFlags(queue.front().first, queue.front().second - 1))
				queue.push_back({ queue.front().first, queue.front().second - 1 });

		}

		//check to ensure there is a position to the east of the current position, and that that position has not been visited before
		if ((queue.front().first < fieldWidth - 1) && !visit[(queue.front().first + 1) + (fieldWidth * queue.front().second)].visited) {

			//set the new position to visited, and from the current position in the queue
			visit[(queue.front().first + 1) + (fieldWidth * queue.front().second)].visited = true;
			visit[(queue.front().first + 1) + (fieldWidth * queue.front().second)].from = { queue.front().first, queue.front().second };

			//check if there is anything on that field tile, if so, avoid it, otherwise, add it to the queue
			if (!fieldData->getTypeFlags(queue.front().first + 1, queue.front().second))
				queue.push_back({ queue.front().first + 1, queue.front().second });

		}

		//check to ensure there is a position to the south of the current position, and that that position has not been visited before
		if ((queue.front().second < fieldHeight - 1) && !visit[queue.front().first + (fieldWidth * (queue.front().second + 1))].visited) {

			//set the new position to visited, and from the current position in the queue
			visit[queue.front().first + (fieldWidth * (queue.front().second + 1))].visited = true;
			visit[queue.front().first + (fieldWidth * (queue.front().second + 1))].from = { queue.front().first, queue.front().second };

			//check if there is anything on that field tile, if so, avoid it, otherwise, add it to the queue
			if (!fieldData->getTypeFlags(queue.front().first, queue.front().second + 1))
				queue.push_back({ queue.front().first, queue.front().second + 1 });

		}

		queue.pop_front();

	}

	//check if the targetted position has a from position set, if not, the there is no path
	if (visit[targetPos.first + (fieldWidth * targetPos.second)].from.first == UINT32_MAX || visit[targetPos.first + (fieldWidth * targetPos.second)].from.second == UINT32_MAX)
		return false;

	//traverse back starting from the targetted position, to the sheepdog's current position, until the next from position is the sheepdog's current position
	//we do not want to store the sheepdog's current position into the path, so we stop when we get there
	for (std::pair<uint32_t, uint32_t> target = { targetPos.first, targetPos.second }; !((xPos == visit[target.first + (fieldWidth * target.second)].from.first) && (yPos == visit[target.first + (fieldWidth * target.second)].from.second));) {

		//set the current target position equal to the next from position
		target = { visit[target.first + (fieldWidth * target.second)].from.first, visit[target.first + (fieldWidth * target.second)].from.second };
		//add the current target position to the front of the path
		//we are traversing backwards, so each current target position we are at, is the reverse order the sheepdog is suppose to move in
		path.push_front(target);

	}

	if (path.empty())
		return false;
	return true;

}