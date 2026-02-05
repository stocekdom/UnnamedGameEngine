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
struct GameContext;

class UISystem
{
   public:
      UISystem();

      void onStart( sf::RenderWindow& window, GameContext* context );

      void render( sf::RenderTarget& target, const Renderer& renderer ) const;

      [[nodiscard]] bool onLeftClick( const sf::Vector2i& position ) const;

      void addUiRootComponent( const std::shared_ptr<UIElement>& root );

   private:
      std::shared_ptr<UIElement> uiRoot;
};
#endif //GAME1_UISYSTEM_H
