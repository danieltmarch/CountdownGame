#include "NumberGame.h"

#include <conio.h>
#include <iostream>
#include <fstream>

#include <math.h>
#include <random>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

void NumberGame::generateBigNumbers()
{
	bigNums = {}; //reset vector

	ifstream file("Data/bigNumberList.txt"); //open file
	int num; //placeholder for characters from file data stream
	while (file >> num) //while there are chars left to read
		bigNums.push_back(num);
	file.close();
}
void NumberGame::generateSmallNumbers()
{
	smallNums = {}; //reset vector

	ifstream file("Data/smallNumberList.txt"); //open file
	int num; //placeholder for characters from file data stream
	while (file >> num) //while there are chars left to read
		smallNums.push_back(num);
	file.close();
}

void NumberGame::generateNumbers()
{
	generateBigNumbers(); //fill the lists from files
	generateSmallNumbers();

	random_shuffle(bigNums.begin(), bigNums.end()); //shuffle the lists
	random_shuffle(smallNums.begin(), smallNums.end());
}

void NumberGame::selectNumbers(std::vector<int>& clues, int& goal)
{
	clues = {}; //reset the clues

	char input = ' ';
	do //get a valid input from the user
	{
		cout << "How many big numbers? (0-4): ";
		input = _getch();
		system("cls");
	} while (input < '0' || input > '4'); //not a valid entry

	int bigNumCount = (input - '0'); //[0,4]
	int smallNumCount = 6 - bigNumCount;

	while (bigNumCount > 0) //add the large nums to the list
	{
		clues.push_back( bigNums.back() );
		bigNums.pop_back();
		--bigNumCount;
	}
	while (smallNumCount > 0) //add the large nums to the list
	{
		clues.push_back( smallNums.back() );
		smallNums.pop_back();
		--smallNumCount;
	}

	goal = 100 + (rand() % 900); //range of [100, 999]

	//print info
	cout << "Goal: " << goal << endl;
	cout << "Numbers: ";
	for (int num : clues)
		cout << num << ' ';
	cout << endl;
}

//------------------------- Solver functions below

void NumSolver::getSolution(std::vector<int> clues, int goal)
{
	searchState solution = findSolution(clues, goal);
	printSearchState(solution);
}

void NumSolver::printSearchState(searchState node)
{
	cout << node.num << " is achievable." << endl;
	cout << "Solution: " << endl;
	int total = node.used[0];
	
	for (int i = 0; i < node.operations.size(); i++)
	{
		cout << "\t= " << total << ", " << total << ' ' << node.operations[i] << ' ' << node.used[i + 1] << endl;
		switch (node.operations[i])
		{
			case '+':
				total = total + node.used[i + 1];
				break;
			case '-':
				total = total - node.used[i + 1];
				break;
			case '*':
				total = total * node.used[i + 1];
				break;
			case '/':
				total = total / node.used[i + 1];
				break;
		}
	}
	cout << "\t= " << total;
}

searchState NumSolver::findSolution(vector<int> clues, int goal)
{
	searchState current{ 0, {}, {}, {} }; //blank current state
	queue<searchState> frontier;

	map<int, searchState> found; //numbers that we have found so far

	for (int i = 0; i < clues.size(); i++) //initial states on the stack
	{
		vector<int> cluesCopy = clues; //copy the clues
		cluesCopy.erase(cluesCopy.begin() + i); //remove this element, since it is now used

		current.num = clues[i]; //init value
		current.used = { clues[i] };
		current.toUse = cluesCopy;

		if (current.num == goal) //check for solution
			return current;
		found[current.num] = current;
		frontier.push(current); //add to the frontier
	}

	cout << endl;
	while (!frontier.empty()) //main searching, while there are nodes left to search
	{
		current = frontier.front();
		frontier.pop();
		
		for (searchState child : expand(current))
			if (found.find(child.num) == found.end()) //not found yet
			{
				if (child.num == goal) //check for solution
					return child;
				found[child.num] = child;
				frontier.push(child);
			}
	}
	//solution not found, find the closest one instead
	int distance = 1; //the distance from goal
	while (1) //until we find a valid state, this could use a more efficient method but this should be fast anyways
	{
		if (found.find(goal + distance) != found.end()) //is in map
			return found[goal + distance];
		else if (found.find(goal - distance) != found.end()) //opposite direction is in map
			return found[goal - distance];
		++distance; //increase search distance
	}
	return current; //return something, this line should never be reached
}

vector<searchState> NumSolver::expand(searchState node)
{
	vector<searchState> children;

	searchState childNode;
	vector<int> toUseCopy = node.toUse;
	vector<int> usedCopy = node.used;
	vector<char> operCopy = node.operations;
	int numCopy = node.num;

	for (int i = 0; i < node.toUse.size(); i++) //for each num to be used
	{
		//modify copies
		toUseCopy.erase(toUseCopy.begin() + i); //remove this num for to use and add it to used
		usedCopy.push_back(node.toUse[i]);
		//set values of childnode
		childNode.toUse = toUseCopy;
		childNode.used = usedCopy;

		//modify copies depending on operation + - * /, must be validated
		if (numCopy + node.toUse[i] >= 0) //addition case validate child option
		{
			//modify copies
			numCopy = numCopy + node.toUse[i];
			operCopy.push_back('+'); //add + to the operations

			//set values of childnode
			childNode.num = numCopy;
			childNode.operations = operCopy;
			children.push_back(childNode); //add to child list

			//reset copies
			numCopy = node.num;
			operCopy = node.operations;
		}
		if (numCopy - node.toUse[i] >= 0) //subtraction case validate child option
		{
			//modify copies
			numCopy = numCopy - node.toUse[i];
			operCopy.push_back('-'); //add + to the operations

			//set values of childnode
			childNode.num = numCopy;
			childNode.operations = operCopy;
			children.push_back(childNode); //add to child list

			//reset copies
			numCopy = node.num;
			operCopy = node.operations;
		}
		if (numCopy * node.toUse[i] >= 0) //multiplication case validate child option
		{
			//modify copies
			numCopy = numCopy * node.toUse[i];
			operCopy.push_back('*'); //add + to the operations

			//set values of childnode
			childNode.num = numCopy;
			childNode.operations = operCopy;
			children.push_back(childNode); //add to child list

			//reset copies
			numCopy = node.num;
			operCopy = node.operations;
		}
		if (numCopy % node.toUse[i] == 0 && numCopy / node.toUse[i] >= 0) //division case validate child option, no fractions allowed
		{
			//modify copies
			numCopy = numCopy / node.toUse[i];
			operCopy.push_back('/'); //add + to the operations

			//set values of childnode
			childNode.num = numCopy;
			childNode.operations = operCopy;
			children.push_back(childNode); //add to child list

			//reset copies
			numCopy = node.num;
			operCopy = node.operations;
		}

		//reset copies
		toUseCopy = node.toUse;
		usedCopy = node.used;
	}
	return children;
}