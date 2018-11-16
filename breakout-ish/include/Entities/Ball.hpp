#ifndef BALL_HPP
#define BALL_HPP
#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <Entity.hpp>
#include <CoreComponents.hpp>

#include <random>

class Ball : public sf::Sprite, public Entity
{
  public:
    explicit Ball(const CoreComponents& components);

    void initialize() override;
    void processInput() override;
    void update() override;
    void render() const override;

  private:
    const CoreComponents& m_Components;
    const float           m_BallSpeed;
    const float           m_Width  = 16;
    const float           m_Height = 16;

    std::random_device                 m_RandomDevice;
    std::mt19937                       m_MTGenerator;
    std::uniform_int_distribution<int> m_Distributor;
};

#endif // BALL_HPP
