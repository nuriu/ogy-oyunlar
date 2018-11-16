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
    float m_DeltaX;
    float m_DeltaY;

    explicit Ball(const CoreComponents& components);

    void initialize() override;
    void processInput() override;
    void update() override;
    void render() const override;

    bool isColliding(const sf::Sprite& target) const;
    void reset();

  private:
    const CoreComponents& m_Components;
    const float           m_Width  = 16.0f;
    const float           m_Height = 16.0f;

    std::random_device                 m_RandomDevice;
    std::mt19937                       m_MTGenerator;
    std::uniform_int_distribution<int> m_Distributor;
};

#endif // BALL_HPP
