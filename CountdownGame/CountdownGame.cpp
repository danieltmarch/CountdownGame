//Made by Daniel March 2020 11 19

#include "GameHandler.h"

#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	GameHandler game;
	game.runFullGame();

	return 0;
}

/* for making a valid countdown dictionary
ifstream file("dictionaryListRaw.txt");
ofstream fileNew("dictionaryListNew.txt");
string line;
while (getline(file, line))
{
	bool valid = true;
	int vowelCount = 0;
	if (line.size() > 9)
		valid = false;
	for (char c : line)
	{
		if (c < 'a' || c > 'z')
		{
			valid = false;
			break;
		}
		if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
			vowelCount++;
	}
	if (vowelCount < 3 || vowelCount > 5)
		valid = false;
	if(valid)
		fileNew << line << endl;
}
file.close();
fileNew.close();
*/

/* for 9 word clue text file, scrapped since conundrum rounds should be hand made
ifstream file("dictionaryListRaw.txt");
	ofstream fileNew("9LetterDictionary.txt");
	string line;
	while (getline(file, line))
	{
		bool valid = true;
		int vowelCount = 0;
		if (line.size() != 9)
			valid = false;
		for (char c : line)
		{
			if (c < 'a' || c > 'z')
			{
				valid = false;
				break;
			}
			if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
				vowelCount++;
		}
		if (vowelCount < 3 || vowelCount > 5)
			valid = false;
		if (valid)
			fileNew << line << endl;
	}
	file.close();
	fileNew.close();

	return 0;
*/


/*
string input;
	cout << "Input: ";
	cin >> input;
	unsigned long long int inputCode = generateWordCode(input);
	for(int i = 0; i < words.size(); i++)
	{
		if (inputCode % wordCodes[i] == 0)
		{
			cout << words[i] << endl;
		}
	}
*/