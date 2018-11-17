#include <Entities/Brick.hpp>

Brick::Brick(const CoreComponents& components, const float x, const float y)
    : m_Components(components)
    , m_X(x)
    , m_Y(y)
    , m_RandomDevice()
    , m_MTGenerator(m_RandomDevice())
    , m_Distributor(0, 6)
{
}

void Brick::initialize()
{
    this->setTexture(m_Components.m_AssetManager->getTexture("bricks"));
    this->setTextureRect(sf::IntRect(0, static_cast<int>(m_Distributor(m_MTGenerator) * m_Height),
                                     static_cast<int>(m_Width), static_cast<int>(m_Height)));
    this->setPosition(m_X, m_Y);
}

void Brick::processInput() {}

void Brick::update() {}

void Brick::render() const
{
    m_Components.m_RenderWindow->draw(*this);
}
