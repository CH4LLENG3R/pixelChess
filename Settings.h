#pragma once
#include <string>
#include <iostream>
#include "Timestamp.h"
class Settings
{
	Timestamp whiteTime;
	Timestamp blackTime;
	bool saveHistory;
	std::string gameName;
	bool allowUndo;
public:
	Settings() {};
	Settings(Timestamp whiteTime, Timestamp blackTime, const bool& saveHistory, const bool& allowUndo, std::string gameName): whiteTime(whiteTime), blackTime(blackTime), saveHistory(saveHistory), gameName(gameName), allowUndo(allowUndo)
	{}
	
	Timestamp getWhiteTime() { return whiteTime; }
	Timestamp getBlackTime() { return blackTime; }
	void setWhiteTime(Timestamp timestamp) { whiteTime = timestamp;  }
	void setBlackTime(Timestamp timestamp) { blackTime = timestamp;  }
	void setGameName(std::string gameName) { this->gameName = gameName;  }
	int getSaveHistory() { return saveHistory; }
	std::string getGameName() { return gameName;  }

	friend std::ostream& operator<<(std::ostream& os, const Settings& s);
	friend std::istream& operator>>(std::istream& os, Settings& s);
};
std::ostream& operator<<(std::ostream& os, const Settings& s)
{
	os << s.whiteTime.getHour() << ' ' << s.whiteTime.getMinute() << ' ' << s.whiteTime.getSecond() << '\n';
	os << s.blackTime.getHour() << ' ' << s.blackTime.getMinute() << ' ' << s.blackTime.getSecond() << '\n';
	os << s.saveHistory << '\n';
	os << s.allowUndo << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, Settings& s)
{
	int hour, min, sec;
	is >> hour >> min >> sec;
	s.whiteTime = Timestamp(hour, min, sec);
	is >> hour >> min >> sec;
	s.blackTime = Timestamp(hour, min, sec);
	is >> s.saveHistory;
	is >> s.allowUndo;
	return is;
}
