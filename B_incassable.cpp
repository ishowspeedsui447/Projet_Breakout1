#include "B_incassable.h"

using namespace sf;
using namespace std;

B_incassable::B_incassable() : Brick(-1, 0, 0, 60.f, 20.f)
{

}

B_incassable::B_incassable(float x, float y) : Brick(-1, x, y, 60.f, 20.f)
{
    forme.setFillColor(Color(128, 128, 128));  // grise
}

void B_incassable::hit()
{

}

bool B_incassable::isDestroyed() const
{
    return false;
}