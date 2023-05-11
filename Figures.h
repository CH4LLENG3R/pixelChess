#pragma once
# include "Piece.h"

class King : public Piece
{
	std::vector<Position> getMoves() override
	{
		return std::vector<Position>();
	}

	bool isChecked(std::vector<Piece> arrangement)
	{
		return false;
	}

	bool isCheckmated(std::vector<Piece> arrangement)
	{
		return isChecked(arrangement) && validMoves.empty();
	}
public:
	King(): Piece()
	{}

	King(const bool& color): Piece(color)
	{}
};

class Queen : public Piece
{
	std::vector<Position> getMoves() override
	{
		return std::vector<Position>();
	}
public:
	Queen() : Piece()
	{}

	Queen(const bool& color) : Piece(color)
	{}
};

class Bishop : public Piece
{
	std::vector<Position> getMoves() override
	{
		return std::vector<Position>();
	}
public:
	Bishop() : Piece()
	{}

	Bishop(const bool& color) : Piece(color)
	{}
};

class Knight : public Piece
{
	std::vector<Position> getMoves() override
	{
		return std::vector<Position>();
	}
public:
	Knight() : Piece()
	{}

	Knight(const bool& color) : Piece(color)
	{}
};

class Rook : public Piece
{
	std::vector<Position> getMoves() override
	{
		return std::vector<Position>();
	}
public:
	Rook() : Piece()
	{}

	Rook(const bool& color) : Piece(color)
	{}
};

class Pawn : public Piece
{
	std::vector<Position> getMoves() override
	{
		return std::vector<Position>();
	}
public:
	Pawn() : Piece()
	{}

	Pawn(const bool& color) : Piece(color)
	{}
};