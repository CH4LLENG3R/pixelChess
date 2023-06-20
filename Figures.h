#pragma once
# include "Piece.h"

class King : public Piece
{
public:
	std::vector<Position> getMoves(std::shared_ptr<Piece>** arrangement) override
	{

		std::vector<Position> init{
			Position(pos.x - 1, pos.y + 1),
			Position(pos.x, pos.y + 1),
			Position(pos.x + 1, pos.y + 1),
			Position(pos.x + 1, pos.y),
			Position(pos.x + 1, pos.y - 1),
			Position(pos.x, pos.y - 1),
			Position(pos.x - 1, pos.y - 1),
			Position(pos.x - 1, pos.y)
		};

		std::vector<Position> res;

		for (Position p : init)
			if (p.x >= 0 && p.x < 8 && p.y >= 0 && p.y < 8 && (arrangement[p.y][p.x] == nullptr || arrangement[p.y][p.x]->getColor() != color))
				res.push_back(p);

		return res;
	}

	King() : Piece()
	{
		pieceType = pc::PieceType::King;
	}

	King(const Position& pos, const bool& color) : Piece(pos, color)
	{
		pieceType = pc::PieceType::King;
	}

	bool isChecked(std::shared_ptr<Piece>** arrangement)
	{
		// knight check
		if (posInBorder(pos.x - 1, pos.y + 2) && arrangement[pos.y + 2][pos.x - 1] != nullptr
			&& arrangement[pos.y + 2][pos.x - 1]->getPieceType() == pc::Knight && arrangement[pos.y + 2][pos.x - 1]->getColor() != color)
			return true;

		if (posInBorder(pos.x + 1, pos.y + 2) && arrangement[pos.y + 2][pos.x + 1] != nullptr
			&& arrangement[pos.y + 2][pos.x + 1]->getPieceType() == pc::Knight && arrangement[pos.y + 2][pos.x + 1]->getColor() != color)
			return true;

		if (posInBorder(pos.x + 2, pos.y + 1) && arrangement[pos.y + 1][pos.x + 2] != nullptr
			&& arrangement[pos.y + 1][pos.x + 2]->getPieceType() == pc::Knight && arrangement[pos.y + 1][pos.x + 2]->getColor() != color)
			return true;

		if (posInBorder(pos.x + 2, pos.y - 1) && arrangement[pos.y - 1][pos.x + 2] != nullptr
			&& arrangement[pos.y - 1][pos.x + 2]->getPieceType() == pc::Knight && arrangement[pos.y - 1][pos.x + 2]->getColor() != color)
			return true;

		if (posInBorder(pos.x + 1, pos.y - 2) && arrangement[pos.y - 2][pos.x + 1] != nullptr
			&& arrangement[pos.y - 2][pos.x + 1]->getPieceType() == pc::Knight && arrangement[pos.y - 2][pos.x + 1]->getColor() != color)
			return true;

		if (posInBorder(pos.x - 1, pos.y - 2) && arrangement[pos.y - 2][pos.x - 1] != nullptr
			&& arrangement[pos.y - 2][pos.x - 1]->getPieceType() == pc::Knight && arrangement[pos.y - 2][pos.x - 1]->getColor() != color)
			return true;

		if (posInBorder(pos.x - 2, pos.y - 1) && arrangement[pos.y - 1][pos.x - 2] != nullptr
			&& arrangement[pos.y - 1][pos.x - 2]->getPieceType() == pc::Knight && arrangement[pos.y - 1][pos.x - 2]->getColor() != color)
			return true;

		if (posInBorder(pos.x - 2, pos.y + 1) && arrangement[pos.y + 1][pos.x - 2] != nullptr
			&& arrangement[pos.y + 1][pos.x - 2]->getPieceType() == pc::Knight && arrangement[pos.y + 1][pos.x - 2]->getColor() != color)
			return true;

		// pawn check
		if (color == 1)
		{
			if (pos.y < 7 && pos.x < 7 && arrangement[pos.y + 1][pos.x + 1] != nullptr
				&& arrangement[pos.y + 1][pos.x + 1]->getPieceType() == pc::Pawn && arrangement[pos.y + 1][pos.x + 1]->getColor() != color)
				return true;

			if (pos.y < 7 && pos.x > 0 && arrangement[pos.y + 1][pos.x - 1] != nullptr
				&& arrangement[pos.y + 1][pos.x - 1]->getPieceType() == pc::Pawn && arrangement[pos.y + 1][pos.x - 1]->getColor() != color)
				return true;
		}
		else
		{
			if (pos.y > 0 && pos.x < 7 && arrangement[pos.y - 1][pos.x + 1] != nullptr
				&& arrangement[pos.y - 1][pos.x + 1]->getPieceType() == pc::Pawn && arrangement[pos.y - 1][pos.x + 1]->getColor() != color)
				return true;

			if (pos.y > 0 && pos.x > 0 && arrangement[pos.y - 1][pos.x - 1] != nullptr
				&& arrangement[pos.y - 1][pos.x - 1]->getPieceType() == pc::Pawn && arrangement[pos.y - 1][pos.x - 1]->getColor() != color)
				return true;
		}

		// vertical line check
		pc::PieceType otherType;
		for (short y = pos.y + 1; y < 8; y++)
		{
			if (arrangement[y][pos.x] == nullptr)
				continue;

			otherType = arrangement[y][pos.x].get()->getPieceType();
			if (arrangement[y][pos.x]->getColor() != this->color && (otherType == pc::Queen || otherType == pc::Rook))
				return true;

			break;
		}

		for (short y = pos.y - 1; y >= 0; y--)
		{
			if (arrangement[y][pos.x] == nullptr)
				continue;

			otherType = arrangement[y][pos.x].get()->getPieceType();
			if (arrangement[y][pos.x]->getColor() != this->color && (otherType == pc::Queen || otherType == pc::Rook))
				return true;

			break;
		}

		//horizontal line check
		for (short x = pos.x + 1; x < 8; x++)
		{
			if (arrangement[pos.y][x] == nullptr)
				continue;

			otherType = arrangement[pos.y][x].get()->getPieceType();
			if (arrangement[pos.y][x]->getColor() != this->color && (otherType == pc::Queen || otherType == pc::Rook))
				return true;

			break;
		}

		for (short x = pos.x - 1; x >= 0; x--)
		{
			if (arrangement[pos.y][x] == nullptr)
				continue;

			otherType = arrangement[pos.y][x].get()->getPieceType();
			if (arrangement[pos.y][x]->getColor() != this->color && (otherType == pc::Queen || otherType == pc::Rook))
				return true;

			break;
		}

		//diagonal line check
		for (short i = 1; i < 8; i++)
		{
			if (pos.x + i > 7 || pos.y + i > 7)
				break;

			if (arrangement[pos.y + i][pos.x + i] == nullptr)
				continue;

			otherType = arrangement[pos.y + i][pos.x + i].get()->getPieceType();
			if (arrangement[pos.y + i][pos.x + i]->getColor() != this->color && (otherType == pc::Queen || otherType == pc::Bishop))
				return true;

			break;
		}

		for (short i = 1; i < 8; i++)
		{
			if (pos.x - i < 0 || pos.y - i < 0)
				break;

			if (arrangement[pos.y - i][pos.x - i] == nullptr)
				continue;

			otherType = arrangement[pos.y - i][pos.x - i].get()->getPieceType();
			if (arrangement[pos.y - i][pos.x - i]->getColor() != this->color && (otherType == pc::Queen || otherType == pc::Bishop))
				return true;

			break;
		}

		for (short i = 1; i < 8; i++)
		{
			if (pos.x - i < 0 || pos.y + i > 7)
				break;

			if (arrangement[pos.y + i][pos.x - i] == nullptr)
				continue;

			otherType = arrangement[pos.y + i][pos.x - i].get()->getPieceType();
			if (arrangement[pos.y + i][pos.x - i]->getColor() != this->color && (otherType == pc::Queen || otherType == pc::Bishop))
				return true;

			break;
		}

		for (short i = 1; i < 8; i++)
		{
			if (pos.x + i > 7 || pos.y - i < 0)
				break;

			if (arrangement[pos.y - i][pos.x + i] == nullptr)
				continue;

			otherType = arrangement[pos.y - i][pos.x + i].get()->getPieceType();
			if (arrangement[pos.y - i][pos.x + i]->getColor() != this->color && (otherType == pc::Queen || otherType == pc::Bishop))
				return true;

			break;
		}

		return false;
		
	}

