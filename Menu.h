#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Menu {
private:
    Font font;
    Text title;
    Text play;
    Text quit;
    Text instructions;
    Text stats;

    // Zones cliquables des boutons
    FloatRect playBounds;
    FloatRect quitBounds;
    FloatRect instructionsBounds;
    FloatRect statsBounds;

 
 
public:
    Menu();

    // Retourne true si "Jouer" a été cliqué
    // Retourne false si "Quitter" a été cliqué
    // Ne fait rien sinon
    enum class Action { None, Play, Instructions, Stats, Quit };
    Action handleEvent(RenderWindow& window, Event& event);

    void draw(RenderWindow& window);
};
