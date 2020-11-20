#ifndef NUMBERGAME_H
#define NUMBERGAME_H

#include <string>
#include <vector>

class NumberGame
{
	public:
		//no constructor needed
		void generateNumbers();

		void selectNumbers(std::vector<int>& clues, int& goal); //user chooses the 6 clues and goal number, the goal number is the 

	private:
		void generateBigNumbers();
		void generateSmallNumbers();

		std::vector<int> bigNums;
		std::vector<int> smallNums;
};

struct searchState
{
	int num; //the current num resulting from the used numbers and operations
	std::vector<int> toUse; //numbers yet to be used
	std::vector<int> used; //numbers used so far
	std::vector<char> operations; // + - / *
};


class NumSolver
{
	public:
		void getSolution(std::vector<int> clues, int goal); //perform the search and print the solution if there is one, if there isn't print the closest one
	private:
		searchState findSolution(std::vector<int> clues, int goal); //perform the search for the goal
		void printSearchState(searchState node);

		std::vector<searchState> expand(searchState); //expand the tree from the searchState node
};

#endif