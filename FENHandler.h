#pragma once

#include <string>
#include <vector>
#include <regex>
#include <stdexcept>

#include "Figures.h"
#include "GameVariables.h"
#include "Position.h"

class FENHandler
{
	std::vector<Piece*> arrangement;
	GameVariables variables;
public:
	std::vector<Piece*> getArrangement() { return arrangement; }

	bool isFENValid(std::string FEN)
	{
		return std::regex_match(FEN, std::regex("^([pnbrqkPNBRQK1-8]{1,8}\\/?){8}\\s+(b|w)\\s+(-|K?Q?k?q)\\s+(-|[a-h][3-6])\\s+(\\d+)\\s+(\\d+)\\s*$", std::regex_constants::ECMAScript | std::regex_constants::icase));
	}

	FENHandler(std::string FEN)
	{
		if (!isFENValid(FEN))
		{
			throw std::invalid_argument("FEN is invalid");
			return;
		}

		// get arrangement
		int y = 7;
		int x = 0;
		bool arrangementEnd = false;
		int i = 0;
		for (; i < 64; i++)
		{
			switch (FEN[i])
			{
			case 'r':
				arrangement.push_back(new Rook(Position(x, y), 0));
				break;
			case 'n':
				arrangement.push_back(new Knight(Position(x, y), 0));
				break;
			case 'b':
				arrangement.push_back(new Bishop(Position(x, y), 0));
				break;
			case 'q':
				arrangement.push_back(new Queen(Position(x, y), 0));
				break;
			case 'k':
				arrangement.push_back(new King(Position(x, y), 0));
				break;
			case 'p':
				arrangement.push_back(new Pawn(Position(x, y), 0));
				break;
			case 'R':
				arrangement.push_back(new Rook(Position(x, y), 1));
				break;
			case 'N':
				arrangement.push_back(new Knight(Position(x, y), 1));
				break;
			case 'B':
				arrangement.push_back(new Bishop(Position(x, y), 1));
				break;
			case 'Q':
				arrangement.push_back(new Queen(Position(x, y), 1));
				break;
			case 'K':
				arrangement.push_back(new King(Position(x, y), 1));
				break;
			case 'P':
				arrangement.push_back(new Pawn(Position(x, y), 1));
				break;
			case '/':
				x = 0;
				y--;
				continue;
			case ' ':
				arrangementEnd = true;
				break;
			default:
				int number = FEN[i] - 48;
				if (number >= 0 && number <= 8)
					x += number;
			}
			if (arrangementEnd)
				break;
			x++;
		}

		// get active color
		i++;
		if (FEN[i] == 'w')
			variables.ActiveColor = true;
		else
			variables.ActiveColor = false;
		i++;

		// get castle availibility
		variables.whiteCastleKingSideAvailible = false;
		variables.whiteCastleQueenSideAvailible = false;
		variables.blackCastleKingSideAvailible = false;
		variables.blackCastleQueenSideAvailible = false;
		i++;
		for (;;i++)
		{
			switch (FEN[i])
			{
			case 'K':
				variables.whiteCastleKingSideAvailible = true;
				continue;
			case 'Q':
				variables.whiteCastleQueenSideAvailible = true;
				continue;
			case 'k':
				variables.blackCastleKingSideAvailible = true;
				continue;
			case 'q':
				variables.blackCastleQueenSideAvailible = true;
				continue;
			case '-':
				continue;
			case ' ':
				break;
			}
			break;
		}

		//get en passant
		variables.enPassantAvailible = false;
		variables.enPassant = Position();
		i++;
		if (FEN[i] != '-')
		{
			variables.enPassantAvailible = true;
			variables.enPassant = Position(FEN[i] - 'a', FEN[++i] - 49);
		}
		i++;

		//get halfmove clock
		variables.halfMoveClock = 0;
		i++;
		while (FEN[i] != ' ')
		{	
			variables.halfMoveClock *= 10;
			variables.halfMoveClock += FEN[i] - 48;
			i++;
		}

		//get fullmove number
		variables.fullMoveNumber = 0;
		i++;
		while (i<FEN.size())
		{
			variables.fullMoveNumber *= 10;
			variables.fullMoveNumber += FEN[i] - 48;
			i++;
		}
	}

	static std::string getFEN(std::shared_ptr<Piece>** arrangement,const GameVariables& variables)
	{
		std::string FEN;
		int freeSpaces;
		for (short y = 7; y >= 0; y--)
		{
			freeSpaces = 0;
			for (short x = 0; x < 8; x++)
			{
				if (arrangement[y][x] == nullptr)
				{
					freeSpaces++;
					continue;
				}

				if (freeSpaces != 0)
				{
					FEN += char(freeSpaces + '0');
					freeSpaces = 0;
				}
				
				Piece p = *arrangement[y][x];

				if (p.getColor() == 1)
				{
					if (p.getPieceType() == pc::Pawn)
						FEN.append("P");
					else if (p.getPieceType() == pc::Rook)
						FEN.append("R");
					else if (p.getPieceType() == pc::Knight)
						FEN.append("N");
					else if (p.getPieceType() == pc::Bishop)
						FEN.append("B");
					else if (p.getPieceType() == pc::Queen)
						FEN.append("Q");
					else if (p.getPieceType() == pc::King)
						FEN.append("K");
				}
				else
				{
					if (p.getPieceType() == pc::Pawn)
						FEN.append("p");
					else if (p.getPieceType() == pc::Rook)
						FEN.append("r");
					else if (p.getPieceType() == pc::Knight)
						FEN.append("n");
					else if (p.getPieceType() == pc::Bishop)
						FEN.append("b");
					else if (p.getPieceType() == pc::Queen)
						FEN.append("q");
					else if (p.getPieceType() == pc::King)
						FEN.append("k");
				}
			}

			if (freeSpaces != 0)
			{
				FEN += char(freeSpaces + '0');
				freeSpaces = 0;
			}

			FEN.append("/");
		}

		return FEN;
	}
};

