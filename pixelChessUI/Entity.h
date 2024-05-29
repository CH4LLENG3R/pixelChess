#pragma once
#include "../Position.h"
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable
{
	protected:
		sf::Texture texture;
		mutable sf::Sprite sprite;

		void setTexture(sf::Texture t_texture) 
		{ 
			texture = t_texture;
			texture.setSmooth(true);
		};
		sf::Texture getTexture() { return texture; }

		void setOriginCentered() { sprite.setOrigin(texture.getSize().x / 2.0, texture.getSize().y / 2.0); }
	public:
		
		bool contains(const Position& pos) { return sprite.getGlobalBounds().contains(float(pos.x), float(pos.y)); }
		bool contains(const sf::Vector2f& pos) { return sprite.getGlobalBounds().contains(pos); }
		void setPosition(const sf::Vector2f& pos) { sprite.setPosition(pos); }

		void draw(sf::RenderTarget& target, const sf::RenderStates t_states = sf::RenderStates::Default) const override
		{
			sprite.setTexture(texture);
			target.draw(sprite);
		}
		Entity() {};

		Entity(sf::Texture texture) 
		{ setTexture(texture); setOriginCentered(); }

		Entity(std::string texture_path) 
		{ texture.loadFromFile(texture_path); }
};

