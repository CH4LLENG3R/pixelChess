#pragma once
#include <SFML/Graphics.hpp>
#include "Consts.h"
#include <iostream>

class Board : public sf::Drawable, public sf::Transformable
{
private:
	sf::Vector2i pos = { 0, 0 };
	sf::RectangleShape edges;

	std::vector<sf::Text> letters;
	sf::Font boardFont;

	int edgeLength;
	int edgeThickness = 4;

	sf::RectangleShape square[32];
	int squareSize;
public:
	sf::Vector2f** positions;
	int getSquareSize() { return squareSize; }

	~Board()
	{
		for (int i = 0; i < 8; i++)
			delete[] positions[i];
		delete[] positions;
	}

	Board(int t_edgeLength, sf::Vector2i t_pos);
	void draw(sf::RenderTarget& target, const sf::RenderStates t_states = sf::RenderStates::Default) const override;

};

