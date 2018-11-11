#include <Entities/Paddle.hpp>

Paddle::Paddle(const sf::Sprite paddle)
{
    setTexture(*paddle.getTexture());
    setTextureRect(paddle.getTextureRect());
}
