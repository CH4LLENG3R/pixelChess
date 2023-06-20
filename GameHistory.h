#pragma once
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
class GameHistory
{
	std::fstream file;
	std::string path;
	std::string gamename;
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

	std::string getlastmove()
	{
		return fens.back();
	}

	void append(std::string fen)
	{
		file.open(historyfullpath);
		fens.push_back(fen);
		std::vector<std::string>::iterator itr;

		for (itr = fens.begin(); itr != fens.end(); itr++)
		{
			file << *itr << '\n';
		}

		file.close();
	}

	GameHistory()
	{
		path = "saves/";
		if (!std::filesystem::exists(path))
			std::filesystem::create_directories(path);

		for (int i = 0; ; i++)
		{
			if (!std::filesystem::exists(path + "game" + std::to_string(i)))
			{
				std::filesystem::create_directories(path + "game" + std::to_string(i));
				gamename = "game" + std::to_string(i);
				break;
			}
		}

		historyfullpath = path + gamename + "/history.txt";
/*		file.open(historyfullpath);
		file << fen << '\n';
		file.close()*/;

	}

	GameHistory(std::string gamename)
	{

		if (std::filesystem::exists(path + gamename + "history.txt"))
		{
			historyfullpath = path + gamename + "/history.txt";
			file.open(historyfullpath);

			std::string str;
			while (std::getline(file, str))
			{
				if (str.size() > 0)
					fens.push_back(str);
			}
		}
	}

	~GameHistory()
	{
		file.close();
	}
};