	bool isKingSideCastlingAvailible(std::shared_ptr<Piece>** arrangement)
	{
		for (short x = pos.x + 1; x < 8; x++)
		{
			if (arrangement[pos.y][x] == nullptr)
				continue;
			if (arrangement[pos.y][x]->getPieceType() == pc::Rook && arrangement[pos.y][x]->getColor() == color && x == 7)
				return true;
			return false;
		}
	}

	bool isQueenSideCastlingAvailible(std::shared_ptr<Piece>** arrangement)
	{
		for (short x = pos.x - 1; x >= 0; x--)
		{
			if (arrangement[pos.y][x] == nullptr)
				continue;
			if (arrangement[pos.y][x]->getPieceType() == pc::Rook && arrangement[pos.y][x]->getColor() == color && x == 0)
				return true;
			return false;
		}
	}
};

class Queen : public Piece
{
	std::vector<Position> getMoves(std::shared_ptr<Piece>** arrangement) override
	{
		//Rook like movement
		std::vector<Position> moves;
		for (short y = pos.y + 1; y < 8; y++)
		{
			if (arrangement[y][pos.x] == nullptr)
			{
				moves.push_back(Position(pos.x, y));
				continue;
			}

			if (arrangement[y][pos.x].get()->getColor() != color)
			{
				moves.push_back(Position(pos.x, y));
				break;
			}

			if (arrangement[y][pos.x].get()->getColor() == color)
				break;
		}

		for (short y = pos.y - 1; y >= 0; y--)
		{
			if (arrangement[y][pos.x] == nullptr)
			{
				moves.push_back(Position(pos.x, y));
				continue;
			}

			if (arrangement[y][pos.x].get()->getColor() != color)
			{
				moves.push_back(Position(pos.x, y));
				break;
			}

			if (arrangement[y][pos.x].get()->getColor() == color)
				break;
		}

		for (short x = pos.x + 1; x < 8; x++)
		{
			if (arrangement[pos.y][x] == nullptr)
			{
				moves.push_back(Position(x, pos.y));
				continue;
			}

			if (arrangement[pos.y][x].get()->getColor() != color)
			{
				moves.push_back(Position(x, pos.y));
				break;
			}

			if (arrangement[pos.y][x].get()->getColor() == color)
				break;
		}

		for (short x = pos.x - 1; x >= 0; x--)
		{
			if (arrangement[pos.y][x] == nullptr)
			{
				moves.push_back(Position(x, pos.y));
				continue;
			}

			if (arrangement[pos.y][x].get()->getColor() != color)
			{
				moves.push_back(Position(x, pos.y));
				break;
			}

			if (arrangement[pos.y][x].get()->getColor() == color)
				break;
		}

		//Bishop like movement

		for (short i = 1; i < 8; i++)
		{
			if (pos.x + i > 7 || pos.y + i > 7)
				break;

			if (arrangement[pos.y + i][pos.x + i] == nullptr)
			{
				moves.push_back(Position(pos.x + i, pos.y + i));
				continue;
			}

			if (arrangement[pos.y + i][pos.x + i].get()->getColor() != color)
			{
				moves.push_back(Position(pos.x + i, pos.y + i));
				break;
			}

			if (arrangement[pos.y + i][pos.x + i].get()->getColor() == color)
				break;
		}

		for (short i = 1; i < 8; i++)
		{
			if (pos.x - i < 0 || pos.y - i < 0)
				break;

			if (arrangement[pos.y - i][pos.x - i] == nullptr)
			{
				moves.push_back(Position(pos.x - i, pos.y - i));
				continue;
			}

			if (arrangement[pos.y - i][pos.x - i].get()->getColor() != color)
			{
				moves.push_back(Position(pos.x - i, pos.y - i));
				break;
			}

			if (arrangement[pos.y - i][pos.x - i].get()->getColor() == color)
				break;
		}

		for (short i = 1; i < 8; i++)
		{
			if (pos.x - i < 0 || pos.y + i > 7)
				break;
			if (arrangement[pos.y + i][pos.x - i] == nullptr)
			{
				moves.push_back(Position(pos.x - i, pos.y + i));
				continue;
			}

			if (arrangement[pos.y + i][pos.x - i].get()->getColor() != color)
			{
				moves.push_back(Position(pos.x - i, pos.y + i));
				break;
			}

			if (arrangement[pos.y + i][pos.x - i].get()->getColor() == color)
				break;
		}

		for (short i = 1; i < 8; i++)
		{
			if (pos.x + i > 7 || pos.y - i < 0)
				break;

			if (arrangement[pos.y - i][pos.x + i] == nullptr)
			{
				moves.push_back(Position(pos.x + i, pos.y - i));
				continue;
			}

			if (arrangement[pos.y - i][pos.x + i].get()->getColor() != color)
			{
				moves.push_back(Position(pos.x + i, pos.y - i));
				break;
			}

			if (arrangement[pos.y - i][pos.x + i].get()->getColor() == color)
				break;
		}

		return moves;

	}
public:
	Queen() : Piece()
	{
		pieceType = pc::PieceType::Queen;
	}

