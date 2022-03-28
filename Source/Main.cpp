#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Config.h"
#include "Row.h"
#include "KeyMap.h"
#include "Input.h"
#include "GameState.h"

#include <vector>

using namespace std;
using namespace olc;

class Wordle : public PixelGameEngine {
public:
	std::vector<Row*> rows;
	Config config;
	GameState gameState = GameState::DuringGame;
	int
		amountOfLetters = 5,
		amountOfTries = 6,
		currentRow = 0;
	Input input{ *this, config, rows, gameState, amountOfLetters, amountOfTries, currentRow };

	std::string title = "Wordle";
	int titleWidth;

	void beginGame() {
		for (Row* row : rows) delete row;
		rows.clear();

		for (int row = 0; row < amountOfTries; row++) {
			rows.push_back(new Row(
				*this,
				config,
				amountOfLetters,
				60 + ((config.cellSize + config.cellPadding) * row)
			));
		}
		rows[0]->selected = true;
		gameState = GameState::DuringGame;
	}

	Wordle() {
		sAppName = "Wordle";
	}

	bool OnUserCreate() {
		titleWidth = GetTextSize(title).x * config.fontSizePrimary;
		beginGame();

		return true;
	}

	bool OnUserUpdate(float dt) {
		Clear(config.backgroundColor);

		DrawString(
			{ (ScreenWidth() / 2) - (titleWidth / 2), 20 },
			title,
			config.colorPrimary,
			config.fontSizePrimary
		);

		input.upate();

		for (Row* row : rows) row->draw();

		return true;
	}
};

int main() {
	Wordle wordle;
	if (wordle.Construct(
		400,	// X
		400,	// Y
		2,		// Scale X
		2,		// Scale Y
		false,	// Fullscreen
		true	// Vsync
	)) wordle.Start();
}