#pragma once
#include <vector>
#include <memory>
#include <typeinfo>

#include "Settings.h"
#include "Clock.h"
#include "GameHistory.h"
#include "InputHandler.h"
#include "Piece.h"
#include "Figures.h"
#include "PieceTypes.h"
#include "FENHandler.h"
#include "GameVariables.h"

class Game
{
protected:
	std::shared_ptr<Piece>** arrangement;
	std::vector<std::shared_ptr<Piece>> arrangementVec;
	std::shared_ptr<King> whiteKing;
	std::shared_ptr<King> blackKing;
	GameVariables variables;
private:
	void processValidMoves()
	{
		for (std::shared_ptr<Piece> p : arrangementVec)
		{
			Piece* piece = p.get();
			if(!piece->isTaken())
				piece->setValidMoves(piece->getMoves(arrangement));
		}
	}

	bool isGameOver()
	{
		return false; 
	}
public:
	bool isFigure(Position at)
	{
		return arrangement[at.y][at.x] != nullptr;
	}

	std::vector<Position> getPieceMoves(short x, short y)
	{
		if (isFigure(Position(x, y)))
			return arrangement[y][x]->getMoves(arrangement);
		else
			return std::vector<Position>();
	}

	bool isPromotion(Position from, Position to)
	{
		if (!isFigure(from))
			return false;

		if (arrangement[from.y][from.x]->getPieceType() == pc::Pawn && arrangement[from.y][from.x]->getColor()==1 && to.y == 7)
			return true;
		if (arrangement[from.y][from.x]->getPieceType() == pc::Pawn && arrangement[from.y][from.x]->getColor() == 0 && to.y == 0)
			return true;

		return false;
	}

	bool move(Position from, Position to, char promoteTo = 'Q')
	{
		processValidMoves();
		//chech if move is valid
		if (!isFigure(from))
			return false;

		bool valid = false;
		for (Position vp : arrangement[from.y][from.x]->getValidMoves())
			if (to == vp)
				valid = true;

		if (!valid)
			return false;

		//update game variables

		//en passant
		if (arrangement[from.y][from.x]->getPieceType() == pc::Pawn)
		{
			variables.enPassantAvailible = false;

			if (from.y == 1 && to.y == 3)
			{
				variables.enPassantAvailible = true;
				variables.enPassant = Position(from.x, 2);
			}

			if ((from.y == 6 && to.y == 4))
			{
				variables.enPassantAvailible = true;
				variables.enPassant = Position(from.x, 5);
			}
		}
		else
			variables.enPassantAvailible = false;

		// castling
		if (arrangement[from.y][from.x]->getPieceType() == pc::King)
		{
			if (arrangement[from.y][from.x]->getColor() == 1)
			{
				variables.whiteCastleKingSideAvailible = false;
				variables.whiteCastleQueenSideAvailible = false;
			}
			else
			{
				variables.blackCastleKingSideAvailible = false;
				variables.blackCastleQueenSideAvailible = false;
			}
		}

		if (arrangement[from.y][from.x]->getPieceType() == pc::Rook)
		{
			if (arrangement[from.y][from.x]->getColor() == 1)
			{
				if (from.y == 0)
				{
					if (from.x == 7)
						variables.whiteCastleKingSideAvailible = false;
					else if(from.x == 0)
						variables.whiteCastleQueenSideAvailible = false;
				}
			}
			else
			{
				if (from.y == 7)
				{
					if (from.x == 7)
						variables.blackCastleKingSideAvailible = false;
					else if (from.x == 0)
						variables.blackCastleQueenSideAvailible = false;
				}
			}
		}

		// half move clock
		if (arrangement[to.y][to.x] != nullptr || arrangement[from.y][from.x]->getPieceType() == pc::Pawn)
			variables.halfMoveClock = 0;
		else
			variables.halfMoveClock++;
			
		// full move clock
		if (variables.ActiveColor == 0)
			variables.fullMoveNumber++;

		//perform move
		if (arrangement[to.y][to.x] != nullptr)
			arrangement[to.y][to.x]->take();

		arrangement[to.y][to.x].reset();
		arrangement[from.y][from.x].get()->setPosition(to);
		arrangement[to.y][to.x].swap(arrangement[from.y][from.x]);

		//promote
		if (arrangement[to.y][to.x]->getPieceType() == pc::Pawn && (to.y == 0 || to.y == 7))
		{
			switch (promoteTo)
			{
			case 'Q':
				arrangementVec.push_back(std::shared_ptr<Piece>(new Queen(Position(to.x, to.y), arrangement[to.y][to.x]->getColor())));
				break;
			case 'B':
				arrangementVec.push_back(std::shared_ptr<Piece>(new Bishop(Position(to.x, to.y), arrangement[to.y][to.x]->getColor())));
				break;
			case 'N':
				arrangementVec.push_back(std::shared_ptr<Piece>(new Knight(Position(to.x, to.y), arrangement[to.y][to.x]->getColor())));
				break;
			case 'R':
				arrangementVec.push_back(std::shared_ptr<Piece>(new Rook(Position(to.x, to.y), arrangement[to.y][to.x]->getColor())));
				break;
			}

			arrangement[to.y][to.x] = arrangementVec.back();

			//remove promoted pawn from vector
			for (int i = 0; i < arrangementVec.size(); i++)
			{
				Piece* temp = arrangementVec[i].get();
				if (temp->getPieceType() == pc::Pawn && (temp->getPosition().y == 0 || temp->getPosition().y == 7))
					arrangementVec.erase(arrangementVec.begin() + i);
			}
		}

		//swap turn
		variables.ActiveColor = !variables.ActiveColor;

		return true;
	}