	Queen(const Position& pos, const bool& color) : Piece(pos, color)
	{
		pieceType = pc::PieceType::Queen;
	}
};

class Bishop : public Piece
{
	std::vector<Position> getMoves(std::shared_ptr<Piece>** arrangement) override
	{
		std::vector<Position> moves;

		for (short i = 1; i < 8; i++)
		{
			if (pos.x + i > 7 || pos.y + i > 7)
				break;

			if (arrangement[pos.y + i][pos.x + i] == nullptr)
			{
				moves.push_back(Position(pos.x + i, pos.y + i));
				continue;
			}

			if (arrangement[pos.y + i][pos.x + i].get()->getColor() != color)
			{
				moves.push_back(Position(pos.x + i, pos.y + i));
				break;
			}

			if (arrangement[pos.y + i][pos.x + i].get()->getColor() == color)
				break;
		}

		for (short i = 1; i < 8; i++)
		{
			if (pos.x - i < 0 || pos.y - i < 0)
				break;

			if (arrangement[pos.y - i][pos.x - i] == nullptr)
			{
				moves.push_back(Position(pos.x - i, pos.y - i));
				continue;
			}

			if (arrangement[pos.y - i][pos.x - i].get()->getColor() != color)
			{
				moves.push_back(Position(pos.x - i, pos.y - i));
				break;
			}

			if (arrangement[pos.y - i][pos.x - i].get()->getColor() == color)
				break;
		}

		for (short i = 1; i < 8; i++)
		{
			if (pos.x - i < 0 || pos.y + i > 7)
				break;
			if (arrangement[pos.y + i][pos.x - i] == nullptr)
			{
				moves.push_back(Position(pos.x - i, pos.y + i));
				continue;
			}

			if (arrangement[pos.y + i][pos.x - i].get()->getColor() != color)
			{
				moves.push_back(Position(pos.x - i, pos.y + i));
				break;
			}

			if (arrangement[pos.y + i][pos.x - i].get()->getColor() == color)
				break;
		}

		for (short i = 1; i < 8; i++)
		{
			if (pos.x + i > 7 || pos.y - i < 0)
				break;

			if (arrangement[pos.y - i][pos.x + i] == nullptr)
			{
				moves.push_back(Position(pos.x + i, pos.y - i));
				continue;
			}

			if (arrangement[pos.y - i][pos.x + i].get()->getColor() != color)
			{
				moves.push_back(Position(pos.x + i, pos.y - i));
				break;
			}

			if (arrangement[pos.y - i][pos.x + i].get()->getColor() == color)
				break;
		}

		return moves;
	}
public:
	Bishop() : Piece()
	{
		pieceType = pc::PieceType::Bishop;
	}

