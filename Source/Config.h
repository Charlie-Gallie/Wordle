#pragma once
#include "olcPixelGameEngine.h"

class Config {
public:
	olc::Pixel
		colorPrimary = olc::Pixel(255, 255, 255),
		colorSecondary = olc::Pixel(200, 200, 200),
		backgroundColor = olc::Pixel(20, 100, 155),
		
		cellColorDefault = olc::Pixel(255, 255, 255),
		cellColorNotInWord = olc::Pixel(130, 130, 130),
		cellColorInWord = olc::Pixel(255, 130, 0),
		cellColorInColumn = olc::Pixel(10, 200, 0);

	int
		fontSizePrimary = 3,
		fontSizeSecondary = 1,
		cellSize = 35,
		cellPadding = 5;
};