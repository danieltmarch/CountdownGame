#include "WordGame.h"

#include <fstream>
#include <conio.h>
#include <iostream>
#include <algorithm>
using namespace std;


//vowel and consonant functions
void WordGame::resetConsonants()
{
	consonants = {}; //reset vector

	ifstream file("Data/consonantList.txt"); //open file
	char c; //placeholder for characters from file data stream
	while (file >> c) //while there are chars left to read
		consonants.push_back(c);
	file.close();
}
void WordGame::resetVowels()
{
	vowels = {}; //reset vector

	ifstream file("Data/vowelList.txt"); //open file
	char c; //placeholder for characters from file data stream
	while (file >> c) //while there are chars left to read
		vowels.push_back(c);
	file.close();
}

void WordGame::generateBuckets()
{
	resetConsonants(); //fill the lists based on files
	resetVowels();
	random_shuffle(consonants.begin(), consonants.end()); //randomize lists
	random_shuffle(vowels.begin(), vowels.end()); //randomize lists
}
//end vowel and consonant functions

//get words from file and find their number codes
void WordGame::generateWordCodes()
{
	ifstream file("Data/dictionaryList.txt");
	
	pair<string, unsigned long long int> wordCode;
	while (getline(file, wordCode.first)) //while there is still data left to read
	{
		wordCode.second = getCodeFromWord(wordCode.first);
		wordCodes.push_back(wordCode);
	}
	file.close();
}

unsigned long long int WordGame::getCodeFromWord(std::string word)
{
	unsigned long long int num = 1;
	for (char& c : word) //determine the num for this word
	{
		num = num * primes[c - 'a']; //i.e. a maps to index zero which is 2, z maps to 25 which is 101
	}
	return num;
}


string WordGame::selectWord()
{
	int lettersChosen = 0;
	int vowelCount = 0;
	int consonantCount = 0;

	string clue = "";
	while (lettersChosen < 9)
	{
		cout << "Current Word: " << clue << endl;
		bool chooseVowel = vowelCount < 5; //max of 5 vowels
		bool chooseConsonant = consonantCount < 6; //max of 6 consonants
		
		if (chooseVowel && chooseConsonant) //either option valid
		{
			chooseVowel = false;
			chooseConsonant = true;
			cout << "Consonant or vowel? v/c: ";
			if (_getch() == 'c')
				chooseConsonant = true;
			else
				chooseVowel = true;
		}
		if (chooseVowel) //select vowel
		{
			clue = clue + vowels.back();
			vowels.pop_back();
			++vowelCount;
		}
		else //select consonant
		{
			clue = clue + consonants.back();
			consonants.pop_back();
			++consonantCount;
		}
		++lettersChosen;
		system("cls"); //clear screen
	}
	cout << "Final Word: " << clue << endl;
	return clue;
}

vector<string> WordGame::getValidWords(string clue)
{
	unsigned long long int clueCode = getCodeFromWord(clue);

	vector<string> validWords;
	for (pair<string, unsigned long long int>& codePair : wordCodes)
		if (clueCode % codePair.second == 0) //valid word
			validWords.push_back(codePair.first);

	sort(validWords.begin(), validWords.end(), [](string a, string b) {return a.size() > b.size();} ); //sort the vector by words size, largest to smallest.
	return validWords;
}

bool WordGame::isValidAnswer(string clue, string answer)
{
	unsigned long long int clueCode = getCodeFromWord(clue);
	unsigned long long int answerCode = getCodeFromWord(answer);

	return (clueCode % answerCode == 0);
}