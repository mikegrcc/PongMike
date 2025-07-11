//
// Created by Huanming Song on 7/7/25.
//

#include "Game.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "EmbeddedFont.hpp"

Game::Game()
    : m_Window(sf::VideoMode({800, 600}), "SFML Pong"),
      m_Ball(std::make_unique<Ball>(800 / 2.0f, 600 / 2.0f)),
      m_LeftPaddle(std::make_unique<Paddle>(50.f, 600 / 2.0f - 50.f)),
      m_RightPaddle(std::make_unique<Paddle>(725.f, 600 / 2.0f - 50.f))
{
    if (!m_Font.openFromMemory(assets_Roboto_SemiBold_ttf, assets_Roboto_SemiBold_ttf_len))
    {
        throw std::runtime_error("Failed to load font from memory!");
    }
    m_ScoreText = std::make_unique<sf::Text>(m_Font);
    m_InstructionsText = std::make_unique<sf::Text>(m_Font);

    m_ScoreText->setCharacterSize(40);
    m_ScoreText->setFillColor(sf::Color::White);
    m_ScoreText->setPosition({350, 20});

    m_InstructionsText->setCharacterSize(20);
    m_InstructionsText->setFillColor(sf::Color::White);
    m_InstructionsText->setString("Press Space to start!\nLeft Paddle: W/S\nRight Paddle: Up/Down");
    m_InstructionsText->setOrigin({
        m_InstructionsText->getLocalBounds().position.x / 2, m_InstructionsText->getLocalBounds().position.y / 2
    });
    m_InstructionsText->setPosition({400, 300});
}

Game::~Game() = default;


void Game::run() {
    sf::Clock clock;
    // Set a constant time per frame for the game logic (e.g., 60 updates per second)
    constexpr sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_Window.isOpen()) {
        // Process events once per visual frame
        processEvents();

        // Add the elapsed time since the last loop iteration
        timeSinceLastUpdate += clock.restart();

        // Update the game logic in fixed steps
        while (timeSinceLastUpdate >= TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            if (m_IsPlaying) {
                // Pass the fixed timestep to the update function
                update(TimePerFrame);
            }
        }

        // Render the result
        render();
    }
}

void Game::processEvents() {
    while (auto event = m_Window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_Window.close();
        }
        if (event->is<sf::Event::KeyPressed>()) {
            handlePlayerInput(event->getIf<sf::Event::KeyPressed>()->code, true);
        }
        if (event->is<sf::Event::KeyReleased>()) {
            handlePlayerInput(event->getIf<sf::Event::KeyReleased>()->code, false);
        }
    }
}

void Game::handlePlayerInput(const sf::Keyboard::Key key, const bool isPressed) {
    // Start the game
    if (key == sf::Keyboard::Key::Space && !m_IsPlaying) {
        m_IsPlaying = true;
    }

    // Left paddle movement
    if (key == sf::Keyboard::Key::W) {
        isPressed ? m_LeftPaddle->moveUp() : m_LeftPaddle->stop();
    } else if (key == sf::Keyboard::Key::S) {
        isPressed ? m_LeftPaddle->moveDown() : m_LeftPaddle->stop();
    }

    // Right paddle movement
    if (key == sf::Keyboard::Key::Up) {
        isPressed ? m_RightPaddle->moveUp() : m_RightPaddle->stop();
    } else if (key == sf::Keyboard::Key::Down) {
        isPressed ? m_RightPaddle->moveDown() : m_RightPaddle->stop();
    }
}


void Game::update(sf::Time dt) {
    m_Ball->update(dt);
    m_LeftPaddle->update(dt, m_Window);
    m_RightPaddle->update(dt, m_Window);

    // --- Wall Collision Logic ---
    // Check if the ball has hit the top or bottom of the window
    if (m_Ball->getPosition().y < 0 || (m_Ball->getPosition().y + m_Ball->getShape().getRadius() * 2) > m_Window.getSize().y) {
        // Reverse the ball's vertical velocity
        m_Ball->reboundTopOrBottom();
    }

    const sf::FloatRect ballBounds = m_Ball->getShape().getGlobalBounds();
    const sf::FloatRect leftPaddleBounds = m_LeftPaddle->getShape().getGlobalBounds();
    const sf::FloatRect rightPaddleBounds = m_RightPaddle->getShape().getGlobalBounds();

    // Ball and paddle collision
    if (auto intersection = ballBounds.findIntersection(leftPaddleBounds))
    {
        m_Ball->reboundPaddle();
        // Use .position.x, .size.x, and .position.y
        m_Ball->getShape().setPosition({leftPaddleBounds.position.x + leftPaddleBounds.size.x, ballBounds.position.y});
    }
    else if (auto intersection = ballBounds.findIntersection(rightPaddleBounds))
    {
        m_Ball->reboundPaddle();
        // Use .position.x, .size.x, and .position.y
        m_Ball->getShape().setPosition({rightPaddleBounds.position.x - ballBounds.size.x, ballBounds.position.y});
    }
    else if (ballBounds.position.x ) {}

    // Scoring
    if (m_Ball->getPosition().x < 0) {
        m_RightScore++;
        m_Ball->reset();
    }
    if (m_Ball->getPosition().x > m_Window.getSize().x) {
        m_LeftScore++;
        m_Ball->reset();
    }

    // Update score text
    std::stringstream ss;
    ss << m_LeftScore << " : " << m_RightScore;
    m_ScoreText->setString(ss.str());
}

void Game::render() {
    m_Window.clear(sf::Color::Black);

    if (!m_IsPlaying) {
        m_Window.draw(*m_InstructionsText);
    } else {
        m_Window.draw(m_Ball->getShape());
        m_Window.draw(m_LeftPaddle->getShape());
        m_Window.draw(m_RightPaddle->getShape());
        m_Window.draw(*m_ScoreText);
    }

    m_Window.display();
}