	Bishop(const Position& pos, const bool& color) : Piece(pos, color)
	{
		pieceType = pc::PieceType::Bishop;
	}
};

class Knight : public Piece
{
	std::vector<Position> getMoves(std::shared_ptr<Piece>** arrangement) override
	{
		std::vector<Position> moves;
		if (posInBorder(pos.x - 1, pos.y + 2) && (arrangement[pos.y + 2][pos.x - 1] == nullptr || arrangement[pos.y + 2][pos.x - 1]->getColor() != color))
			moves.push_back(Position(pos.x - 1, pos.y + 2));

		if (posInBorder(pos.x + 1, pos.y + 2) && (arrangement[pos.y + 2][pos.x + 1] == nullptr || arrangement[pos.y + 2][pos.x + 1]->getColor() != color))
			moves.push_back(Position(pos.x + 1, pos.y + 2));

		if (posInBorder(pos.x + 2, pos.y + 1) && (arrangement[pos.y + 1][pos.x + 2] == nullptr || arrangement[pos.y + 1][pos.x + 2]->getColor() != color))
			moves.push_back(Position(pos.x + 2, pos.y + 1));

		if (posInBorder(pos.x + 2, pos.y - 1) && (arrangement[pos.y - 1][pos.x + 2] == nullptr || arrangement[pos.y - 1][pos.x + 2]->getColor() != color))
			moves.push_back(Position(pos.x + 2, pos.y - 1));

		if (posInBorder(pos.x + 1, pos.y - 2) && (arrangement[pos.y - 2][pos.x + 1] == nullptr || arrangement[pos.y - 2][pos.x + 1]->getColor() != color))
			moves.push_back(Position(pos.x + 1, pos.y - 2));

		if (posInBorder(pos.x - 1, pos.y - 2) && (arrangement[pos.y - 2][pos.x - 1] == nullptr || arrangement[pos.y - 2][pos.x - 1]->getColor() != color))
			moves.push_back(Position(pos.x - 1, pos.y - 2));

		if (posInBorder(pos.x - 2, pos.y - 1) && (arrangement[pos.y - 1][pos.x - 2] == nullptr || arrangement[pos.y - 1][pos.x - 2]->getColor() != color))
			moves.push_back(Position(pos.x - 2, pos.y - 1));

		if (posInBorder(pos.x - 2, pos.y + 1) && (arrangement[pos.y + 1][pos.x - 2] == nullptr || arrangement[pos.y + 1][pos.x - 2]->getColor() != color))
			moves.push_back(Position(pos.x - 2, pos.y + 1));

		return moves;
	}
public:
	Knight() : Piece()
	{
		pieceType = pc::PieceType::Knight;
	}

