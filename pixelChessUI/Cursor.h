#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

#define CURSOR_IMAGE_PATH "Graphics/Cursors/WhiteCursor.png"

class Cursor : protected Entity
{
	private:
		sf::Mouse mouse;
		bool color;
		bool clicked;
		bool AlreadyMoving = false;
	public:
		void update(sf::RenderWindow& t_target);
		void initialize();
		void setAlreadyMoving(bool value) { AlreadyMoving = value; };
		bool isAlreadyMoving() { return AlreadyMoving; };
		bool isClicked() { return clicked; };
		sf::Vector2f getPosition() { return sprite.getPosition();  };
};

