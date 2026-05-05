#include "Paddle.h"

Paddle::Paddle(float x, float y)
{
	forme.setSize(sf::Vector2f(100.f, 20.f));
	forme.setFillColor(sf::Color::Blue);
    forme.setOrigin(50.f, 10.f);
	forme.setPosition(x, y);
	mouvement = 7.0f;
}
void Paddle::update(int windowWidth) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (getBounds().left > 0)
            forme.move(-mouvement, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (getBounds().left + getBounds().width < windowWidth)
            forme.move(mouvement, 0.f);
    }
}

void Paddle::draw(sf::RenderWindow& window) {
	window.draw(forme);
}
sf::FloatRect Paddle::getBounds()const {
	return forme.getGlobalBounds();
}
sf::Vector2f Paddle::getPosition() const {
	return forme.getPosition();
}