	Knight(const Position& pos, const bool& color) : Piece(pos, color)
	{
		pieceType = pc::PieceType::Knight;
	}
};

class Rook : public Piece
{
	std::vector<Position> getMoves(std::shared_ptr<Piece>** arrangement) override
	{
		std::vector<Position> moves;
		for (short y = pos.y + 1; y < 8; y++)
		{
			if (arrangement[y][pos.x] == nullptr)
			{
				moves.push_back(Position(pos.x, y));
				continue;
			}

			if (arrangement[y][pos.x].get()->getColor() != color)
			{
				moves.push_back(Position(pos.x, y));
				break;
			}

			if (arrangement[y][pos.x].get()->getColor() == color)
				break;
		}

		for (short y = pos.y - 1; y >= 0; y--)
		{
			if (arrangement[y][pos.x] == nullptr)
			{
				moves.push_back(Position(pos.x, y));
				continue;
			}

			if (arrangement[y][pos.x].get()->getColor() != color)
			{
				moves.push_back(Position(pos.x, y));
				break;
			}

			if (arrangement[y][pos.x].get()->getColor() == color)
				break;
		}

		for (short x = pos.x + 1; x < 8; x++)
		{
			if (arrangement[pos.y][x] == nullptr)
			{
				moves.push_back(Position(x, pos.y));
				continue;
			}

			if (arrangement[pos.y][x].get()->getColor() != color)
			{
				moves.push_back(Position(x, pos.y));
				break;
			}

			if (arrangement[pos.y][x].get()->getColor() == color)
				break;
		}

		for (short x = pos.x - 1; x >= 0; x--)
		{
			if (arrangement[pos.y][x] == nullptr)
			{
				moves.push_back(Position(x, pos.y));
				continue;
			}

			if (arrangement[pos.y][x].get()->getColor() != color)
			{
				moves.push_back(Position(x, pos.y));
				break;
			}

			if (arrangement[pos.y][x].get()->getColor() == color)
				break;
		}

		return moves;
	}
public:
	Rook() : Piece()
	{
		pieceType = pc::PieceType::Rook;
	}

