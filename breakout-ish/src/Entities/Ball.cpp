#include <Entities/Ball.hpp>

Ball::Ball(const CoreComponents& components)
    : m_Components(components)
    , m_DeltaX(0.0f)
    , m_DeltaY(0.0f)
    , m_RandomDevice()
    , m_MTGenerator(m_RandomDevice())
    , m_Distributor(0, 3)
{
}

void Ball::initialize()
{
    this->setTexture(m_Components.m_AssetManager->getTexture("balls"));
    this->setTextureRect(sf::IntRect(0, static_cast<int>(m_Distributor(m_MTGenerator) * m_Height),
                                     static_cast<int>(m_Width), static_cast<int>(m_Height)));

    this->setPosition(
        m_Components.m_RenderWindow->getSize().x / 2.0f - this->getLocalBounds().width / 2.0f,
        m_Components.m_RenderWindow->getSize().y / 2.0f - this->getLocalBounds().height / 2.0f);

    m_Distributor = std::uniform_int_distribution<int>(-200, 200);
    m_DeltaX      = m_Distributor(m_MTGenerator);
    m_Distributor = std::uniform_int_distribution<int>(100, 200);
    m_DeltaY      = m_Distributor(m_MTGenerator) * -1.0f;
}

void Ball::processInput() {}

void Ball::update()
{
    this->move(m_DeltaX * m_Components.m_TimePerFrame->asSeconds(),
               m_DeltaY * m_Components.m_TimePerFrame->asSeconds());

    if (this->getPosition().x < 0)
    {
        this->setPosition(0.0f, this->getPosition().y);

        m_DeltaX = -m_DeltaX * 1.1f;
        m_Components.m_AssetManager->playSound("impact");
    }

    if (this->getPosition().x + m_Width >= m_Components.m_RenderWindow->getSize().x)
    {
        this->setPosition(m_Components.m_RenderWindow->getSize().x - m_Width,
                          this->getPosition().y);

        m_DeltaX = -m_DeltaX * 1.1f;
        m_Components.m_AssetManager->playSound("impact");
    }

    if (this->getPosition().y <= 0)
    {
        this->setPosition(this->getPosition().x, 0.0f + m_Height);

        m_DeltaY = -m_DeltaY * 1.1f;
        m_Components.m_AssetManager->playSound("impact");
    }
}

void Ball::render() const
{
    m_Components.m_RenderWindow->draw(*this);
}

bool Ball::isColliding(const sf::Sprite& target) const
{
    auto targetPosition = target.getPosition();
    auto targetBounds   = target.getLocalBounds();
    auto ballPosition   = this->getPosition();

    if (ballPosition.x > targetPosition.x + targetBounds.width or
        targetPosition.x > ballPosition.x + m_Width)
    {
        return false;
    }
    else if (ballPosition.y + m_Height > targetPosition.y + targetBounds.height or
             targetPosition.y > ballPosition.y + m_Height)
    {
        return false;
    }

    return true;
}

void Ball::reset()
{
    this->setPosition(m_Components.m_RenderWindow->getSize().x / 2.0f,
                      m_Components.m_RenderWindow->getSize().y / 2.0f);
    m_DeltaX = 0.0f;
    m_DeltaY = 0.0f;
}
