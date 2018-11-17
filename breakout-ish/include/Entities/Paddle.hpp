#ifndef PADDLE_HPP
#define PADDLE_HPP
#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <Entity.hpp>
#include <CoreComponents.hpp>

class Paddle : public sf::Sprite, public Entity
{
  public:
    float m_DeltaX;
    float m_Width;
    float m_Height;

    explicit Paddle(const CoreComponents& components, unsigned int selectedPaddleIndex);

    void initialize() override;
    void processInput() override;
    void update() override;
    void render() const override;

  private:
    const CoreComponents& m_Components;
    const float           m_PaddleSpeed;
};

#endif // PADDLE_HPP
