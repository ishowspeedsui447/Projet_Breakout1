#include "Game.h"

// ================= CONSTRUCTEUR =================
Game::Game()
    : window(sf::VideoMode(800, 600), "Breakout"),
    ball(400, 300),
    paddle(350, 550)
{
    loadStats();
    init();
}

Game::~Game()
{
}

// ================= INIT =================
void Game::init() {
    lives = 3;
    score = 0;
    isGameOver = false;
    isWin = false;
    ballLaunched = false;

    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Erreur : arial.ttf introuvable" << std::endl;
    }

    //chargement des sons
    chargerSon(bufferStart, soundStart, "Sons/starting_sound.wav");
    chargerSon(bufferBrick, soundBrick, "Sons/brick_sound.wav");
    chargerSon(bufferPaddle, soundPaddle, "Sons/paddle_sound.wav");
    chargerSon(bufferWall, soundWall, "Sons/wall_sound.wav");
    chargerSon(bufferLostLife, soundLostLife, "Sons/lostLife_sound.wav");
 
    if (!backgroundMusic.openFromFile("Sons/background_sound.wav")) {
        std::cout << "Erreur : background_sound.wav introuvable" << std::endl;
    }
    else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(40);
    }

    if(!menuMusic.openFromFile("Sons/menu_sound.wav")) {
        std::cout << "Erreur : menu_sound.wav introuvable" << std::endl;
    }
    else {
        menuMusic.setLoop(true);
        menuMusic.setVolume(30);
        menuMusic.play();
    }

    if (!endMusic.openFromFile("Sons/end_sound.wav")) {
        std::cout << "Erreur : end_sound.wav introuvable" << std::endl;
    }
    else {
        endMusic.setLoop(false);
        endMusic.setVolume(30);
    }
}

void Game::chargerSon(sf::SoundBuffer& buffer, sf::Sound& son, const std::string& fichier) {
    if (buffer.loadFromFile(fichier)) {
        son.setBuffer(buffer);
    }
    else {
        std::cout << "Erreur : Impossible de charger " << fichier << std::endl;
    }
}


//LOOP
void Game::play() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        handleEvents();

        if (currentState == State::PLAYING) {
            update(dt);
        }

        render();

        sf::sleep(sf::milliseconds(16));
    }
}

// ================= EVENTS =================

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        switch (currentState) {

            case State::MENU: {
                Menu::Action action = menu.handleEvent(window, event);
                if (action == Menu::Action::Play) {
                    menuMusic.stop();
                    soundStart.play();
                    backgroundMusic.play();
                    resetGame(); 
                    currentState = State::PLAYING;
                }
                else if (action == Menu::Action::Instructions) { currentState = State::INSTRUCTIONS; }
                else if (action == Menu::Action::Stats) { currentState = State::STATS; }
                else if (action == Menu::Action::Quit) { window.close(); }
                break;
            }
                           
            case State::PLAYING: {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                    currentState = State::PAUSE;
                }
                break;
            }

            case State::PAUSE: {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                    currentState = State::PLAYING;
                }
                break;
            }

            case State::INSTRUCTIONS:
            case State::STATS:
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                    currentState = State::MENU;
                }
                break;

            case State::GAMEOVER:
                //Rejouer
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    resetGame();
                    endMusic.stop();
                    soundStart.play();
                    backgroundMusic.play();
                    currentState = State::PLAYING;
                }
                //Retourner au menu
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                    endMusic.stop();
                    menuMusic.play();
                    currentState = State::MENU;
                }
                break;
        }
    }
    if (currentState == State::PLAYING && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        ballLaunched = true;
    }
}

// ================= UPDATE =================

void Game::update(float dt) {
    if (currentState == State::PLAYING) {
        totalTimeSession += dt; //cmpt temps passé
        paddle.update(window.getSize().x);

        if (!ballLaunched) {
            ball.setPosition(paddle.getPosition().x, paddle.getPosition().y - 20);
        }
        else {
            sf::Vector2f pos = ball.getPosition();
            float r = 10.f; //rayon de la balle

            if (pos.x - r <= 0 || pos.x + r >= window.getSize().x || pos.y - r <= 0) {
                soundWall.play();
            }
            ball.update(window.getSize().x, window.getSize().y);
        }

        handleCollisions();

        // Perte de vie
        if (ball.getPosition().y > window.getSize().y) {
            soundLostLife.play();
            lives--;
            if (lives > 0) { resetRound(); }
        }

        // Conditions de fin de partie
        if (lives <= 0 || grid.isCleared()) {
            backgroundMusic.stop();
            endMusic.play();
            // Calcul du temps et sauvegarde
            totalTimeSession += clock.getElapsedTime().asSeconds();
            totalGames++;
            if (score > highScore) { highScore = score; } // Nouveau record

            saveStats();

            if (grid.isCleared()) { isWin = true; }
            else { isWin = false; }

            currentState = State::GAMEOVER;
        }
    }
}

