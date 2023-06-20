#pragma once
class Timestamp
{
	short hour;
	short minute;
	short second;
public:
	short getHour() const { return hour; }
	short getMinute() const { return minute; }
	short getSecond() const { return second; }

	void decrement()
	{
		second--;
		if (second == -1)
		{
			second = 59;
			minute--;
			if (minute == -1)
			{
				minute = 59;
				hour--;
			}
		}
	}

	bool isZero()
	{
		if (hour == 0 && minute == 0 && second == 0)
			return true;
		return false;
	}
	Timestamp(){}
	Timestamp(short hour, short minute, short second) : hour(hour), minute(minute), second(second) {};

	friend std::ostream& operator<<(std::ostream& os, const Timestamp& dt);
};

std::ostream& operator<<(std::ostream& os, const Timestamp& dt)
{
	os << dt.hour << " : " << dt.minute << " : " << dt.second;
	return os;
}
