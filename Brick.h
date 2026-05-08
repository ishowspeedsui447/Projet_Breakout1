#pragma once
#include <SFML/Graphics.hpp>

class Brick {
protected:
    int vie;
    sf::RectangleShape forme;
public:
    Brick(int vie, float x, float y, float w, float h);
    Brick();
    virtual ~Brick();
    virtual void hit();
    virtual void draw(sf::RenderWindow& window);
    virtual bool isDestroyed() const;
    virtual bool isUnbreakable() const;
    sf::FloatRect getBounds() const { return forme.getGlobalBounds(); }
    sf::Color getColor() const { return forme.getFillColor(); }
};