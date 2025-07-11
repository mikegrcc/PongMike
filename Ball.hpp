//
// Created by Huanming Song on 7/7/25.
//

#ifndef BALL_HPP
#define BALL_HPP
#include <SFML/Graphics.hpp>

class Ball {
public:
    // Constructor: Initializes the ball's properties
    Ball(float startX, float startY);

    // Get the position of the ball
    sf::Vector2f getPosition() const;

    // Get the shape of the ball for drawing
    sf::CircleShape& getShape();

    // Get the velocity of the ball
    sf::Vector2f getVelocity() const;

    // Reverse the Y direction of the ball's movement
    void reboundTopOrBottom();

    // Reverse the X direction of the ball's movement (e.g., paddle hit)
    void reboundPaddle();

    // Reset the ball to the center and reverse its direction
    void reset();

    // Update the ball's position based on its velocity and the frame time
    void update(sf::Time dt);

private:
    sf::CircleShape m_Shape;
    sf::Vector2f m_Velocity;
    float m_Speed = 500.0f;
};



#endif //BALL_HPP
