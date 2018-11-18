#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include <CoreComponents.hpp>
#include <Scenes/MenuScene.hpp>

#include <memory>
#include <string>

class Game
{
  public:
    Game(const sf::String& title, unsigned int width, unsigned int height);

    void run();

  private:
    std::shared_ptr<CoreComponents> m_Components;
    std::unique_ptr<sf::Clock>      m_Clock;
    std::unique_ptr<sf::Text>       m_FPSText;

    void processEvents();
    void update();
    void render();
};

#endif // GAME_HPP
