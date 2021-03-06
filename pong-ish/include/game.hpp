#ifndef GAME
#define GAME
#pragma once

#include <memory>
#include <random>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "paddle.hpp"

class Game
{
  public:
    Game(const sf::String& title, unsigned int width, unsigned int height);

    void run();

  private:
    void initGameRound();
    void processEvents();
    void update();
    void render();

  private:
    std::unique_ptr<sf::RenderWindow> m_Window;
    std::unique_ptr<sf::Font>         m_Font;
    std::unique_ptr<sf::Text>         m_Title;
    std::unique_ptr<sf::Text>         m_StatusText;
    std::unique_ptr<sf::Text>         m_PlayerOneScoreText;
    std::unique_ptr<sf::Text>         m_PlayerTwoScoreText;
    std::unique_ptr<Paddle>           m_PlayerOne;
    std::unique_ptr<Paddle>           m_PlayerTwo;
    std::unique_ptr<Paddle>           m_Ball;

    std::random_device                 m_RandomDevice;
    std::mt19937                       m_MTGenerator;
    std::uniform_int_distribution<int> m_Distributor;

    sf::Clock m_Clock;

    float m_BallAngle;
    int   m_PlayerOneScore = 0;
    int   m_PlayerTwoScore = 0;
    bool  m_IsPlaying;

    const float paddleSpeed = 500.f;
    const float ballSpeed   = 300.f;
    const float pi          = 3.14159f;
};

#endif
