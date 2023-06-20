#pragma once
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "Settings.h"
class GameHistory
{
	std::string path;
	std::string historyfullpath;
	std::vector<std::string> fens;
public:

	static bool gameExists(std::string gameName)
	{
		std::string path_temp = "saves/" + gameName;
		return std::filesystem::exists(path_temp);
	}

	static std::vector<std::string> getAvailibleGames()
	{
		std::vector<std::string> res;
		std::string path_temp = "saves/";
		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path_temp))
		{
			if (entry.is_directory())
				res.push_back(entry.path().filename().string());
		}

		return res;
	}

	static void saveSettings(Settings set)
	{
		std::ofstream file_temp;
		file_temp.open("saves/" + set.getGameName() + "/settings.txt");
		file_temp << set;
	}


	static Settings getSettings(std::string gameName)
	{
		std::ifstream file_temp;
		file_temp.open("saves/" + gameName + "/settings.txt");
		Settings set;
		file_temp >> set;
		file_temp.close();
		set.setGameName(gameName);
		return set;
	}


	std::string getlastmove()
	{
		return fens.back();
	}

	void append(std::string fen)
	{
		fens.push_back(fen);
		std::ofstream file;
		file.open(historyfullpath);
		std::vector<std::string>::iterator itr;

		for (itr = fens.begin(); itr != fens.end(); itr++)
		{
			file << *itr << '\n';
		}

		file.close();
	}

	GameHistory(Settings settings)
	{
		path = "saves/";
		historyfullpath = path + settings.getGameName() + "/history.txt";


		if (std::filesystem::exists(historyfullpath))
		{
			std::ifstream file;
			file.open(historyfullpath);

			std::string str;
			while (std::getline(file, str))
			{
				if (str.size() > 0)
					fens.push_back(str);
			}
			file.close();
		}
		else
		{
			std::filesystem::create_directories(path + settings.getGameName());
			fens.push_back("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			std::ofstream file;
			file.open(historyfullpath);
			file << fens.back() << '\n';
			file.close();
			saveSettings(settings);
		}
	}
};