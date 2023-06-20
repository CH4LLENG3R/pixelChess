#pragma once
#include <string>

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
	int getSaveHistory() { return saveHistory; }
	std::string getGameName() { return gameName;  }
};