#pragma once
#include "olcPixelGameEngine.h"
#include "Row.h"

#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <random>

class WordValidator {
public:
	std::vector<std::string> words;
	std::string targetWord;

	WordValidator()	{
		std::ifstream file("words.txt");
		if (file.is_open()) {
			std::string word;
			while (file >> word) {
				words.push_back(word);
			}
		}
		newWord();
	}

	void newWord() {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> uDist(0, (int)words.size());
		int randomIndex = uDist(rng);

		targetWord = words[randomIndex];
	}

	bool isCorrectWord(std::string word) {
		transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::tolower(c); });

		return word == targetWord;
	}

	std::string getTargetWord() {
		return targetWord;
	}

	bool isValidWord(std::string word, Row* row) {
		transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::tolower(c); });

		if (!(std::find(words.begin(), words.end(), word) != words.end())) return false;

		for (int i = 0; i < word.length(); i++) {
			if (word[i] == targetWord[i]) {
				row->cells[i]->setState(CellState::InColumn);
			}
			else if (std::find(targetWord.begin(), targetWord.end(), word[i]) != targetWord.end()) {
				row->cells[i]->setState(CellState::InWord);
			}
			else {
				row->cells[i]->setState(CellState::NotInWord);
			}
		}

		return true;
	}
};