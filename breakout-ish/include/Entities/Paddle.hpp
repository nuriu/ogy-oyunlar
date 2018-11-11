#ifndef PADDLE_HPP
#define PADDLE_HPP
#pragma once

#include <SFML/Graphics/Sprite.hpp>

class Paddle : public sf::Sprite
{
  public:
    Paddle(const sf::Sprite paddle);
};

#endif // PADDLE_HPP
