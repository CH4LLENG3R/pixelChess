#pragma once
#include "Entity.h"
# include "../Piece.h"
class GFigure : public Entity
{
private:
public:
	GFigure(const Piece& piece)
	{
		switch (piece.getPieceType())
		{
		case pc::Pawn:
			break;
		case pc::Rook:
			break;
		case pc::Knight:
			break;
		case pc::Bishop:
			break;
		case pc::Queen:
			break;
		case pc::King:
			break;
		}
	}
};