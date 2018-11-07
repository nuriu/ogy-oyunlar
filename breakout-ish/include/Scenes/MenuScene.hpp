#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <Scene.hpp>
#include <CoreComponents.hpp>
#include <Scenes/PaddleSelectScene.hpp>

#include <memory>

class MenuScene : public Scene
{
  public:
    MenuScene(std::shared_ptr<CoreComponents> components);

    void initialize() override;
    void processInput() override;
    void update() override;
    void render() const override;

  private:
    std::shared_ptr<CoreComponents> m_Components;
    std::unique_ptr<sf::Text> m_Title;
    std::unique_ptr<sf::Text> m_Start;
    std::unique_ptr<sf::Text> m_HighScores;

    unsigned int m_MenuSelectedIndex;
};

#endif // MENU_SCENE_HPP
