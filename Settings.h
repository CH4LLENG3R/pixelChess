#pragma once
#include <string>

class Settings
{
	int whiteTime;
	int blackTime;
	bool saveHistory;
	std::string historyPath;
public:
	Settings(const int& whiteTime, const int& blackTime, const bool& saveHistory, std::string historyPath): whiteTime(whiteTime), blackTime(blackTime), saveHistory(saveHistory), historyPath(historyPath)
	{}
	
	int getWhiteTime() { return whiteTime; }
	int getBlackTime() { return blackTime; }
	int getSaveHistory() { return saveHistory; }
	std::string getHistoryPath() { return historyPath;  }
};