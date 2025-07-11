//
// Created by Huanming Song on 7/7/25.
//

#include "Ball.hpp"
#include <random>

sf::Vector2f speed_gen(const float speed) {
    static std::default_random_engine generator(std::random_device{}());

    const auto sp_sqr = speed * speed;
    static constexpr float direction[2] = {-1.0f, 1.0f};

    static std::uniform_real_distribution dist(sp_sqr / 10.0f, 9.0f * sp_sqr / 10.0f);
    static std::uniform_int_distribution<> dir(0, 1);

    const auto generated = dist(generator);
    return {
        direction[dir(generator)] * sqrt(generated),
        direction[dir(generator)] * sqrt(sp_sqr - generated)
    };
}

Ball::Ball(float startX, float startY) {
    m_Shape.setRadius(10.0f);
    m_Shape.setFillColor(sf::Color::White);
    m_Shape.setPosition({startX, startY});
    m_Velocity = speed_gen(m_Speed);
}

sf::Vector2f Ball::getPosition() const {
    return m_Shape.getPosition();
}

sf::CircleShape &Ball::getShape() {
    return m_Shape;
}

sf::Vector2f Ball::getVelocity() const {
    return m_Velocity;
}

void Ball::reboundTopOrBottom() {
    m_Velocity.y = -m_Velocity.y;
}

void Ball::reboundPaddle() {
    m_Velocity.x = -m_Velocity.x;
}

void Ball::reset() {
    m_Shape.setPosition({800 / 2.0f, 600 / 2.0f});
    m_Velocity = speed_gen(m_Speed);
}

void Ball::update(sf::Time dt) {
    m_Shape.move(m_Velocity * dt.asSeconds());
}
