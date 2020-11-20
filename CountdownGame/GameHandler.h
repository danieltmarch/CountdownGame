#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "WordGame.h"
#include "NumberGame.h"

class GameHandler
{
	public:
		GameHandler(); //constructor
		void runFullGame();
	private:
		void runWordGame(int& score);
		void runNumberGame(int& score);

		void runClock(std::string message); //print the clock and print message until the timer expires
		void printClock(int secRemain); //print nice hourglass to show time remaining
		void setRandomSeed(); //suggests a random seed based on system time, or allows user to set custom seed if they want to sync games

		WordGame wordGame;
		NumberGame numberGame;
		NumSolver numSolver;
};

#endif