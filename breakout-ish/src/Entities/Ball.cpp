#include <Entities/Ball.hpp>

Ball::Ball(const CoreComponents& components)
    : m_Components(components)
    , m_BallSpeed(500.0f)
    , m_RandomDevice()
    , m_MTGenerator(m_RandomDevice())
    , m_Distributor(1, 4)
{
}

void Ball::initialize()
{
    setTexture(m_Components.m_AssetManager->getTexture("balls"));
    setTextureRect(sf::IntRect(0, static_cast<int>(m_Distributor(m_MTGenerator) * m_Height),
                               static_cast<int>(m_Width), static_cast<int>(m_Height)));

    setOrigin(m_Width / 2.0f, m_Height / 2.0f);
    setPosition(m_Components.m_RenderWindow->getSize().x / 2.0f,
                m_Components.m_RenderWindow->getSize().y / 2.0f);
}

void Ball::processInput() {}

void Ball::update() {}

void Ball::render() const
{
    m_Components.m_RenderWindow->draw(*this);
}
