#pragma once
#include <vector>
#include <memory>

#include "Settings.h"
#include "Clock.h"
#include "GameHistory.h"
#include "InputHandler.h"
#include "Piece.h"
#include "Figures.h"
#include "FENHandler.h"
#include "GameVariables.h"

class Game
{
protected:
	std::shared_ptr<Piece>** arrangement;
	std::shared_ptr<Piece> whiteKing;
	std::shared_ptr<Piece> blackKing;
	GameVariables variables;
private:
	void processValidMoves()
	{}
	bool isGameOver()
	{
		return false; 
	}
public:
	void move(std::string AN)
	{}

	Game()
	{
		arrangement = new std::shared_ptr<Piece>*[8];
		for (size_t i = 0; i < 8; i++)
			arrangement[i] = new std::shared_ptr<Piece>[8];

		std::string basicFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
		FENHandler fenHandler(basicFEN);

		std::vector<Piece*> arrangementVec = fenHandler.getArrangement();

		for (Piece* p : arrangementVec)
		{

		}
	}

	~Game()
	{
		whiteKing.reset();
		blackKing.reset();
		for (size_t y = 0; y < 8; y++)
		{
			for (size_t x = 0; x < 8; x++)
				arrangement[y][x].reset();
			delete[] arrangement[y];
		}
		delete[] arrangement;
	}
};