	Rook(const Position& pos, const bool& color) : Piece(pos, color)
	{
		pieceType = pc::PieceType::Rook;
	}
};

class Pawn : public Piece
{
	std::vector<Position> getMoves(std::shared_ptr<Piece>** arrangement) override
	{
		std::vector<Position> moves;

		if (color == 1 && arrangement[pos.y + 1][pos.x] == nullptr)
			moves.push_back(Position(pos.x, pos.y + 1));
		else if (color == 0 && arrangement[pos.y - 1][pos.x] == nullptr)
			moves.push_back(Position(pos.x, pos.y - 1));

		if (color == 1 && pos.y == 1 && arrangement[pos.y + 2][pos.x] == nullptr)
			moves.push_back(Position(pos.x, pos.y + 2));
		else if (color == 0 && pos.y == 6 && arrangement[pos.y - 2][pos.x] == nullptr)
			moves.push_back(Position(pos.x, pos.y - 2));

		// capture
		if (color == 1)
		{
			if (pos.x > 0 && arrangement[pos.y + 1][pos.x - 1] != nullptr && arrangement[pos.y + 1][pos.x - 1]->getColor() != color)
				moves.push_back(Position(pos.x - 1, pos.y + 1));
			if(pos.x < 7 && arrangement[pos.y + 1][pos.x + 1] != nullptr && arrangement[pos.y + 1][pos.x + 1]->getColor() != color)
				moves.push_back(Position(pos.x + 1, pos.y + 1));
		}
		else
		{
			if (pos.x > 0 && arrangement[pos.y - 1][pos.x - 1] != nullptr && arrangement[pos.y - 1][pos.x - 1]->getColor() != color)
				moves.push_back(Position(pos.x - 1, pos.y - 1));
			if (pos.x < 7 && arrangement[pos.y - 1][pos.x + 1] != nullptr && arrangement[pos.y - 1][pos.x + 1]->getColor() != color)
				moves.push_back(Position(pos.x + 1, pos.y - 1));
		}


		return moves;
	}
public:
	Pawn() : Piece()
	{
		pieceType = pc::PieceType::Pawn;
	}

	Pawn(const Position& pos, const bool& color) : Piece(pos, color)
	{
		pieceType = pc::PieceType::Pawn;
	}
};