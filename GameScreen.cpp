#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{
	lattice_ = true;
	latticeColor_ = sf::Color::White;
}

void GameScreen::handleInput(sf::RenderWindow& window)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		lattice_ = true;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		lattice_ = false;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		latticeColor_ = sf::Color::White;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		latticeColor_ = sf::Color::Black;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		latticeColor_ = sf::Color(150, 75, 0);


	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() == 0)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	if(lattice_) latticeRender(window);

	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::latticeRender(sf::RenderWindow& window)
{
    sf::RectangleShape hline(sf::Vector2f(Game::Width,1));
	float interval = SnakeNode::Radius * 1.3;
	hline.setFillColor(latticeColor_);
	for (int i=0;i<Game::Height/interval;i++)
	{
		hline.setPosition(sf::Vector2f(0,i*interval));
		window.draw(hline);
	}
	sf::RectangleShape sline(sf::Vector2f(1,Game::Height));
	sline.setFillColor(latticeColor_);
	for (int j=0;j<Game::Width/interval;j++)
	{
		sline.setPosition(sf::Vector2f(j*interval,0));
		window.draw(sline);
	}
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine;
	engine.seed(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Radius);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Radius);

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine))));
}

