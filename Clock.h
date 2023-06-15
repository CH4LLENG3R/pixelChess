#pragma once
#include <thread>
#include "Timestamp.h"
class Clock
{
	Timestamp whiteTime;
	Timestamp blackTime;
	bool activeColor;
	std::thread clockThread;

	void update()
	{
		while (!whiteTime.isZero() && !blackTime.isZero())
		{
			if (activeColor)
				whiteTime.decrement();
			else
				blackTime.decrement();
		
		}
	}

public:
	void setActiveColor(bool activeColor) { this->activeColor = activeColor; }

	Clock(Timestamp whiteTime, Timestamp blackTime) : whiteTime(whiteTime), blackTime(blackTime)
	{
		clockThread = std::thread(&Clock::update)
	};

	~Clock()
	{

	}
};

