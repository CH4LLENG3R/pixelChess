#pragma once

#include "Consts.h"
#include "Cursor.h"
#include "../Timestamp.h"

#include <thread>
#include <regex>
#include <string>
#include <SFML/Graphics.hpp>

class TimeInput : public sf::Drawable, public sf::Transformable
{
	std::string value;
	sf::Text text;
	sf::Font font;
	sf::RectangleShape box;
	bool active;
public:

	bool isValueCorrect()
	{
		return std::regex_match(value, std::regex("^([0-5][0-9]:){2}[0-5][0-9]$", std::regex_constants::ECMAScript | std::regex_constants::icase));
	}

	void update(Cursor& cursor, sf::Event& event)
	{
		if (cursor.isClicked() && box.getGlobalBounds().contains(cursor.getPosition()))
		{
			box.setFillColor(sf::Color::White);
			text.setFillColor(sf::Color::Black);
			value.clear();
			text.setString(value);
			active = true;
		}
		else if (cursor.isClicked())
		{
			box.setFillColor(sf::Color::Black);
			text.setFillColor(sf::Color::White);
			if (!isValueCorrect())
				box.setOutlineColor(sf::Color::Red);
			else
				box.setOutlineColor(sf::Color::White);
			active = false;
		}

		if (active && event.type == sf::Event::TextEntered) {
			if (event.text.unicode == 8)
			{
				if (value.size() > 0)
					value.pop_back();
				if (value.size() > 0 && value.size() % 3 == 0)
					value.pop_back();
			}
			else if (value.size() < 8 && event.text.unicode >47 && event.text.unicode <58) {
				value += static_cast<char>(event.text.unicode);
				if (value.size() == 2 || value.size() == 5)
					value += ':';
			}
			text.setString(value);
			std::this_thread::sleep_for(std::chrono::milliseconds(130));
		}
	}

	Timestamp getValue() 
	{
		int hour = std::stoi(value.substr(0, 2));
		int min = std::stoi(value.substr(3, 2));
		int sec = std::stoi(value.substr(7, 2));
		return Timestamp(hour, min, sec);
	}

	void draw(sf::RenderTarget& target, const sf::RenderStates t_states = sf::RenderStates::Default) const override
	{
		target.draw(box);
		target.draw(text);
	}

	TimeInput(sf::Vector2f pos, sf::Vector2f size) : active(false)
	{
		font.loadFromFile(FONT_PATH);

		text.setFont(font);
		text.setPosition(pos);
		text.setString("hh:mm:ss");

		box.setPosition(pos);
		box.setSize(size);
		box.setOutlineColor(sf::Color::White);
		box.setOutlineThickness(4);
	}
};