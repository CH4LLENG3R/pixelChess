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
		void update(sf::RenderWindow& t_target)
		{
			t_target.setMouseCursorVisible(false);


			sprite.setPosition(sf::Vector2f(mouse.getPosition(t_target).x, mouse.getPosition(t_target).y));

			if (mouse.isButtonPressed(sf::Mouse::Button::Left)) 
				clicked = 1;
			else 
				clicked = 0;

			draw(t_target);
		}
		void setAlreadyMoving(bool value) { AlreadyMoving = value; };
		bool isAlreadyMoving() { return AlreadyMoving; };
		bool isClicked() { return clicked; };
		sf::Vector2f getPosition() { return sprite.getPosition();  };
		Cursor(): color(true), clicked(false)
		{
			//Cursor texture
			sf::Texture texture;
			if (texture.loadFromFile(CURSOR_IMAGE_PATH))
				this->setTexture(texture);
			else std::cout << "[WARNING]: Image not found: " << CURSOR_IMAGE_PATH << '\n';
		}
};

