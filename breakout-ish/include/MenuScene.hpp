#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>

#include <Scene.hpp>
#include <CoreComponents.hpp>

#include <memory>
#include <iostream>

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
    std::unique_ptr<sf::CircleShape> m_Shape;
};

#endif // MENU_SCENE_HPP
