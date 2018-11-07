#ifndef PADDLE_SELECT_SCENE_HPP
#define PADDLE_SELECT_SCENE_HPP
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <Scene.hpp>
#include <CoreComponents.hpp>

#include <memory>

class PaddleSelectScene : public Scene
{
  public:
    PaddleSelectScene(const CoreComponents& components);

    void initialize() override;
    void processInput() override;
    void update() override;
    void render() const override;

  private:
    const CoreComponents& m_Components;

    std::unique_ptr<sf::Text> m_Title;
    std::unique_ptr<sf::Text> m_LeftArrow;
    std::unique_ptr<sf::Text> m_RightArrow;

    unsigned int m_MenuSelectedIndex;
};

#endif // PADDLE_SELECT_SCENE_HPP
