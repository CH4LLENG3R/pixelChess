#pragma once
#include <vector>

#include "Position.h"

class Piece
{
protected:
	std::vector<Position> validMoves;
	Position pos;
	bool color;
	Piece(): pos() 
	{}
	Piece(const Position& pos, const bool& color) : pos(pos), color(color)
	{}
public: 
	bool getColor() { return color;  }

	std::vector<Position> getValidMoves() { return validMoves; }

	void setValidMoves(std::vector<Position> validMoves)
	{
		this->validMoves = validMoves;
	}

	void clearValidMoves()
	{
		validMoves.clear();
	}

	virtual std::vector<Position> getMoves() 
	{
		return std::vector<Position>();
	};
};

