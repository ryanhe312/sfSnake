#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0), float rotation = 0);

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void setRotation(float x);

	void move(float xOffset, float yOffset);

	void render(sf::RenderWindow& window,int item = 0);

	sf::Vector2f getPosition() const;
	float getRotation() const;
	sf::FloatRect getBounds() const;

	static const float Radius;

private:
	sf::CircleShape shape_;
	sf::RectangleShape deco_;
	sf::Vector2f position_;
	float rotation_;
};
}

#endif