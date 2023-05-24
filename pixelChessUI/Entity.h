#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable
{
	private:
		short z = 0;
		sf::Texture texture;
	protected:
		mutable sf::Sprite sprite;

		void setTexture(sf::Texture t_texture) 
		{ 
			texture = t_texture;
			texture.setSmooth(true);
		};
		sf::Texture getTexture() { return texture; };

		void setOriginCentered() { sprite.setOrigin(texture.getSize().x / 2.0, texture.getSize().y / 2.0); };
	public:
		void setZ(short t_z) { z = t_z; };
		short getZ() { return z; };
		
		void draw(sf::RenderTarget& target, const sf::RenderStates t_states = sf::RenderStates::Default) const override;
};

