#ifndef GAME
#define GAME
#pragma once

#include <memory>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "paddle.hpp"

class Game
{
  public:
    Game(const sf::String &title, const unsigned int width, const unsigned int height);

    void run();

  private:
    void initGameRound();
    void processEvents();
    void update();
    void render();

  private:
    std::unique_ptr<sf::RenderWindow> m_Window;
    std::unique_ptr<Paddle> m_PlayerOne;
    std::unique_ptr<Paddle> m_PlayerTwo;
    std::unique_ptr<Paddle> m_Ball;

    sf::Clock m_Clock;

    float m_BallAngle;
    int m_PlayerOneScore = 0;
    int m_PlayerTwoScore = 0;
    bool m_IsPlaying;

    const float paddleSpeed = 500.f;
    const float ballSpeed = 300.f;
    const float pi = 3.14159f;
};

#endif
