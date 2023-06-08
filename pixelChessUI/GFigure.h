#pragma once
#include "Entity.h"
#include "Consts.h"
#include "../Piece.h"
class GFigure : public Entity
{
private:
	const Piece* piece;
	bool pickedUp;
public:

	Position getBoardPos() { return piece->getPosition(); }

	std::vector<Position> getValidMoves() { return piece->getValidMoves(); }


	sf::FloatRect getGlobalBounds() { return sprite.getGlobalBounds(); }

	bool isTaken() { return piece->isTaken(); }
	bool isPickedUp() { return pickedUp; }
	void setPickedUp(const bool pickedUp) { this->pickedUp = pickedUp; }

	void setPosition(sf::Vector2f pos)
	{
		sprite.setPosition(pos);
	}

	void resetPosition(sf::Vector2f** positions)
	{
		Position pos = piece->getPosition();
		sf::Vector2f posOnScreen = positions[pos.x][7 - pos.y];
		sprite.setPosition(posOnScreen.x, posOnScreen.y);
		sprite.setTexture(texture, true);
	}

	GFigure(const Piece* piece, sf::Vector2f** positions): piece(piece)
	{
		pickedUp = false;

		Position pos = piece->getPosition();
		sf::Vector2f posOnScreen = positions[pos.x][7 - pos.y];
		sprite.setPosition(posOnScreen.x, posOnScreen.y);
		
		if (piece->getColor())
		{
			switch (piece->getPieceType())
			{
			case pc::Pawn:
				texture.loadFromFile(WHITE_PAWN_TEXTURE_PATH);
				break;
			case pc::Rook:
				texture.loadFromFile(WHITE_ROOK_TEXTURE_PATH);
				break;
			case pc::Knight:
				texture.loadFromFile(WHITE_KNIGHT_TEXTURE_PATH);
				break;
			case pc::Bishop:
				texture.loadFromFile(WHITE_BISHOP_TEXTURE_PATH);
				break;
			case pc::Queen:
				texture.loadFromFile(WHITE_QUEEN_TEXTURE_PATH);
				break;
			case pc::King:
				texture.loadFromFile(WHITE_KING_TEXTURE_PATH);
				break;
			}

		}
		else
		{
			switch (piece->getPieceType())
			{
			case pc::Pawn:
				texture.loadFromFile(BLACK_PAWN_TEXTURE_PATH);
				break;
			case pc::Rook:
				texture.loadFromFile(BLACK_ROOK_TEXTURE_PATH);
				break;
			case pc::Knight:
				texture.loadFromFile(BLACK_KNIGHT_TEXTURE_PATH);
				break;
			case pc::Bishop:
				texture.loadFromFile(BLACK_BISHOP_TEXTURE_PATH);
				break;
			case pc::Queen:
				texture.loadFromFile(BLACK_QUEEN_TEXTURE_PATH);
				break;
			case pc::King:
				texture.loadFromFile(BLACK_KING_TEXTURE_PATH);
				break;
			}
		}
		this->setTexture(texture);
		this->setOriginCentered();
		sprite.setTexture(texture);
	}
};