#include "B_dur.h"

using namespace sf;
using namespace std;


B_dur::B_dur() : Brick(2, 0, 0, 60.f, 20.f)
{

}

B_dur::B_dur(float x, float y) : Brick(2, x, y, 60.f, 20.f)
{
    forme.setFillColor(Color::Red);   // rouge
}

void B_dur::hit()
{
    if (vie > 0)
    {
        vie--;
        // Mi-vie : rouge foncé pour indiquer les dégâts
        if (vie == 1)
            forme.setFillColor(Color(139, 0, 0));
    }
}
