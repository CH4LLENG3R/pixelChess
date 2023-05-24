#include "Board.h"
#include <SFML/Graphics.hpp>
#include <vector>

void Board::initialize(int t_edgeLength, sf::Vector2i t_pos)
{
	edgeLength = t_edgeLength;
	pos = t_pos;

	squareSize = t_edgeLength / 8;

	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 8; x++) position[x][y].pos = sf::Vector2f((squareSize * x) + (squareSize / 2)+ pos.x, (squareSize * y) + (squareSize / 2)+pos.y);
	/*for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++) std::cout << position[x][y].pos.x << " " << position[x][y].pos.y << "\t";
		std::cout << '\n';
	}*/
	//std::cout << squareSize<<'\n';


	edges.setSize(sf::Vector2f(edgeLength - edgeThickness, edgeLength - edgeThickness));
	edges.setPosition(sf::Vector2f(pos));
	edges.setFillColor(sf::Color::Black);

	edges.setOutlineThickness(edgeThickness);
	edges.setOutlineColor(sf::Color::White);
	
	/*for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			std::cout << position[x][y].x << " " << position[x][y].y << "\t";
		}
		std::cout << '\n';
	}*/

	if (!(boardFont.loadFromFile(FONT_PATH)))
	{
		std::cout<<"[WARNING]: Board font not found";
	}
	
	for(int i = 0; i < 8; i++)
	{
		sf::Text textL, textR, textU, textD;
		textL.setFont(boardFont);
		textL.setFillColor(sf::Color::White);
		textL.setCharacterSize(30);
		textL.setString(char('8'-i));
		sf::FloatRect textRectL = textL.getLocalBounds();
		textL.setOrigin(textRectL.left + (textRectL.width / 2.0), textRectL.top + (textRectL.height / 2.0));
		
		textL.setPosition(sf::Vector2f(pos.x - 30, pos.y + (squareSize/2) + (squareSize * i)));
		letters.push_back(textL);



		textR.setFont(boardFont);
		textR.setFillColor(sf::Color::White);
		textR.setCharacterSize(30);
		textR.setString(char('8' - i));
		sf::FloatRect textRectR = textR.getLocalBounds();
		textR.setOrigin(textRectL.left + (textRectL.width / 2.0), textRectL.top + (textRectL.height / 2.0));

		textR.setPosition(sf::Vector2f(pos.x + edgeLength + 30, pos.y + (squareSize / 2) + (squareSize * i)));
		textR.rotate(180.0);
		letters.push_back(textR);


		textU.setFont(boardFont);
		textU.setFillColor(sf::Color::White);
		textU.setCharacterSize(30);
		textU.setString(char('A' + i));
		sf::FloatRect textrectR = textU.getLocalBounds();
		textU.setOrigin(textRectL.left + (textRectL.width / 2.0), textRectL.top + (textRectL.height / 2.0));

		textU.setPosition(sf::Vector2f(pos.x + (squareSize / 2) + (squareSize * i), pos.y -30));
		textU.rotate(180.0);
		letters.push_back(textU);

		textD.setFont(boardFont);
		textD.setFillColor(sf::Color::White);
		textD.setCharacterSize(30);
		textD.setString(char('A' + i));
		sf::FloatRect textRectD = textD.getLocalBounds();
		textD.setOrigin(textRectD.left + (textRectD.width / 2.0), textRectD.top + (textRectD.height / 2.0));

		textD.setPosition(sf::Vector2f(pos.x + (squareSize / 2) + (squareSize * i), pos.y + edgeLength + 30));
		letters.push_back(textD);
	}


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			square[i*4+j].setSize(sf::Vector2f(squareSize, squareSize));
			square[i*4+j].setFillColor(sf::Color::White);
			if (i % 2)
			{
				square[i * 4 + j].setPosition(sf::Vector2f((j * (squareSize * 2) + squareSize) + pos.x, i * (squareSize) + pos.y));
			}
			else square[i * 4 + j].setPosition(sf::Vector2f(j * (squareSize * 2) + pos.x, i * (squareSize) + pos.y));
		}
	}

}

void Board::draw(sf::RenderTarget& t_target, const sf::RenderStates t_states) const
{
	
	t_target.draw(this->edges, t_states);
	for(int i =0; i<32; i++) t_target.draw(this->square[i]);
	

	for (int i = 0; i < 32; i++)
	{
		sf::Text letter = letters[i];
		letter.setFont(boardFont);
		t_target.draw(letter);
	}
	//t_target.draw(letters[0]);
}