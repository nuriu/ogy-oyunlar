#ifndef PADDLE
#define PADDLE
#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

class Paddle : public sf::RectangleShape
{
  public:
    Paddle(const sf::Vector2f &size, const sf::Vector2f &position,
           const sf::Color &color);
};

#endif
