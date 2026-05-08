#include "Game.h"
#include <SFML/Graphics.hpp>

//CONSTRUCTEUR
Game::Game()
    : window(sf::VideoMode(800, 600), "Breakout Fruits"),
    ball(400, 300),
    paddle(350, 550)
{
    init();
}

//INIT
void Game::init() {
    lives = 3;
    score = 0;

    isRunning = true;
    isGameOver = false;
    isWin = false;
    ballLaunched = false;

    font.loadFromFile("arial.ttf");
}

//EVENTS
void Game::handleEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        ballLaunched = true;

    if (isGameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        resetGame();
}

//UPDATE
void Game::update(float dt) {

    paddle.update(window.getSize().x);

    // balle attachée au paddle
    if (!ballLaunched) {
        ball = Ball(
            paddle.getPosition().x + 50,
            paddle.getPosition().y - 20
        );
    }
    else {
        ball.update(window.getSize().x, window.getSize().y);
    }

    handleCollisions();

    // perte de vie
    if (ball.getPosition().y > window.getSize().y) {
        lives--;
        resetRound();
    }

    // fin de jeu
    if (lives <= 0) {
        isGameOver = true;
        isRunning = false;
    }

    if (grid.isCleared()) {
        isGameOver = true;
        isWin = true;
        isRunning = false;
    }
}

//COLLISIONS
void Game::handleCollisions() {

    // paddle
    if (ball.getBounds().intersects(paddle.getBounds())) {
        ball.bondY();
    }

    // briques via Grid
    score += grid.handleCollision(ball);
}

//RENDER
void Game::render() {

    window.clear();

    grid.draw(window);
    paddle.draw(window);
   /* ball.draw(window);*/

    drawHUD();

    if (isGameOver)
        drawEndScreen();

    window.display();
}

//HUD
void Game::drawHUD() {
    drawText("Lives: " + std::to_string(lives), 10, 10, 20, sf::Color::White);
    drawText("Score: " + std::to_string(score), 650, 10, 20, sf::Color::White);
}

//FIN
void Game::drawEndScreen() {

    if (isWin)
        drawText("YOU WIN", 400, 250, 40, sf::Color::Green, true);
    else
        drawText("GAME OVER", 400, 250, 40, sf::Color::Red, true);

    drawText("Press R to restart", 400, 320, 20, sf::Color::White, true);
}

//RESET
void Game::resetRound() {

    ballLaunched = false;

    ball = Ball(400, 300);
    paddle = Paddle(350, 550);
}

void Game::resetGame() {

    init();
   /* grid.reset();*/
}

//TEXTE
void Game::drawText(const std::string& str, float x, float y,
    unsigned size, sf::Color color, bool center)
{
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);

    if (center) {
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2, bounds.height / 2);
    }

    text.setPosition(x, y);
    window.draw(text);
}

//LOOP
void Game::play() {

    while (window.isOpen()) {

        float dt = clock.restart().asSeconds();

        handleEvents();

        if (isRunning)
            update(dt);

        render();

        sf::sleep(sf::milliseconds(16));
    }
}