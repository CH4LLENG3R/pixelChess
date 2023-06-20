#pragma once
#include <thread>
#include "Timestamp.h"
class Clock
{
	Timestamp whiteTime;
	Timestamp blackTime;
	bool activeColor;
	bool terminate;
	bool running;
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

	void start()
	{
		if (!running)
		{
			clockThread = std::thread(&Clock::update, this);
			running = true;
		}
	}

	Clock(Timestamp whiteTime, Timestamp blackTime, bool start = false) : whiteTime(whiteTime), blackTime(blackTime), activeColor(1), terminate(false)
	{
		running = false;
		if (start)
			this->start();
	};

	~Clock()
	{
		terminate = true;
		if(running)
			clockThread.join();
	}
};

