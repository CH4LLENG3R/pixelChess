#pragma once
#include <thread>
#include "Timestamp.h"
class Clock
{
	Timestamp whiteTime;
	Timestamp blackTime;
	bool activeColor;
	bool terminate;
	std::thread clockThread;

	void update()
	{
		while (!terminate && !whiteTime.isZero() && !blackTime.isZero())
		{
			if (activeColor)
				whiteTime.decrement();
			else
				blackTime.decrement();

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}

public:
	bool isWhiteTimeOver() { return whiteTime.isZero(); }
	bool isBlackTimeOver() { return blackTime.isZero(); }

	Timestamp getWhiteTime() { return whiteTime; }
	Timestamp getBlackTime() { return blackTime; }

	void setActiveColor(bool activeColor) { this->activeColor = activeColor; }

	Clock(Timestamp whiteTime, Timestamp blackTime) : whiteTime(whiteTime), blackTime(blackTime), activeColor(1), terminate(false)
	{
		clockThread = std::thread(&Clock::update, this);
	};

	~Clock()
	{
		terminate = true;
		clockThread.join();
	}
};

