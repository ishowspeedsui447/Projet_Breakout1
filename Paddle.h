#pragma once

#include "Ball.h"

class Paddle {

private:
	sf::RectangleShape forme;
	float mouvement;

public:
	Paddle(float x, float y);

	void update(int windowWidth);
	void draw(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;
	sf::Vector2f getPosition() const;
};
