#pragma once
#include "Consts.h"
#include "Cursor.h"

#include <thread>
#include <SFML/Graphics.hpp>
class TextInput : public sf::Drawable, public sf::Transformable
{
	std::string value;
	sf::Text text;
	sf::Font font;
	sf::RectangleShape box;
	bool active;
	int maxInput;
public:

	void update(Cursor& cursor, sf::Event& event)
	{
		if (cursor.isClicked() && box.getGlobalBounds().contains(cursor.getPosition()))
		{
			box.setFillColor(sf::Color::White);
			text.setFillColor(sf::Color::Black);
			text.setString(value);
			box.setOutlineColor(sf::Color::White);
			active = true;
		}
		else if(cursor.isClicked())
		{
			box.setFillColor(sf::Color::Black);
			text.setFillColor(sf::Color::White);
			active = false;
		}

		if (active && event.type == sf::Event::TextEntered) {
			if (event.text.unicode == 8)
			{
				if(value.size() > 0)
					value.pop_back();
			}
			else if (event.text.unicode < 128 && value.size()<maxInput) {
				value += std::toupper(static_cast<char>(event.text.unicode));
			}
			text.setString(value);
			std::this_thread::sleep_for(std::chrono::milliseconds(130));
		}
	}

	std::string getValue() { return value; }

	void setRed()
	{
		box.setOutlineColor(sf::Color::Red);
	}

	void draw(sf::RenderTarget& target, const sf::RenderStates t_states = sf::RenderStates::Default) const override
	{
		target.draw(box);
		target.draw(text);
	}

	TextInput(int maxInput, std::string placeHolder, sf::Vector2f pos, sf::Vector2f size) : active(false), maxInput(maxInput)
	{
		font.loadFromFile(FONT_PATH);
		value = placeHolder;
		text.setFont(font);
		text.setPosition(pos);
		text.setString(placeHolder);

		box.setPosition(pos);
		box.setSize(size);
		box.setOutlineColor(sf::Color::White);
		box.setOutlineThickness(4);
	}
};