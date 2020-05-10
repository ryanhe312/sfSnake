#include <SFML/Graphics.hpp>

#include <memory>

#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	bgMusic_.openFromFile("Music/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();

	bgColor_ = sf::Color::White;
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		bgColor_ = sf::Color::White;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		bgColor_ = sf::Color::Black;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		bgColor_ = sf::Color(150, 75, 0);

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

void Game::render()
{
	window_.clear();
	backgroundRender(window_);
	Game::Screen->render(window_);
	window_.display();
}

void Game::backgroundRender(sf::RenderWindow& window)
{
	sf::RectangleShape background(sf::Vector2f(Game::Width,Game::Height));
	background.setFillColor(bgColor_);
	window_.draw(background);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}