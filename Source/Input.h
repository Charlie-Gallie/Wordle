#pragma once
#include "KeyMap.h"
#include "Row.h"
#include "WordValidator.h"
#include "Config.h"
#include "GameState.h"
#include "Notify.h"

#include <vector>

class Input {
public:
	olc::PixelGameEngine& PGE;
	Config& config;
	std::vector<Row*>& rows;
	std::vector<char> typingBuffer;
	WordValidator wordValidator;
	GameState& gameState;
	Notify* notify;
	int
		typingIndex = 0,
		amountOfLetters,
		amountOfTries;
	int&
		currentRow;

	Input(
		olc::PixelGameEngine& _PGE,
		Config& _config,
		std::vector<Row*>& _rows,
		GameState& _gameState,
		int _amountOfLetters,
		int _amountOfTries,
		int& _currentRow
	) :
		PGE(_PGE),
		config(_config),
		rows(_rows),
		gameState(_gameState),
		amountOfLetters(_amountOfLetters),
		amountOfTries(_amountOfTries),
		currentRow(_currentRow)
	{
		for (int letter = 0; letter < amountOfLetters; letter++) typingBuffer.push_back(' ');
		notify = new Notify(PGE);
	}

	void upate() {
		KeyMap key = getKey(PGE);
		if (key.Key != olc::NONE) {
			if (key.typable) {
				if (typingIndex < amountOfLetters) {
					typingBuffer[typingIndex] = key.Character;
					typingIndex++;
				}
			}
			else {
				if (key.Character == '<') {
					if (gameState == GameState::DuringGame) {
						if (typingIndex > 0) {
							typingIndex--;
							typingBuffer[typingIndex] = ' ';
						}
					}
				}
				if (key.Character == '+') {
					if (gameState == GameState::DuringGame) {
						if (!(std::find(typingBuffer.begin(), typingBuffer.end(), ' ') != typingBuffer.end())) {
							std::string word(typingBuffer.begin(), typingBuffer.end());
							if (wordValidator.isValidWord(word, rows[currentRow])) {
								rows[currentRow]->selected = false;
								if (!wordValidator.isCorrectWord(word)) {
									typingIndex = 0;
									if (currentRow + 1 < amountOfTries) {
										for (char& letter : typingBuffer) letter = ' ';
										currentRow++;
										rows[currentRow]->selected = true;
									}
									else {
										notify->send(
											"The word was \"" + wordValidator.getTargetWord() + "\"",
											-1
										);
										notify->send(
											"Press [ENTER] to play again",
											-1
										);
										gameState = GameState::PostGame;
									}
								}
								else {
									notify->send(
										"You got the word!",
										-1
									);
									notify->send(
										"Press [ENTER] to play again",
										-1
									);
									gameState = GameState::PostGame;
								}
							}
							else {
								notify->send(
									word + " is not a word"
								);
							}
						}
						else {
							notify->send(
								"Not enough characters"
							);
						}
					}
					else {
						notify->clear();
						for (char& letter : typingBuffer) letter = ' ';
						typingIndex = 0;
						currentRow = 0;

						for (Row* row : rows) delete row;
						rows.clear();

						for (int row = 0; row < amountOfTries; row++) {
							rows.push_back(new Row(
								PGE,
								config,
								amountOfLetters,
								60 + ((config.cellSize + config.cellPadding) * row)
							));
						}
						rows[0]->selected = true;
						wordValidator.newWord();
						gameState = GameState::DuringGame;
					}
				}
			}
			rows[currentRow]->setTypingBuffer(typingBuffer);
		}
		notify->draw();
	}
};