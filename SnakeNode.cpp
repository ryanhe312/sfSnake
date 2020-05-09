#include <SFML/Graphics.hpp>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Radius = 10.f;

SnakeNode::SnakeNode(sf::Vector2f position, float rotation)
: position_(position), rotation_(rotation)
{
	setPosition(position_);

	shape_.setFillColor(sf::Color::Yellow);
	shape_.setRadius(SnakeNode::Radius);
	shape_.setOrigin(SnakeNode::Radius,SnakeNode::Radius);

	shape_.setOutlineColor(sf::Color::Black);
	shape_.setOutlineThickness(-0.8);

	deco_.setFillColor(sf::Color::Black);
	deco_.setSize(sf::Vector2f(2 * SnakeNode::Radius, 0.6* SnakeNode::Radius));
	deco_.setOrigin(SnakeNode::Radius, 0.3* SnakeNode::Radius);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
	deco_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	setPosition(position_);
}

void SnakeNode::setRotation(float x){
	rotation_ = x;
	deco_.setRotation(rotation_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

float SnakeNode::getRotation() const
{
	return rotation_;
}

void SnakeNode::render(sf::RenderWindow& window,int item)
{
	if(item == 0)
		window.draw(shape_);
	else 
		window.draw(deco_);
}