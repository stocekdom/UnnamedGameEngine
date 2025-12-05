//
// Created by dominik on 04.12.25.
//

#ifndef GAME1_UISYSTEM_H
#define GAME1_UISYSTEM_H

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Renderer.h"

class UIElement;
class GameContext;

class UISystem
{
   public:
      UISystem();

      void onStart( sf::RenderWindow& window, GameContext* context );

      void renderUI( sf::RenderTarget& target, const Renderer& renderer );

      bool onLeftClick( const sf::Vector2i& position );

      void addUiRootComponent( const std::shared_ptr<UIElement>& root );

   private:
      std::shared_ptr<sf::View> uiView;
      std::shared_ptr<UIElement> uiRoot;
};
#endif //GAME1_UISYSTEM_H
