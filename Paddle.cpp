//
// Created by Huanming Song on 7/7/25.
//

#include "Paddle.hpp"
Paddle::Paddle(float startX, float startY) {
    m_Shape.setSize(sf::Vector2f(25, 100));
    m_Shape.setFillColor(sf::Color::White);
    m_Shape.setPosition({startX, startY});
}

sf::Vector2f Paddle::getPosition() {
    return m_Shape.getPosition();
}

sf::RectangleShape& Paddle::getShape() {
    return m_Shape;
}

void Paddle::moveUp() {
    m_Velocity.y = -m_Speed;
}

void Paddle::moveDown() {
    m_Velocity.y = m_Speed;
}

void Paddle::stop() {
    m_Velocity.y = 0;
}

void Paddle::update(sf::Time dt, const sf::RenderWindow& window) {
    m_Shape.move(m_Velocity * dt.asSeconds());

    // Prevent paddle from moving off-screen
    if (m_Shape.getPosition().y < 0) {
        m_Shape.setPosition({m_Shape.getPosition().x, 0});
    }
    if (m_Shape.getPosition().y + m_Shape.getSize().y > window.getSize().y) {
        m_Shape.setPosition({m_Shape.getPosition().x, window.getSize().y - m_Shape.getSize().y});
    }
}