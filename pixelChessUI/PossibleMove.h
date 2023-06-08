#pragma once
#include "Entity.h"
#include "Board.h"
#include "Cursor.h"
#include "Consts.h"
#include <SFML/Graphics.hpp>

class PossibleMove : public Entity
{
	Position boardPos;
public:

	PossibleMove(Position boardPos, sf::Vector2f pos)
	{
		this->boardPos = boardPos;
		if (texture.loadFromFile(POSSIBLE_MOVE_TEXTURE_PATH))
			setTexture(texture);
		else std::cout << "[WARNING]: Image not found: " << POSSIBLE_MOVE_TEXTURE_PATH << '\n';
		setOriginCentered();
		sprite.setPosition(pos);
		sprite.setScale(FIGURE_TEXTURE_SIZE / 100.0, FIGURE_TEXTURE_SIZE / 100.0);
	}
	Position getBoardPos() { return boardPos; }
	
	sf::Vector2f getPos() { return sprite.getPosition(); }
	
};