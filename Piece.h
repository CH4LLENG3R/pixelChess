#pragma once
#include <vector>

#include "Position.h"
#include "PieceTypes.h"

bool posInBorder(short x, short y)
{
	if (x >= 0 && x < 8 && y >= 0 && y < 8)
		return true;
	return false;
}

bool posInBorder(Position pos)
{
	return posInBorder(pos.x, pos.y);
}

class Piece
{
protected:
	std::vector<Position> validMoves;

	bool color;
	pc::PieceType pieceType;
	Position pos;
	Piece(): pieceType(pc::PieceType::empty), pos()
	{}
	Piece(const Position& pos, const bool& color): pieceType(pc::PieceType::empty), color(color), pos(pos)
	{}
public: 
	bool getColor() { return color;  }

	pc::PieceType getPieceType() { return pieceType;  }

	Position getPosition() { return pos; }
	void setPosition(const Position& pos) { this->pos = pos; }

	std::vector<Position> getValidMoves() { return validMoves; }

	void setValidMoves(std::vector<Position> validMoves)
	{
		this->validMoves = validMoves;
	}

	void clearValidMoves()
	{
		validMoves.clear();
	}

	virtual std::vector<Position> getMoves(std::shared_ptr<Piece>** arrangement)
	{
		return std::vector<Position>();
	};
};

