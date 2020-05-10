#include <SFML/Graphics.hpp>

#include <cmath>
#include <memory>
#include <iostream>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : hitSelf_(false), direction_(sf::Vector2f(0,-1.0))
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);

	texture_.loadFromFile("Picture/head.png", sf::IntRect(0, 0, 30, 30));
	head_.setTexture(texture_);
	head_.setOrigin(sf::Vector2f(15,15));
	head_.setPosition(nodes_[0].getPosition());
	head_.setRotation(nodes_[0].getRotation());
}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Radius / 2,
			Game::Height / 2 - (SnakeNode::Radius / 2) + (SnakeNode::Radius * i * 1.3))));
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
	SnakeNode& headNode = nodes_[0];

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		direction_ = sf::Vector2f(sf::Mouse::getPosition(window))-headNode.getPosition();
		direction_ /= float(sqrt(pow(direction_.x,2) + pow(direction_.y,2)));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction_ = sf::Vector2f(0,-1.0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction_ = sf::Vector2f(0,1.0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction_ = sf::Vector2f(-1.0,0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction_ = sf::Vector2f(1.0,0);
	std::clog<<"x:"<<direction_.x<<'\t'<<"y:"<<direction_.y<<std::endl;
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		for (int i = toRemove->getWeight(); i>0 ; i--)
		{
			grow();
		}
		fruits.erase(toRemove);
	}
}

void Snake::grow()
{
	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
			nodes_[nodes_.size() - 1].getPosition().y),nodes_[nodes_.size() - 1].getRotation()));
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
	{
		sf::Vector2f diff = headNode.getPosition() - nodes_[i].getPosition();
		if (pow(diff.x,2) + pow(diff.y,2) < pow(SnakeNode::Radius,2) * 0.9)
		{
			std::clog<<"wrong:"<<i<<'\t'<<"x:"<<diff.x<<'\t'<<"y:"<<diff.x<<std::endl;
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
		nodes_[i].setRotation(nodes_.at(i - 1).getRotation());
	}

	nodes_[0].move(SnakeNode::Radius * 1.3 * direction_.x, SnakeNode::Radius * 1.3 * direction_.y);
	nodes_[0].setRotation(atan2(direction_.x,-direction_.y) * 180 / 3.14159265);
	head_.setPosition(nodes_[0].getPosition());
	head_.setRotation(nodes_[0].getRotation());
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto node : nodes_)
		node.render(window,0);
	for (auto node : nodes_)
		node.render(window,1);
	window.draw(head_);
}