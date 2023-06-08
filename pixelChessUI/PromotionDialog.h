#pragma once
#include "Consts.h"
#include "Cursor.h"

#include <SFML/Graphics.hpp>
#include <vector>
class PromotionDialog : public sf::Drawable, public sf::Transformable
{
	sf::RectangleShape box;
	std::vector<sf::RectangleShape> options;
	sf::Font font;
	sf::Text text;
	Entity whiteQueen, whiteKnight, whiteRook, whiteBishop;
	Entity blackQueen, blackKnight, blackRook, blackBishop;

	char* promotionVariants;
	bool visible;
	bool activeColor;

public:
	void draw(sf::RenderTarget& target, const sf::RenderStates t_states = sf::RenderStates::Default) const override
	{
		if (!visible)
			return;

		target.draw(text);
		target.draw(box);
		for (int i = 0; i < options.size(); i++)
			target.draw(options[i]);

		if (activeColor)
		{
			target.draw(whiteQueen);
			target.draw(whiteKnight);
			target.draw(whiteRook);
			target.draw(whiteBishop);
		}
		else
		{
			target.draw(blackQueen);
			target.draw(blackKnight);
			target.draw(blackRook);
			target.draw(blackBishop);
		}
	}

	char update(const Cursor& cursor)
	{
		if (!visible)
			return 'E';

		for (int i = 0; i < options.size(); i++)
		{
			if (options[i].getGlobalBounds().contains(cursor.getPosition()))
			{
				options[i].setFillColor(sf::Color::Black);

				if (cursor.isClicked())
					return promotionVariants[i];
			}
			else
				options[i].setFillColor(sf::Color::White);
		}

		return 'E';
	}

	void setActiveColor(const bool& activeColor) { this->activeColor = activeColor; }

	void show() { this->visible = true; }
	void hide() { this->visible = false; }

	PromotionDialog(const bool& activeColor, const bool& show)
	{
		this->promotionVariants = new char[5] {'Q', 'N', 'R', 'B', 'E'};
		this->visible = show;
		this->activeColor = activeColor;
		font.loadFromFile(FONT_PATH);
		text.setFont(font);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(15);
		text.setString("promote to:");
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + (textRect.width / 2.0), textRect.top + (textRect.height / 2.0));
		text.setPosition(sf::Vector2f((SCREEN_WIDTH - BOARD_SIZE) / 2.0 - 150.0, SCREEN_HEIGHT/2 - 220));

		box.setSize(sf::Vector2f(100, 400));
		box.setPosition(sf::Vector2f((SCREEN_WIDTH - BOARD_SIZE) / 2.0 - 200.0, SCREEN_HEIGHT / 2 - 200));
		box.setOutlineColor(sf::Color::White);
		box.setOutlineThickness(5);

		float x, y;
		for (int i = 0; i < 4; i++)
		{
			options.push_back(sf::RectangleShape(sf::Vector2f(100, 100)));
			x = box.getPosition().x;
			y = box.getPosition().y;
			options[i].setPosition(sf::Vector2f(x, y + (100 * i)));
		}

		//figures
		whiteQueen = Entity(WHITE_QUEEN_TEXTURE_PATH);
		whiteQueen.setPosition(options[0].getPosition());

		whiteKnight = Entity(WHITE_KNIGHT_TEXTURE_PATH);
		whiteKnight.setPosition(options[1].getPosition());

		whiteRook = Entity(WHITE_ROOK_TEXTURE_PATH);
		whiteRook.setPosition(options[2].getPosition());

		whiteBishop = Entity(WHITE_BISHOP_TEXTURE_PATH);
		whiteBishop.setPosition(options[3].getPosition());


		blackQueen = Entity(BLACK_QUEEN_TEXTURE_PATH);
		blackQueen.setPosition(options[0].getPosition());

		blackKnight = Entity(BLACK_KNIGHT_TEXTURE_PATH);
		blackKnight.setPosition(options[1].getPosition());

		blackRook = Entity(BLACK_ROOK_TEXTURE_PATH);
		blackRook.setPosition(options[2].getPosition());

		blackBishop = Entity(BLACK_BISHOP_TEXTURE_PATH);
		blackBishop.setPosition(options[3].getPosition());
	}

	~PromotionDialog()
	{
		delete[] promotionVariants;
	}
};

