#pragma once
#include "olcPixelGameEngine.h"
#include "Cell.h"

#include <vector>

class Row {
public:
	olc::PixelGameEngine& PGE;
	Config& config;
	int
		amountOfLetters,
		verticalPosition,
		rowLength = 0,
		dotRadius = 3;
	bool selected = false;

	std::vector<Cell*> cells;
	std::vector<char> typingBuffer;

	Row(
		olc::PixelGameEngine& _PGE,
		Config& _config,
		int _amountOfLetters,
		int _verticalPosition
	) :
		PGE(_PGE),
		config(_config),
		amountOfLetters(_amountOfLetters),
		verticalPosition(_verticalPosition)
	{
		rowLength = (config.cellSize + config.cellPadding) * amountOfLetters;

		for (int cell = 0; cell < amountOfLetters; cell++) {
			cells.push_back(new Cell(
				PGE,
				config,
				{ 
					{	// Scoped to make it easier to read
						((config.cellSize * cell) +
						(config.cellPadding * cell) +
						(PGE.ScreenWidth() / 2)) -
						(rowLength / 2)
					},
					verticalPosition
				}
			));
		}
	}

	void setTypingBuffer(std::vector<char> _typingBuffer) {
		typingBuffer = _typingBuffer;
		for (int cellIndex = 0; cellIndex < cells.size(); cellIndex++) {
			cells[cellIndex]->letter = typingBuffer[cellIndex];
		}
	}

	void draw() {
		if (selected) PGE.FillCircle(
			{
				((PGE.ScreenWidth() / 2) - (rowLength / 2) - (config.cellPadding)) - dotRadius,
				verticalPosition + (config.cellSize / 2) + (dotRadius / 2)
			},
			dotRadius,
			config.colorPrimary
		);
		for (Cell* cell : cells) cell->draw();
	}
};