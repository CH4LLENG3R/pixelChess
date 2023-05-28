#include <iostream>
#include "Cursor.h"

void Cursor::update(sf::RenderWindow& t_target)
{

	t_target.setMouseCursorVisible(false);


	sprite.setPosition(sf::Vector2f(mouse.getPosition(t_target).x, mouse.getPosition(t_target).y));

	if (mouse.isButtonPressed(sf::Mouse::Button::Left)) clicked = 1;
	else clicked = 0;

	draw(t_target);
}
void Cursor::initialize()
{
	//temporary

	//Cursor texture
	sf::Texture texture;
	if (texture.loadFromFile(CURSOR_IMAGE_PATH))
		this->setTexture(texture);
	else std::cout << "[WARNING]: Image not found: " << CURSOR_IMAGE_PATH << '\n';
}