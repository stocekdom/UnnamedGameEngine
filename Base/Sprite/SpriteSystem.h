//
// Created by dominik on 21.12.25.
//

#ifndef GAME1_SPRITESYSTEM_H
#define GAME1_SPRITESYSTEM_H

#include "../System.h"
#include "../Renderer.h"
#include "../ComponentContainer.h"
#include "SpriteComponent.h"
#include "SpriteRenderProxy.h"
#include <vector>

struct TransformComponent;

// TODO handle sprite visibility
class SpriteSystem : public System
{
   public:
      explicit SpriteSystem() = default;

      void init( GameContext* context ) override;

      void update( float dt ) override;

      void onStart() override;

      void render( sf::RenderTarget& target, const Renderer& renderer ) const;

      void onBeforeComponentsDestroyed( Entity entity ) override;

      void onComponentAdded( Entity entity ) override;

   private:
      GameContext* gameContext = nullptr;
      // Component containers
      ComponentContainer<SpriteComponent>* spriteContainer = nullptr;

      std::vector<SpriteRenderProxy> staticSprites;
      std::vector<SpriteRenderProxy> movableSprites;
      // List of static sprites whose transform isn't set yet.
      // We use this because static entities are inserted only once and than they don't move and don't check their transform every frame
      // This way we can only update them and insert them once. In every frame we check this array and update pending static sprites.
      // Every frame the transforms are already updated since transform system updates first, so we can just update everything in the array
      std::vector<SpriteRenderProxy> pendingStaticSprites;

      [[nodiscard]] SpriteRenderProxy makeRenderProxy( Entity entity, SpriteComponent& spriteComponent ) const;

      static void eraseFromProxies( std::vector<SpriteRenderProxy>& v, Entity entity );

      inline void refreshSprites( std::vector<SpriteRenderProxy>& v ) const;

      static void checkOrigin( SpriteComponent& spriteComponent, SpriteRenderProxy& sprite );

      static void setSpriteTransform( SpriteRenderProxy& proxy, const TransformComponent& transform );
};

#endif //GAME1_SPRITESYSTEM_H
