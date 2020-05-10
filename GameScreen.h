#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;
	void latticeRender(sf::RenderWindow& window);

	void generateFruit();

private:
	Snake snake_;
	bool lattice_;
	sf::Color latticeColor_;
	std::vector<Fruit> fruit_;
};
}

#endif