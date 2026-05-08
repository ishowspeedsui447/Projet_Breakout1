#include "Ball.h"

Ball::Ball(float debutX, float debutY)
{
	forme.setRadius(rayon);
	forme.setOrigin(rayon, rayon);
	forme.setPosition(debutX, debutY);
	forme.setFillColor(sf::Color::White);
	mouvement = sf::Vector2f(4.0f, -4.0f);
}

void Ball::setPosition(float x, float y)
{
	forme.setPosition(x, y);
}

void Ball::update(int windowWidth, int windowHeight)
{
	forme.move(mouvement);
	if (forme.getPosition().x - rayon < 0 || forme.getPosition().x + rayon >800)
	{
		bondX();
	}
	if (forme.getPosition().y - rayon < 0)
	{
		bondY();
	}
}

void Ball::reboundFromPaddle(float paddleX, float paddleWidth)
{
	float ballX = forme.getPosition().x;
	float paddleCenter = paddleX;

	float distance = ballX - paddleCenter;

	// petite division pour éviter vitesse trop grande
	mouvement.x = distance / 15;

	// toujours vers le haut
	mouvement.y = -abs(mouvement.y);
}

void Ball::bondX()
{
	mouvement.x = -mouvement.x;
}

void Ball::bondY()
{
	mouvement.y = -mouvement.y;
}

const sf::CircleShape& Ball::getForme() const
{
	return forme;
}

sf::FloatRect Ball::getBounds() const
{
	return forme.getGlobalBounds();
}

sf::Vector2f Ball::getPosition() const
{
	return forme.getPosition();
}

void Ball::draw(sf::RenderWindow& window)
{ 
	window.draw(forme);
}

Ball::~Ball()
{

}

