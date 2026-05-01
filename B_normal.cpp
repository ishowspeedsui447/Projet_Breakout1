#include "B_normal.h"

using namespace sf;
using namespace std;

B_normal::B_normal() : Brick(1, 0, 0, 60.f, 20.f) {
    
}

B_normal::B_normal(float x, float y) : Brick(1, x, y, 60.f, 20.f)
{
    forme.setFillColor(Color::Green);
}