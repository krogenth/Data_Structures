/*
Name:  Daniel Kelley
Class: CIS243
Date:  10/2/2019
*/
#include <iostream>
#include <time.h>
#if defined (_DEBUG) || defined (DEBUG)
#include <iomanip>
#include <bitset>
#endif

#include "field.h"
#include "AnimalInterface.h"
#include "Sheep.h"
#include "Sheepdog.h"

int main(int argc, char *argv[]) {

	std::ifstream inFile;
	inFile.open("data.in");
	std::string data = "";
	uint32_t fieldWidth = 0, fieldHeight = 0;
	Sheepdog *sheepdogData;
	std::streampos fieldObjectsPosition;
	uint32_t totalSheep = 0;
	Sheep *sheepData;

	std::srand(34343);

	//check to ensure the file is open, and that it is not at the end of the file
	if (!inFile.is_open() || inFile.eof())
		return 0;

	inFile >> fieldWidth >> fieldHeight;

	//check if the file failed to read data
	if (inFile.fail())
		return 0;

	//create the field, and the 4 sheepdogs
	field fieldData(fieldWidth, fieldHeight);
	sheepdogData = new Sheepdog[4];

	for (uint8_t count = 0; count < 4; count++) {

		std::string sheepdogName = "";
		std::string sheepdogType = "";
		int32_t sheepdogPos = 0;

		inFile >> sheepdogName >> sheepdogType;
		inFile >> sheepdogPos;
		sheepdogData[count].setName(sheepdogName);

		if (sheepdogType == "English") {

			sheepdogData[count].setSpeed(3);
			sheepdogData[count].setStrength(2);

		}
		else if (sheepdogType == "Sarplaninac") {

			sheepdogData[count].setSpeed(2);
			sheepdogData[count].setStrength(1);

		}
		else if (sheepdogType == "Icelandic") {

			sheepdogData[count].setSpeed(4);
			sheepdogData[count].setStrength(3);

		}
		else if (sheepdogType == "Puli") {

			sheepdogData[count].setSpeed(2);
			sheepdogData[count].setStrength(3);

		}
		else
			return 0;

		switch (sheepdogPos) {

		case 1: sheepdogData[count].setPos(0, 0); break;
		case 2: sheepdogData[count].setPos(fieldHeight - 1, 0); break;
		case 3: sheepdogData[count].setPos(0, fieldWidth - 1); break;
		case 4: sheepdogData[count].setPos(fieldHeight - 1, fieldWidth - 1); break;

		}

		fieldData.setAnimal(&sheepdogData[count]);

	}

	//set the data file to 2 bytes past it's current position(must read past 0x0D and 0x0A to get to the next line otherwise)
	inFile.seekg(2, std::ios::cur);
	//store the current data file position
	fieldObjectsPosition = inFile.tellg();

	//read each remaining line of the file
	while (std::getline(inFile, data)) {

		//check if the data is for a sheep, if so, increment the total amount of sheep
		if (data[data.length() - 1] == 'S')
			totalSheep++;

	}

	//create an array for the amount of sheep there are
	sheepData = new Sheep[totalSheep];

	//clear the state flags of the data file(previous read through set the eof and bad flags)
	inFile.clear();
	//reposition data file to the previous position
	inFile.seekg(fieldObjectsPosition);

	//re-read each remaining line of the file
	for (uint32_t count = 0; !inFile.fail(); ) {

		int32_t objectXPos = 0, objectYPos = 0;
		char objectType = '\0';

		inFile >> objectXPos >> objectYPos >> objectType;

		//check if the object's x and y are within the field's dimensions
		if ((objectXPos < 0) || (objectYPos >= fieldData.getWidth()) || (objectYPos < 0) || (objectYPos >= fieldData.getHeight()))
			return 0;

		if (objectType == 'H')
			fieldData.setTypeFlag(objectXPos, objectYPos, typesEnum::hazardType);
		else if (objectType == 'S') {

			sheepData[count].setPos(objectXPos, objectYPos);
			fieldData.setAnimal(&sheepData[count]);
			count++;

		}

	}

	//set the static sheep pointer for the sheepdogs
	sheepdogData[0].setSheep_ptr(sheepData);

	inFile.close();

	//open the output file to clear it, we want a fresh output for each run, I think
	std::ofstream outFile;
	outFile.open("results.txt");
	outFile.close();

	//game loop: 480 rounds, or no sheep remaining
	for (uint32_t count = 0; (count < 480) && (sheepData[0].getSheepLeft() > 0); count++) {

		//only for debug purposes, compile in release to remove
#if defined (_DEBUG) || defined (DEBUG)
		std::cout << count << '\t' << sheepData[0].getSheepLeft() << std::endl;
#endif

		//loop through each sheep, and call their update method
		for (uint32_t i = 0; i < sheepData[0].getNumSheep(); i++) {

			sheepData[i].update(&fieldData);

			//only for debug purposes, compile in release to remove
#if defined (_DEBUG) || defined (DEBUG)
			std::cout << "\tSheep #" << std::setw(2) << i << " status is: " << std::bitset<8>(sheepData[i].getStatusFlag()) << " and position is: " << std::setw(2) << sheepData[i].getXPos() << ',' << std::setw(2) << sheepData[i].getYPos() << '\n';
#endif

		}

		//loop through each sheepdog, and call their update method
		for (uint32_t i = 0; i < 4; i++) {

			sheepdogData[i].update(&fieldData);

			//only for debug purposes, compile in release to remove
#if defined (_DEBUG) || defined (DEBUG)
			std::cout << "\tDog   #" << std::setw(2) << i << " status is: " << std::bitset<8>(sheepdogData[i].getStatusFlag()) << " and position is: " << std::setw(2) << sheepdogData[i].getXPos() << ',' << std::setw(2) << sheepdogData[i].getYPos() << " and rescued: " << sheepdogData[i].getSheepRescued() << '\n';
#endif

		}

		//iterate through sheep, and remove the moved bitflag from each
		for (uint32_t i = 0; i < sheepData[0].getNumSheep(); i++)
			sheepData[i].removeStatusFlag(flagsEnum::Moved);

	}

	Sheepdog bestDog;

	for (uint32_t i = 0; i < 3; i++) {

		bestDog = sheepdogData[i];

		for (uint32_t j = i + 1; j < 4; j++) {

			if (bestDog.getSheepRescued() < sheepdogData[j].getSheepRescued()) {

				sheepdogData[i] = sheepdogData[j];
				sheepdogData[j] = bestDog;

				bestDog = sheepdogData[i];

			}

		}

	}

	std::cout << "1st place: " << sheepdogData[0].getName() << " with " << sheepdogData[0].getSheepRescued() << " rescued sheep!\n";
	std::cout << "2nd place: " << sheepdogData[1].getName() << " with " << sheepdogData[1].getSheepRescued() << " rescued sheep!\n";
	std::cout << "3rd place: " << sheepdogData[2].getName() << " with " << sheepdogData[2].getSheepRescued() << " rescued sheep!\n";
	std::cout << "4th place: " << sheepdogData[3].getName() << " with " << sheepdogData[3].getSheepRescued() << " rescued sheep!\n";

	delete[]sheepData;
	delete[]sheepdogData;

	std::cout << "Please press enter to continue...";
	std::cin.get();

}