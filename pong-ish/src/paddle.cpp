#include "paddle.hpp"

Paddle::Paddle(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color)
{
    this->setSize(size);
    this->setPosition(position);
    this->setFillColor(color);
}
