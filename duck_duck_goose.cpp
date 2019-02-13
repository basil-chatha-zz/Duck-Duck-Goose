#include "duck_duck_goose.h"
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>

void simulateDDGRound(GameData * gameData, std::ostream & output) {
	int m = rand() % (4 * (int) (gameData->playerList).size());
	int goose = (gameData->playerList).get((size_t) m);

	//going around the circle
	for(int i = 0; i <= m; i++) {
		int curPlayerID = (gameData->playerList).get((size_t) i);
		if((int) i == m) output << curPlayerID << " is a Goose!\n";
		else output << curPlayerID << " is a Duck.\n";
	}

	//both goose and it choose unique random numbers
	int gooseRandom; int itRandom;
	do {
		gooseRandom = rand() % 50;
		itRandom = rand() % 50;
	} while(gooseRandom == itRandom);

	if(itRandom > gooseRandom) { //if goose doesn't catch it player
		output << gameData->itPlayerID << " took " << goose << "'s spot!\n";

		int tempPlayerID = gameData->itPlayerID;

		//switch places of the goose and it player
		gameData->itPlayerID = goose;
		output << gameData->itPlayerID << " was chosen as the new it.\n";
		(gameData->playerList).set((size_t) m, tempPlayerID);
	} else { //if goose catches it player
		output << gameData->itPlayerID << " is out!\n";
		if((int) (gameData->playerList).size() == 1) {
			output << "Winner is " << (gameData->playerList).get(0) << "!\n";
			gameData->itPlayerID = 0;
			return;
		}
		int newItPlayerIndex = rand() % ((int) (gameData->playerList).size());

		gameData->itPlayerID = (gameData->playerList).get((size_t) newItPlayerIndex);
		(gameData->playerList).remove((size_t) newItPlayerIndex);
	}
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		std::cout << "Please retry command with the following format: ./duck_duck_goose *input_configuration_file.txt* *output_file.txt" << std::endl;
		return 1;
	}

	std::ifstream myfile(argv[1]);
	if(myfile.fail()) {
		std::cout << "Was not able to open the specified file." << std::endl;
	}
	std::string myline;

	GameData *gameData = new GameData;

	std::stringstream output;

	int lineNum = 1;

	unsigned int randSeed;
	int numPlayers;

	while(getline(myfile, myline)) {
		std::stringstream ss(myline);
		switch(lineNum) {
			case 1:
				ss >> randSeed;
				srand(randSeed);
				break;
			case 2:
				ss >> numPlayers;
				break;
			case 3:
				ss >> (gameData->itPlayerID);
				break;
			default:
				int newPlayerID;
				ss >> newPlayerID;
				(gameData->playerList).push_back(newPlayerID);
		} lineNum++;
	}

	// run the game
	do {
		simulateDDGRound(gameData, output);
	} while(gameData->itPlayerID != 0);

	//make the outputfile
	std::ofstream outputFile;
	outputFile.open(argv[2]);
	if(outputFile.fail()) {
		std::cout << "Was not able to create specified file." << std::endl;
	}
	outputFile << output.str();
	outputFile.close();

	delete gameData;
	return 0;
}