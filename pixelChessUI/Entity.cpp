#include "Entity.h"
#include <SFML/Graphics.hpp>

void Entity::draw(sf::RenderTarget& t_target, const sf::RenderStates t_states) const
{
	sprite.setTexture(texture);
	t_target.draw(sprite);
}
