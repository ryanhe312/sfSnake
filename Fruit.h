#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Color& color,int weight,sf::Vector2f position = sf::Vector2f(0, 0));

	void render(sf::RenderWindow& window);

	int getWeight() const;
	sf::FloatRect getBounds() const;

private:
	sf::CircleShape shape_;

	int weight_;
	static const float Radius;
};
}

#endif