//COLLISIONS
void Game::handleCollisions() {

    // paddle
    if (ball.getBounds().intersects(paddle.getBounds()))
    {
        soundPaddle.play();

        ball.reboundFromPaddle(
            paddle.getPosition().x,
            paddle.getBounds().width
        );
    }
    // briques via Grid
    int points = grid.handleCollision(ball); // On stocke le résultat
    if (points > 0) {
        soundBrick.play(); // JOUE UNIQUEMENT SI ON TOUCHE UNE BRIQUE
        score += points;
    }
}

//RENDER
void Game::render() {
    window.clear();

    switch (currentState) {
    case State::MENU:
        menu.draw(window);
        break;

    case State::PLAYING:
        grid.draw(window);
        paddle.draw(window);
        ball.draw(window);
        drawHUD();
        break;

    case State::PAUSE: {
        grid.draw(window);
        paddle.draw(window);
        ball.draw(window);
        drawHUD();

        drawText("PAUSE", 400, 300, 50, sf::Color::Yellow, true);
        drawText("Appuyez sur P pour reprendre", 400, 360, 20, sf::Color::White, true);
        break;
    }

    case State::INSTRUCTIONS:
        drawInstructions(); // Utilise drawText() pour afficher les touches
        break;

    case State::STATS:
        drawStats(); // Affiche tes variables highScore, totalGames, etc.
        break;

    case State::GAMEOVER:
        drawEndScreen();
        break;
    }

    window.display();
}

//HUD
void Game::drawHUD() {
    drawText("Lives: " + std::to_string(lives), 10, 10, 20, sf::Color::White);
    drawText("Score: " + std::to_string(score), 650, 10, 20, sf::Color::White);
}

//END
void Game::drawEndScreen() {
    if (isWin)
        drawText("VICTOIRE !", 400, 200, 50, sf::Color::Green, true);
    else
        drawText("GAME OVER", 400, 200, 50, sf::Color::Red, true);

    drawText("Score final : " + std::to_string(score), 400, 280, 25, sf::Color::White, true);

    //options
    drawText("Appuyez sur R pour REJOUER", 400, 380, 20, sf::Color::Yellow, true);
    drawText("Appuyez sur M pour le MENU", 400, 430, 20, sf::Color::Cyan, true);

}

//RESET
void Game::resetRound() {
    ballLaunched = false;

    ball = Ball(400, 300);
    paddle = Paddle(350, 550);
}

void Game::resetGame() {
    lives = 3;
    score = 0;
    ballLaunched = false;
    isWin = false;
    grid.reset();
    resetRound();
    clock.restart(); // On remet le chrono à zéro pour la partie
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

void Game::drawInstructions() {
    drawText("COMMENT JOUER", 400, 100, 30, sf::Color::Yellow, true);
    drawText("Espace : Lancer la balle", 400, 200, 20, sf::Color::White, true);
    drawText("Fleches : Deplacer le paddle", 400, 250, 20, sf::Color::White, true);
    drawText("P : Pause / Reprendre", 400, 280, 20, sf::Color::White, true);

    drawText("Appuyez sur M pour revenir au menu", 400, 450, 15, sf::Color::Cyan, true);
}

void Game::drawStats() {
    drawText("STATISTIQUES DU JEU", 400, 80, 35, sf::Color::Yellow, true);
    drawText("Meilleur Score : " + std::to_string(highScore), 400, 180, 25, sf::Color::White, true);
    drawText("Parties jouees : " + std::to_string(totalGames), 400, 240, 25, sf::Color::White, true);
    drawText("Temps total : " + std::to_string((int)totalTimeSession) + " secondes", 400, 300, 25, sf::Color::White, true);

    drawText("Appuyez sur M pour revenir au Menu", 400, 500, 18, sf::Color::Cyan, true);
}

void Game::saveStats() {
    std::ofstream file("stats.txt");

    if (file.is_open()) {
        file << highScore << "\n";
        file << totalGames << "\n";
        file << totalTimeSession << "\n";
        file.close();
    }
}

void Game::loadStats() {
    std::ifstream file("stats.txt");

    if (file.is_open()) {
        file >> highScore;
        file >> totalGames;
        file >> totalTimeSession;
        file.close();
    }
}
