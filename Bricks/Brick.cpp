#include "Brick.h"

using namespace sf;
using namespace std;

Brick::Brick(int vie, float x, float y, float w, float h) : vie(vie)
{
    forme.setSize(Vector2f(w, h));
    forme.setPosition(x, y);
    forme.setFillColor(Color::Blue);
}

Brick::Brick() : vie(1)
{
    forme.setSize(Vector2f(60, 20));
    forme.setPosition(0, 0);
    forme.setFillColor(Color::Blue);
}

Brick::~Brick() {}

void Brick::hit()
{
    if (vie > 0)
    {
        vie--;
    }

}

bool Brick::isDestroyed() const
{
    return vie <= 0;
}

bool Brick::isUnbreakable() const {
    return false;
}

void Brick::draw(RenderWindow& window)
{
    if (!isDestroyed())
    {
        window.draw(forme);
    }
}
