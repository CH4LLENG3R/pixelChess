#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define FONT_PATH "Fonts/slkscr.ttf"

#define FIGURE_IMAGE_SIZE 100

struct Positions
{
	sf::Vector2f pos;
};

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

public:

	Positions position[8][8];
	int squareSize;

	~Board() = default;
	void initialize(int t_edgeLength, sf::Vector2i t_pos);
	void draw(sf::RenderTarget& target, const sf::RenderStates t_states = sf::RenderStates::Default) const override;

};

