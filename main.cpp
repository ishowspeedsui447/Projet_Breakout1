#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Mesfonctions.h"

using namespace std;


int main() {

    srand(time(NULL));

    Game game;
    game.play();

    return 0;
}
