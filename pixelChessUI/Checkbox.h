#pragma once

#include "Cursor.h"

#include <SFML/Graphics.hpp>

class Checkbox : public sf::Drawable, public sf::Transformable
{
	sf::RectangleShape box;
	bool value;
	bool wasClicked;
public:

	bool getValue() { return value; }

	void update(Cursor& cursor)
	{
		if (!wasClicked && cursor.isClicked() && box.getGlobalBounds().contains(cursor.getPosition()))
		{
			wasClicked = true;
			value = !value;

			if(value)
				box.setFillColor(sf::Color::White);
			else
				box.setFillColor(sf::Color::Black);
		}
		else if (!cursor.isClicked())
		{
			wasClicked = false;
		}
	}

	void draw(sf::RenderTarget& target, const sf::RenderStates t_states = sf::RenderStates::Default) const override
	{
		target.draw(box);
	}

	Checkbox(sf::Vector2f pos, sf::Vector2f size, bool value = false) : value(value), wasClicked(false)
	{
		box.setPosition(pos);
		box.setSize(size);
		box.setOutlineColor(sf::Color::White);
		box.setOutlineThickness(4);

		if (value)
			box.setFillColor(sf::Color::White);
		else
			box.setFillColor(sf::Color::Black);
	}
};