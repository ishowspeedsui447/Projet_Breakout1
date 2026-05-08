#pragma once
#include <SFML/Graphics.hpp>

class Ball {
private:

	sf::CircleShape forme;
	sf::Vector2f mouvement;
	float rayon = 10.f;

public:

	Ball(float debutX, float debutY);
	void setPosition(float x, float y);
	void update(int windowWidth, int windowHeight);
	void draw(sf::RenderWindow& window);
	void bondX();
	void bondY();
	const sf::CircleShape& getForme() const;
	sf::FloatRect getBounds()const;
	sf::Vector2f getPosition()const;
	~Ball();
};
