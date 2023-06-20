#pragma once
#include "Consts.h"
#include "../Clock.h"
#include "SFML/Graphics.hpp"
class GClock : public Clock, public sf::Drawable, public sf::Transformable
{
	sf::Text timerWhite;
	sf::Text timerBlack;
	sf::RectangleShape whiteBorder;
	sf::RectangleShape blackBorder;
	sf::Font font;
public:
	void update()
	{
		
		Timestamp tw = this->getWhiteTime();
		char buff[13];
		snprintf(buff, sizeof(buff), "%.2i : %.2i : %.2i", tw.getHour(), tw.getMinute(), tw.getSecond());
		std::string whiteT = buff;

		Timestamp tb = this->getBlackTime();
		snprintf(buff, sizeof(buff), "%02i : %02i : %02i", tb.getHour(), tb.getMinute(), tb.getSecond());
		std::string blackT = buff;

		timerWhite.setString(whiteT);
		timerBlack.setString(blackT);
	}

	void draw(sf::RenderTarget& target, const sf::RenderStates t_states = sf::RenderStates::Default) const override
	{
		target.draw(whiteBorder);
		target.draw(blackBorder);
		target.draw(timerWhite);
		target.draw(timerBlack);
	}

	GClock(Timestamp whiteTime, Timestamp blackTime) : Clock(whiteTime, blackTime)
	{
		font.loadFromFile(FONT_PATH);
		timerWhite.setFont(font);
		timerBlack.setFont(font);

		timerWhite.setPosition((BOARD_SIZE/2.f) + (SCREEN_WIDTH/2.f)+10, (SCREEN_HEIGHT/2.F) + (BOARD_SIZE / 2.f));
		timerBlack.setPosition((BOARD_SIZE / 2.f) + (SCREEN_WIDTH / 2.f) +10, (SCREEN_HEIGHT / 2.F) - (BOARD_SIZE / 2.f));

		timerWhite.setString("00 : 00 : 00");
		timerBlack.setString("00 : 00 : 00");

		sf::FloatRect whiteB = timerWhite.getGlobalBounds();
		sf::FloatRect blackB = timerWhite.getGlobalBounds();

		whiteBorder = sf::RectangleShape(sf::Vector2f(whiteB.width+10, whiteB.height*2.2));
		blackBorder = sf::RectangleShape(sf::Vector2f(blackB.width+10, blackB.height*2.2));

		whiteBorder.setOutlineColor(sf::Color::White);
		blackBorder.setOutlineColor(sf::Color::White);

		whiteBorder.setFillColor(sf::Color::Black);
		blackBorder.setFillColor(sf::Color::Black);

		whiteBorder.setOutlineThickness(4);
		blackBorder.setOutlineThickness(4);

		whiteBorder.setPosition(timerWhite.getPosition());
		blackBorder.setPosition(timerBlack.getPosition());

		whiteBorder.move(0, -0.9 * whiteBorder.getGlobalBounds().height - 1);
		timerWhite.move(0, -0.9 * whiteBorder.getGlobalBounds().height - 1);
	}

	~GClock()
	{}
};