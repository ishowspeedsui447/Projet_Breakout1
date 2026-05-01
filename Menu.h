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

    // Zones cliquables des boutons
    FloatRect playBounds;
    FloatRect quitBounds;

public:
    Menu();

    // Retourne true si "Jouer" a été cliqué
    // Retourne false si "Quitter" a été cliqué
    // Ne fait rien sinon
    enum class Action { None, Play, Quit };
    Action handleEvent(RenderWindow& window, Event& event);

    void draw(RenderWindow& window);
};
