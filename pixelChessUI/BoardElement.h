#pragma once
#include "Entity.h"
#include "Board.h"
#include "Cursor.h"
#include "Consts.h"
#include <SFML/Graphics.hpp>

#define POSSIBLE_MOVE_IMAGE_PATH "Graphics/PossibleMove/PossibleMove.png"

#define WHITE_PAWN_IMAGE_PATH "Graphics/figures/pawn.png"
#define BLACK_PAWN_IMAGE_PATH "Graphics/figures/pawnBlack.png"

#define WHITE_TOWER_IMAGE_PATH "Graphics/figures/tower.png"
#define BLACK_TOWER_IMAGE_PATH "Graphics/figures/towerBlack.png"

#define WHITE_KNIGHT_IMAGE_PATH "Graphics/figures/knight.png"
#define BLACK_KNIGHT_IMAGE_PATH "Graphics/figures/knightBlack.png"

#define WHITE_BISHOP_IMAGE_PATH "Graphics/figures/bishop.png"
#define BLACK_BISHOP_IMAGE_PATH "Graphics/figures/bishopBlack.png"

#define WHITE_QUEEN_IMAGE_PATH "Graphics/figures/queen.png"
#define BLACK_QUEEN_IMAGE_PATH "Graphics/figures/queenBlack.png"

#define WHITE_KING_IMAGE_PATH "Graphics/figures/king.png"
#define BLACK_KING_IMAGE_PATH "Graphics/figures/kingBlack.png"

class BoardElement : public Entity
{
private:
	short x, y;
protected:
	bool setX(short t_x) { if ((t_x >= 0) && (t_x <= 7)) x = t_x; else return 1; }
	bool setY(short t_y) { if ((t_y >= 0) && (t_y <= 7)) y = t_y; else return 1; }

	bool setXY(short t_x, short t_y) 
	{ 
		if (((t_x >= 0) && (t_x <= 7)) && ((t_y >= 0) && (t_y <= 7)))
		{
			x = t_x;
			y = t_y;
		}
		else return 1;
	}
public:
	short getX() { return x; }
	short getY() { return y; }
};

class PossibleMove : public BoardElement
{
public:
	sf::FloatRect hitbox;

	PossibleMove(Board& t_board, short t_x, short t_y);
	
	sf::Vector2f getPos() { return sprite.getPosition(); }
	
};