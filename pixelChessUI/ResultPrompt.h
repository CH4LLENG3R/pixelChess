#pragma once
#include "Consts.h"

#include <SFML/Graphics.hpp>
class ResultPrompt : public sf::Drawable, public sf::Transformable
{
	static ResultPrompt* instanceWhite;
	static ResultPrompt* instanceBlack;
	sf::RectangleShape box;
	sf::Text text;
	sf::Font font;
public:
	void draw(sf::RenderTarget& target, const sf::RenderStates t_states = sf::RenderStates::Default) const override
	{
		target.draw(box);
		target.draw(text);
	}



	ResultPrompt(std::string value,sf::Vector2f pos, sf::Vector2f size, bool color)
	{
		
		font.loadFromFile(FONT_PATH);
		text.setString(value);

		if (color)
		{
			box.setFillColor(sf::Color::White);
			box.setOutlineColor(sf::Color::Black);
			text.setFillColor(sf::Color::Black);
		}
		else
		{
			box.setFillColor(sf::Color::Black);
			box.setOutlineColor(sf::Color::White);
			text.setFillColor(sf::Color::White);
		}
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
		text.move(0, -10);
	}

	static ResultPrompt* getInstance(sf::Vector2f pos, sf::Vector2f size, bool color)
	{
		if (instanceWhite == nullptr)
		{
			instanceWhite = new ResultPrompt("White wins", pos, size, 1);
		}

		if (instanceBlack == nullptr)
		{
			instanceBlack = new ResultPrompt("Black wins", pos, size, 0);
		}

		if(color)
			return instanceWhite;
		else
			return instanceWhite;
	}

	static ResultPrompt* getWhiteInstance()
	{
		return instanceWhite;
	}

	static ResultPrompt* getBlackInstance()
	{
		return instanceBlack;
	}

	~ResultPrompt()
	{
		delete instanceWhite;
		delete instanceBlack;
	}
};
ResultPrompt* ResultPrompt::instanceWhite;
ResultPrompt* ResultPrompt::instanceBlack;