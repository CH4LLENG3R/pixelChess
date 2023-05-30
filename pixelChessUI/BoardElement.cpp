#include "BoardElement.h"


PossibleMove::PossibleMove(Board& t_board, short t_x, short t_y)
{
	sf::Texture texture;
	if (texture.loadFromFile(POSSIBLE_MOVE_IMAGE_PATH))
		setTexture(texture);
	else std::cout << "[WARNING]: Image not found: " << POSSIBLE_MOVE_IMAGE_PATH << '\n';
	setOriginCentered();
	setX(t_x);
	setY(t_y);
	sprite.setPosition(t_board.position[getX()][getY()].pos);

	//std::cout << "height: " << sprite.getGlobalBounds().height << "\nwidth: " << sprite.getGlobalBounds().width << "\ntop: " << sprite.getGlobalBounds().top << "\n left: " << sprite.getGlobalBounds().left << '\n';
	hitbox = sprite.getGlobalBounds();
	hitbox.width = texture.getSize().x;
	hitbox.height = texture.getSize().y;
}
