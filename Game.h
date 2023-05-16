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
			piece->setValidMoves(piece->getMoves(arrangement));
		}
	}

	bool isGameOver()
	{
		return false; 
	}
public:
	std::vector<Position> getPieceMoves(short x, short y)
	{
		return arrangement[y][x]->getMoves(arrangement);
	}

	bool move(Position from, Position to)
	{
		processValidMoves();
		//chech if move is valid
		bool valid = false;
		for (Position vp : arrangement[from.y][from.x].get()->getValidMoves())
			if (to == vp)
				valid = true;

		if (!valid)
			return false;
		//perform move
		arrangement[to.y][to.x].reset();
		arrangement[from.y][from.x].get()->setPosition(to);
		arrangement[to.y][to.x].swap(arrangement[from.y][from.x]);

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

				std::shared_ptr<Piece> temp = arrangement[y][x];
				if (temp == nullptr)
				{
					std::cout << ' ';
					continue;
				}
				Piece piece = *temp.get();
				if (piece.getColor())
				{
					if (piece.getPieceType() == pc::PieceType::Pawn)
						std::cout << 'P';
					else if (piece.getPieceType() == pc::PieceType::Rook)
						std::cout << 'R';
					else if (piece.getPieceType() == pc::PieceType::Knight)
						std::cout << 'N';
					else if (piece.getPieceType() == pc::PieceType::Bishop)
						std::cout << 'B';
					else if (piece.getPieceType() == pc::PieceType::Queen)
						std::cout << 'Q';
					else if (piece.getPieceType() == pc::PieceType::King)
						std::cout << 'K';
				}
				else
				{
					if (piece.getPieceType() == pc::PieceType::Pawn)
						std::cout << 'p';
					else if (piece.getPieceType() == pc::PieceType::Rook)
						std::cout << 'r';
					else if (piece.getPieceType() == pc::PieceType::Knight)
						std::cout << 'n';
					else if (piece.getPieceType() == pc::PieceType::Bishop)
						std::cout << 'b';
					else if (piece.getPieceType() == pc::PieceType::Queen)
						std::cout << 'q';
					else if (piece.getPieceType() == pc::PieceType::King)
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