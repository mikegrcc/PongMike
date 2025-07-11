//
// Created by Huanming Song on 7/7/25.
//

#ifndef PADDLE_HPP
#define PADDLE_HPP
#include <SFML/Graphics.hpp>


class Paddle {
public:
    // Constructor: Initializes the paddle's properties
    Paddle(float startX, float startY);

    // Get the position of the paddle
    sf::Vector2f getPosition();

    // Get the shape of the paddle for drawing
    sf::RectangleShape& getShape();

    // Move the paddle up
    void moveUp();

    // Move the paddle down
    void moveDown();

    // Stop the paddle's movement
    void stop();

    // Update the paddle's position based on its velocity and frame time
    void update(sf::Time dt, const sf::RenderWindow& window);

private:
    sf::RectangleShape m_Shape;
    float m_Speed = 400.0f;
    sf::Vector2f m_Velocity;
};



#endif //PADDLE_HPP
