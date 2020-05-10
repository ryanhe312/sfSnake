#include <SFML/Graphics.hpp>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Color& color,int weight,sf::Vector2f position)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	shape_.setFillColor(color);
	weight_ = weight;
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

int Fruit::getWeight() const
{
	return weight_;
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}