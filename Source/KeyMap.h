#pragma once
#include "olcPixelGameEngine.h"
#include <vector>

struct KeyMap {
	olc::Key Key;
	char Character;
	bool typable = true;
};

std::vector<KeyMap> keyMap = {
	{olc::A, 'A'},
	{olc::B, 'B'},
	{olc::C, 'C'},
	{olc::D, 'D'},
	{olc::E, 'E'},
	{olc::F, 'F'},
	{olc::G, 'G'},
	{olc::H, 'H'},
	{olc::I, 'I'},
	{olc::J, 'J'},
	{olc::K, 'K'},
	{olc::L, 'L'},
	{olc::M, 'M'},
	{olc::N, 'N'},
	{olc::O, 'O'},
	{olc::P, 'P'},
	{olc::Q, 'Q'},
	{olc::R, 'R'},
	{olc::S, 'S'},
	{olc::T, 'T'},
	{olc::U, 'U'},
	{olc::V, 'V'},
	{olc::W, 'W'},
	{olc::X, 'X'},
	{olc::Y, 'Y'},
	{olc::Z, 'Z'},

	{olc::BACK, '<', false},
	{olc::ENTER, '+', false},
	{olc::RETURN, '+', false},

	{olc::NONE, ' ', false}
};

KeyMap getKey(olc::PixelGameEngine& PGE) {
	for (KeyMap key : keyMap)
		if (PGE.GetKey(key.Key).bPressed)
			return key;
	return keyMap.back();
}