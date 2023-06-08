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
	bool taken;
	pc::PieceType pieceType;
	Position pos;
	Piece(): pieceType(pc::PieceType::empty), pos()
	{}
	Piece(const Position& pos, const bool& color): pieceType(pc::PieceType::empty), color(color), taken(false), pos(pos)
	{}
public: 
	void take() { taken = true; };
	bool isTaken() const { return taken; }
	bool getColor() const { return color;  }

	pc::PieceType getPieceType() const { return pieceType;  }

	Position getPosition() const { return pos; }
	void setPosition(const Position& pos) { this->pos = pos; }

	std::vector<Position> getValidMoves() const { return validMoves; }

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


	Piece(Piece& piece): validMoves(piece.validMoves), color(piece.color), taken(piece.taken), pieceType(piece.pieceType), pos(piece.pos)
	{}

	~Piece()
	{}
};

