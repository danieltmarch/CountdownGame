#ifndef WORDGAME_H
#define WORDGAME_H

#include <string>
#include <vector>
#include <map>

class WordGame
{
	public:
		//no constructor needed

		void generateWordCodes(); //populate the WordCodes pair list;
		void generateBuckets(); //(re)populate the vowels and consonants
		std::string selectWord(); //get the clue, requires user input
		std::vector<std::string> getValidWords(std::string clue); //get a sorted list of valid matching words
		bool isValidAnswer(std::string clue, std::string answer);

	private:

		void resetConsonants();
		void resetVowels();
		unsigned long long int getCodeFromWord(std::string word);

		const std::vector<int> primes = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101 };

		std::vector<std::pair<std::string, unsigned long long int>> wordCodes; //the list of words and their prime number codes
		std::vector<char> vowels; //list of vowels in the "bucket"
		std::vector<char> consonants; //list of consonants in the "bucket"
};


#endif
