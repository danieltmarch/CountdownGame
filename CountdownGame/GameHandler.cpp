#include "GameHandler.h"

#include <iostream>
#include <conio.h>

#include <time.h>
#include <random>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

GameHandler::GameHandler()
{
	cout << "Preparing game..." << endl;

	wordGame.generateWordCodes(); //doesn't use randomness, and takes the longest
	
	setRandomSeed();

	//setup the games
	wordGame.generateBuckets();
	numberGame.generateNumbers();

	cout << "Game setup!" << endl << endl;
	system("pause");
	system("cls");
}

void GameHandler::runNumberGame(int& score)
{
	cout << "Number Round:" << endl;
	vector<int> clues;
	int goal;
	int userNum;
	//select goal
	numberGame.selectNumbers(clues, goal); //this function will print out the info
	numberGame.generateNumbers(); //reset the numbers every round

	//make print message for the timer
	string message = "Goal: " + to_string(goal) + " by using: ";
	for (int num : clues)
		message = message + to_string(num) + ' ';

	system("pause");

	//30 sec timer
	runClock(message);

	cout << "Enter your solution: ";
	cin >> userNum;

	//perform scoring
	int distance = abs(goal - userNum); //distance from goal
	if (distance <= 10)
	{
		score = score + 5; //5 score
		if (distance <= 5)
		{
			score = score + 2; //2 + 5 = 7 score
			if (distance == 0)
				score = score + 3; //5 + 2 + 3 = 10 score
		}
		cout << "Good job. Your score is now " << score << '.' << endl;
	}
	else
	{
		cout << "Sory, your score is still " << score << '.' << endl;
	}

	//print the closest solution
	cout << endl << "Here is the best solution: " << endl;
	numSolver.getSolution(clues, goal);
	cout << endl << endl;

	system("pause");
	system("cls");
}


void GameHandler::runWordGame(int& score)
{
	cout << "Word Round: " << endl;
	vector<string> options;
	string word;
	string inputWord;

	//select word
	word = wordGame.selectWord();
	system("pause");
	
	//30 sec timer
	runClock("Letters are: " + word);
	
	//enter user soluction
	cout << "Enter your solution: ";
	cin >> inputWord;

	//calculate scoring
	options = wordGame.getValidWords(word);
	if (find(options.begin(), options.end(), inputWord) != options.end()) //if word is an option
	{
		score = score + inputWord.size(); //1 point for each letter
		if (inputWord.size() == 9) //18 points for 9 letter word, 9 points already added from previous line
			score = score + 9;
		cout << "Congrats, that word is valid. Your score is now " << score << '.' << endl;
	}
	else
	{
		cout << "Sorry that word isn't valid. Your Score is still " << score << '.' << endl;
		inputWord = "aaaaa"; //reset input to size 5 so all options of 5 or bigger will be printed out
	}

	cout << "Other options: " << endl << '\t';
	for (int i = 0; i < options.size() && options[i].size() >= inputWord.size() && i < 25; i++) //stop after 25 words or after size of user input
		cout << options[i] << ", ";
	cout << endl << endl;

	system("pause");
	system("cls");
}

void GameHandler::runFullGame()
{
	int score = 0;

	//first set
	runWordGame(score);
	runWordGame(score);
	runNumberGame(score);

	//2nd set
	runWordGame(score);
	runWordGame(score);
	runNumberGame(score);

	//3rd set
	runWordGame(score);
	runWordGame(score);
	runNumberGame(score);

	//last set, twice as long
	runWordGame(score);
	runWordGame(score);
	runWordGame(score);
	runWordGame(score);
	runNumberGame(score);
	runNumberGame(score);

	system("cls");
	cout << "Thanks for playing. Your final score is " << score << '.' << endl;
	system("pause");
}

void GameHandler::setRandomSeed() //suggests a random seed based on system time, and adds
{
	cout << "Use default random seed? y/n: " << endl;
	if (_getch() == 'n')
	{
		cout << "Reccomended Seed: " << time(0) << endl;
		cout << "Enter Seed: ";
		int seed;
		cin >> seed;
		srand(seed);
	}
	else
		srand(time(0)); //default seed based on time
}


void GameHandler::runClock(std::string message)
{
	int startTime = time(0);
	int currentTime = startTime;
	int lastTime = currentTime;
	while (currentTime - startTime < 30) //30 sec timer
	{
		currentTime = time(0);
		if (currentTime != lastTime)
		{
			system("cls");
			cout << message << endl;
			printClock(currentTime - startTime);
		}

		lastTime = currentTime;
	}
}

void GameHandler::printClock(int secRemain)
{
	int topHalf = 30 - secRemain; //how many O's on the top
	int bottomHalf = secRemain; //"how many O's on the bottom
	cout << "Seconds Remaining: " << secRemain << endl;
	int width = 11;
	cout << "-------------" << endl;
	while (width >= 1) //print top half
	{
		int sideWidth = 5 - (width / 2);
		int dots = topHalf - pow((width - 1) / 2, 2);
		if (dots < 0)
			dots = 0;
		if (dots > width)
			dots = width;

		for (int j = 0; j < sideWidth; j++)
			cout << ' ';

		cout << '\\';
		
		int i = 0;
		for (; i < dots; i++)
			cout << 'O';
		for (; i < width; i++)
			cout << ' ';

		cout << '/' << endl;

		width = width - 2;
	}
	width = 1;
	while (width <= 11) //print top half
	{
		int sideWidth = 5 - (width / 2);
		int dots = bottomHalf - (-1*pow(width,2) - 2*width + 143) / 4; //mapping, quadratic function
		if (dots < 0)
			dots = 0;
		if (dots > width)
			dots = width;

		for (int j = 0; j < sideWidth; j++)
			cout << ' ';

		cout << '/';

		int i = 0;
		for (; i < dots; i++)
			cout << 'O';
		for (; i < width; i++)
			cout << ' ';

		cout << '\\' << endl;

		width = width + 2;
	}
	cout << "-------------" << endl;
}