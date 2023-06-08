#pragma once
#include "Entity.h"
#include "Consts.h"
#include <SFML/Graphics.hpp>



class Cursor : protected Entity
{
	private:
		sf::Mouse mouse;
		bool color;
		bool clicked;
		bool movingFigure;
		int movingFigureId;

		sf::Texture whiteCursor;
		sf::Texture blackCursor;
	public:
		void update(sf::RenderWindow& t_target)
		{
			sprite.setPosition(sf::Vector2f(mouse.getPosition(t_target).x, mouse.getPosition(t_target).y));

			clicked = mouse.isButtonPressed(sf::Mouse::Button::Left);

			draw(t_target);
		}
		void setMovingFigureID(int value) { movingFigureId = value; };
		int getMovingFigureID() { return movingFigureId; };

		void setMovingFigure(bool value) { movingFigure = value; };
		bool isMovingFigure() { return movingFigure; };
		bool isClicked() const { return clicked; };
		sf::Vector2f getPosition() const { return sprite.getPosition();  };

		void setWhiteColor()
		{
			this->setTexture(whiteCursor);
		}

		void setBlackColor()
		{
			this->setTexture(blackCursor);
		}

		Cursor() : color(true), clicked(false), movingFigure(false), movingFigureId(0)
		{
			//Cursor texture
			whiteCursor.loadFromFile(WHITE_CURSOR_TEXTURE_PATH);
			blackCursor.loadFromFile(BLACK_CURSOR_TEXTURE_PATH);

			this->setTexture(whiteCursor);
		}
};

