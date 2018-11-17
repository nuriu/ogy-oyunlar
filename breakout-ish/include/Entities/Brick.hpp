#ifndef BRICK_HPP
#define BRICK_HPP

#include <SFML/Graphics/Sprite.hpp>

#include <Entity.hpp>
#include <CoreComponents.hpp>

#include <random>

class Brick : public sf::Sprite, public Entity
{
  public:
    const float m_Width  = 64.0f;
    const float m_Height = 30.0f;

    explicit Brick(const CoreComponents& components, float x, float y);

    void initialize() override;
    void processInput() override;
    void update() override;
    void render() const override;

    float getX() const;
    float getY() const;

  private:
    const CoreComponents& m_Components;
    const float           m_X;
    const float           m_Y;

    std::random_device                 m_RandomDevice;
    std::mt19937                       m_MTGenerator;
    std::uniform_int_distribution<int> m_Distributor;
};

#endif // BRICK_HPP
