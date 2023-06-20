#pragma once
#include "Consts.h"
#include "Cursor.h"

#include <SFML/Graphics.hpp>
class Button : public sf::Drawable, public sf::Transformable
{
	sf::RectangleShape box;
	sf::Text text;
	sf::Font font;
	static bool wasClicked;
public:
	void setPosition(sf::Vector2f pos)
	{
		box.setPosition(pos);

		text.setPosition(pos);
		text.move(0, -10);
	}

	void flip_text()
	{
		text.rotate(180);
		text.move(6, 22);
	}

	void draw(sf::RenderTarget& target, const sf::RenderStates t_states = sf::RenderStates::Default) const override
	{
		target.draw(box);
		target.draw(text);
	}
	
	bool update(Cursor& cursor)
	{
		if (box.getGlobalBounds().contains(cursor.getPosition()))
		{
			box.setFillColor(sf::Color::White);
			box.setOutlineColor(sf::Color::Black);
			text.setFillColor(sf::Color::Black);

			if (wasClicked && !cursor.isClicked())
				wasClicked = false;
			else if (!wasClicked && cursor.isClicked())
			{
				wasClicked = true;
				return true;
			}
		}
		else
		{
			box.setFillColor(sf::Color::Black);
			box.setOutlineColor(sf::Color::White);
			text.setFillColor(sf::Color::White);
		}
		return false;
	}

	Button(std::string value, sf::Vector2f pos, sf::Vector2f size)
	{
		font.loadFromFile(FONT_PATH);
		text.setString(value);

		box.setFillColor(sf::Color::Black);
		box.setOutlineColor(sf::Color::White);
		text.setFillColor(sf::Color::White);

		box.setOutlineThickness(5);
		box.setSize(size);
		text.setFont(font);
		text.setCharacterSize(30);

		sf::Vector2f center = sf::Vector2f(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
		sf::Vector2f rounded = sf::Vector2f{ std::round(center.x), std::round(center.y) };
		text.setOrigin(rounded);


		box.setOrigin(size.x / 2.0, size.y / 2.0);
		box.setPosition(pos);

		text.setPosition(pos);
		text.move(-3, -10);
	}

};
bool Button::wasClicked = false;