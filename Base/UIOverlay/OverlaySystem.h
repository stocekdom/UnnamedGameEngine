//
// Created by dominik on 28.12.25.
//

#ifndef GAME1_OVERLAYSYSTEM_H
#define GAME1_OVERLAYSYSTEM_H

#include "../Renderer.h"
#include "../System.h"
#include "../ComponentContainer.h"
#include <SFML/Graphics/RenderTarget.hpp>

#include "OverlaySpriteComponent.h"

class OverlaySystem : public System
{
   public:
      OverlaySystem();

      void init( GameContext* context ) override;

      void onStart() override;

      void render( sf::RenderTarget& target, const Renderer& renderer ) const;

      void update( float dt ) override;

      void onBeforeComponentsDestroyed( Entity entity ) override;

      void onComponentAdded( Entity entity ) override;

   private:
      ComponentContainer<OverlaySpriteComponent>* overlaysContainer;
      GameContext* context_;

      void refreshSprites() const;

};

#endif //GAME1_OVERLAYSYSTEM_H
