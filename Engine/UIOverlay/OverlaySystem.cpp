//
// Created by dominik on 28.12.25.
//

#include "OverlaySystem.h"
#include "../GameContext.h"

void OverlaySystem::init( GameContext* context )
{
   context_ = context;
   context->scene->getComponentRegistry().registerComponentType<OverlaySpriteComponent>();
   overlaysContainer = context->scene->getComponentRegistry().getComponentContainer<OverlaySpriteComponent>();
}

void OverlaySystem::onStart()
{
}

void OverlaySystem::render( sf::RenderTarget& target, const Renderer& renderer ) const
{
   for( auto& sprite : *overlaysContainer )
      renderer.render( sprite.sprite, target );
}

void OverlaySystem::update( float dt )
{
   refreshSprites();
}

void OverlaySystem::onBeforeComponentsDestroyed( Entity entity )
{
}

void OverlaySystem::onComponentAdded( Entity entity )
{
   if( !overlaysContainer->hasComponent( entity ) )
      return;

   auto& overlay = overlaysContainer->getComponent( entity );
   overlay.sprite.setTexture( context_->resourceManager->loadTexture( overlay.texturePath ) );

}

void OverlaySystem::refreshSprites() const
{
   for( auto& sprite : *overlaysContainer )
   {
      auto& transform = context_->scene->getComponentRegistry().getComponent<TransformComponent>( sprite.owner );
      sprite.sprite.setPosition( transform.getGlobalPosition() );
      sprite.sprite.setRotation( transform.getGlobalRotation() );
      sprite.sprite.setScale( transform.getGlobalScale() );
   }
}
