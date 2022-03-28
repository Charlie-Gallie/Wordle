#pragma once
#include "olcPixelGameEngine.h"
#include "Config.h"

enum class CellState {
	Default,
	NotInWord,
	InWord,
	InColumn
};

class Cell {
public:
	olc::PixelGameEngine& PGE;
	Config& config;
	olc::vi2d position;
	CellState cellState = CellState::Default;
	olc::Pixel cellColor = config.cellColorDefault;
	char letter = ' ';

	Cell(
		olc::PixelGameEngine& _PGE,
		Config& _config,
		olc::vi2d _position = { 0, 0 }
	) :
		PGE(_PGE),
		config(_config),
		position(_position)
	{
		// Constructor
	}

	void setState(CellState _cellState) {
		cellState = _cellState;

		switch (cellState) {
		case CellState::Default: {
			cellColor = config.cellColorDefault;
			break;
		}
		case CellState::NotInWord: {
			cellColor = config.cellColorNotInWord;
			break;
		}
		case CellState::InWord: {
			cellColor = config.cellColorInWord;
			break;
		}
		case CellState::InColumn: {
			cellColor = config.cellColorInColumn;
			break;
		}
		}
	}

	void draw() {
		olc::vi2d characterSize = PGE.GetTextSize(std::string(1, letter));

		PGE.DrawString(
			{
				position.x + (characterSize.x) + 3,
				position.y + (characterSize.y) + 3
			},
			std::string(1, letter),
			cellColor,
			2
		);

		PGE.DrawRect(
			position,
			{ config.cellSize, config.cellSize },
			cellColor
		);
	}
};