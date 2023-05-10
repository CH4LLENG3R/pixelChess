#pragma once

#include "Position.h"

struct GameVariables
{
	bool ActiveColor; // 1 - white, // 0 - black
	bool blackCastleKingSideAvailible;
	bool blackCastleQueenSideAvailible;
	bool whiteCastleKingSideAvailible;
	bool whiteCastleQueenSideAvailible;
	bool enPassantAvailible;
	Position enPassant;
	int halfMoveClock;
	int fullMoveNumber;
};