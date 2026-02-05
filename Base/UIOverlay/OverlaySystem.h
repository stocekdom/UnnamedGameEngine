//
// Created by dominik on 28.12.25.
//

#ifndef GAME1_OVERLAYSYSTEM_H
#define GAME1_OVERLAYSYSTEM_H

#include "../Renderer.h"
#include "../ComponentSystem.h"
#include "../ComponentContainer.h"
#include "OverlaySpriteComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>

class OverlaySystem : public ComponentSystem
{
   public:
      void init( GameContext* context ) override;

      void onStart() override;

      void render( sf::RenderTarget& target, const Renderer& renderer ) const;

      void update( float dt ) override;

      void onBeforeComponentsDestroyed( Entity entity ) override;

      void onComponentAdded( Entity entity ) override;

   private:
      ComponentContainer<OverlaySpriteComponent>* overlaysContainer = nullptr;
      GameContext* context_ = nullptr;

      void refreshSprites() const;

};

#endif //GAME1_OVERLAYSYSTEM_H
