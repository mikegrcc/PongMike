//
// Created by Huanming Song on 7/7/25.
//

#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>

class Ball;
class Paddle;

class Game {
public:
    // Constructor: Sets up the game window, objects, and state
    Game();
    ~Game();

    // The main function to run the entire game
    void run();

private:
    // The main game loop
    void processEvents();
    void update(sf::Time dt);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    sf::RenderWindow m_Window;
    std::unique_ptr<Ball> m_Ball;
    std::unique_ptr<Paddle> m_LeftPaddle;
    std::unique_ptr<Paddle> m_RightPaddle;

    sf::Font m_Font;
    std::unique_ptr<sf::Text> m_ScoreText;
    std::unique_ptr<sf::Text> m_InstructionsText;

    int m_LeftScore = 0;
    int m_RightScore = 0;

    bool m_IsPlaying = false;
};



#endif //GAME_HPP