	bool move(std::string AN)
	{
		return true;
	}

	void debug()
	{
		//show arrangement
		for (short y = 7; y >= 0; y--)
		{
			std::cout << y;
			for (short x = 0; x < 8; x++)
			{
				std::cout << ' ';

				if (arrangement[y][x] == nullptr)
				{
					std::cout << ' ';
					continue;
				}
				Piece* piece = arrangement[y][x].get();
				if (piece->getColor())
				{
					if (piece->getPieceType() == pc::PieceType::Pawn)
						std::cout << 'P';
					else if (piece->getPieceType() == pc::PieceType::Rook)
						std::cout << 'R';
					else if (piece->getPieceType() == pc::PieceType::Knight)
						std::cout << 'N';
					else if (piece->getPieceType() == pc::PieceType::Bishop)
						std::cout << 'B';
					else if (piece->getPieceType() == pc::PieceType::Queen)
						std::cout << 'Q';
					else if (piece->getPieceType() == pc::PieceType::King)
						std::cout << 'K';
				}
				else
				{
					if (piece->getPieceType() == pc::PieceType::Pawn)
						std::cout << 'p';
					else if (piece->getPieceType() == pc::PieceType::Rook)
						std::cout << 'r';
					else if (piece->getPieceType() == pc::PieceType::Knight)
						std::cout << 'n';
					else if (piece->getPieceType() == pc::PieceType::Bishop)
						std::cout << 'b';
					else if (piece->getPieceType() == pc::PieceType::Queen)
						std::cout << 'q';
					else if (piece->getPieceType() == pc::PieceType::King)
						std::cout << 'k';
				}
			}
			std::cout << '\n';
		}
		std::cout << ' ';
		for (short x = 0; x < 8; x++)
			std::cout << ' ' << char('A' + x);
		std::cout << "\n ";
		for (short x = 0; x < 8; x++)
			std::cout << ' ' << x;
		std::cout << '\n';

		//show variables
		std::cout << "white king checked: " << whiteKing->isChecked(arrangement) << '\n';
		std::cout << "black king checked: " << blackKing->isChecked(arrangement) << '\n';
	}

	std::string getFEN()
	{
		return FENHandler::getFEN(arrangement, variables);
	}

	Game()
	{
		arrangement = new std::shared_ptr<Piece>*[8];
		for (size_t i = 0; i < 8; i++)
			arrangement[i] = new std::shared_ptr<Piece>[8];

		std::string basicFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
		FENHandler fenHandler(basicFEN);
		variables = fenHandler.getVariables();

		std::vector<Piece*> initialArrangement = fenHandler.getArrangement();

		int x, y;
		for (Piece* p : initialArrangement)
		{
			x = p->getPosition().x;
			y = p->getPosition().y;

			arrangementVec.push_back(std::shared_ptr<Piece>(p));
			arrangement[y][x] = arrangementVec.back();

			if (typeid(King) == typeid(*p))
			{
				if (p->getColor() == 1)
					whiteKing = std::dynamic_pointer_cast<King>(arrangement[y][x]);
				else
					blackKing = std::dynamic_pointer_cast<King>(arrangement[y][x]);
			}
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
		arrangementVec.clear();
		delete[] arrangement;
	}
};