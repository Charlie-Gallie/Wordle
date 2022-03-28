#pragma once
#include "olcPixelGameEngine.h"

#include <string>
#include <vector>
#include <algorithm>

class Message {
public:
	olc::PixelGameEngine& PGE;
	std::string message;
	int
		counter = 0,
		seconds,
		offset,
		messageLength;

	Message(olc::PixelGameEngine& _PGE, std::string _message, int _offset, int _seconds) :
		PGE(_PGE),
		message(_message),
		offset(_offset),
		seconds(_seconds)
	{
		messageLength = PGE.GetTextSize(message).x;
	}

	bool operator==(Message const &_msg) {
		return message == _msg.message;
	}

	Message& operator=(const Message& _msg) {
		return *this;
	}

	bool draw() {
		PGE.DrawString(
			{
				(PGE.ScreenWidth() / 2) - (messageLength / 2),
				(PGE.ScreenHeight() - 80) + offset
			},
			message
		);
		if (seconds < 0) return true;
		if (counter < (int)(PGE.GetFPS() * seconds)) {
			counter++;
			return true;
		}
		return false;
	}
};

class Notify {
public:
	std::vector<Message> messages;
	olc::PixelGameEngine& PGE;

	Notify(olc::PixelGameEngine& _PGE) : PGE(_PGE) {}

	void clear() {
		messages.clear();
		messages.shrink_to_fit();
	}

	void send(std::string message, int seconds = 2) {
		if (seconds < 0) for (Message message : messages) if (message.seconds > 0) clear();
		messages.push_back(Message(PGE, message, ((int)messages.size() * 10), seconds));
	}

	void draw() {
		for (Message& message : messages) {
			if (!message.draw()) {
				messages.erase(std::remove(messages.begin(), messages.end(), message), messages.end());
			}
		}
		messages.shrink_to_fit();
	}
};