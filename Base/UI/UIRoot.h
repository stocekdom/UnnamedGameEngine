//
// Created by dominik on 23.11.25.
//

#ifndef GAME1_UIROOT_H
#define GAME1_UIROOT_H

#include "UIElement.h"
#include "../Event/Events.h"

class UIRoot : public UIElement
{
   public:
      explicit UIRoot( const std::shared_ptr<UIElement>& menuLayer );

      void onStart( GameContext* context ) override;

      void setMenuLayer( const std::shared_ptr<UIElement>& newMenuLayer );

      void draw( sf::RenderTarget& target, const Renderer& renderer ) override;

      bool onClick( const sf::Vector2f& position ) override;

   private:
      void onPauseGame( const GamePaused& event );

      void onResumeGame( const GameResumed& event );

      std::shared_ptr<UIElement> menuLayer;
};

#endif //GAME1_UIROOT_H
