//
// Created by dominik on 22.12.25.
//

#include "SpriteSystem.h"
#include "../GameContext.h"
#include "../Transform/TransformComponent.h"

void SpriteSystem::init( GameContext* context )
{
   gameContext = context;
   auto& registry = context->scene->getComponentRegistry();
   registry.registerComponentType<SpriteComponent>();

   spriteContainer = registry.getComponentContainer<SpriteComponent>();
}

void SpriteSystem::update( float dt )
{
   // Insert the newly added static sprites. Their transforms are now valid since transform system updates first
   // Doing this without checking size is faster than looping over empty vector and than clearing it
   for( auto& pendingStaticSprite: pendingStaticSprites )
   {
      auto& transform = gameContext->scene->getComponentRegistry().getComponent<TransformComponent>(
         pendingStaticSprite.owner );
      setSpriteTransform( pendingStaticSprite, transform );

      auto it = std::ranges::lower_bound( staticSprites, pendingStaticSprite,
                                          []( const SpriteRenderProxy& a, const SpriteRenderProxy& b ) {
                                             return a.sortKey < b.sortKey;
                                          } );

      staticSprites.insert( it, std::move( pendingStaticSprite ) );
   }

   pendingStaticSprites.clear();

   // Update movable sprites position
   refreshSprites( movableSprites );
   // TODO sort movables
}

void SpriteSystem::onStart()
{
   staticSprites.reserve( pendingStaticSprites.size() );

   // Sort the statics before the game begins
   for( auto& pendingStaticSprite: pendingStaticSprites )
   {
      auto& transform = gameContext->scene->getComponentRegistry().getComponent<TransformComponent>(
         pendingStaticSprite.owner );
      setSpriteTransform( pendingStaticSprite, transform );

      staticSprites.push_back( std::move( pendingStaticSprite ) );
   }

   pendingStaticSprites.clear();

   std::ranges::sort( staticSprites, []( const SpriteRenderProxy& a, const SpriteRenderProxy& b ) {
      return a.sortKey < b.sortKey;
   } );
}

void SpriteSystem::render( sf::RenderTarget& target, const Renderer& renderer ) const
{
   // TODO add merging of static and movables
   for( auto& sprite: staticSprites )
      renderer.render( sprite.sprite, target );
}

void SpriteSystem::onBeforeComponentsDestroyed( Entity entity )
{
   if( !spriteContainer->hasComponent( entity ) )
      return;

   auto& component = spriteContainer->getComponent( entity );

   if( component.getMobility() == SpriteMobility::STATIC )
      eraseFromProxies( staticSprites, entity );
   else if( component.getMobility() == SpriteMobility::MOVABLE )
      eraseFromProxies( movableSprites, entity );
}

void SpriteSystem::onComponentAdded( Entity entity )
{
   if( !spriteContainer->hasComponent( entity ) )
      return;

   auto& component = spriteContainer->getComponent( entity );

   if( component.getMobility() == SpriteMobility::STATIC )
      pendingStaticSprites.push_back( makeRenderProxy( entity, component ) );
   else if( component.getMobility() == SpriteMobility::MOVABLE )
      movableSprites.push_back( makeRenderProxy( entity, component ) );
   // Movables go directly to the right array since they are updated every frame
}

SpriteRenderProxy SpriteSystem::makeRenderProxy( Entity entity, SpriteComponent& spriteComponent ) const
{
   SpriteRenderProxy renderProxy;
   renderProxy.owner = entity;
   renderProxy.sprite.setTexture( gameContext->resourceManager->loadTexture( spriteComponent.texturePath ) );
   spriteComponent.globalBounds = renderProxy.sprite.getGlobalBounds();
   spriteComponent.localBounds = renderProxy.sprite.getLocalBounds();
   // Set the origin, which is represented as a percentage of the bounding rectangle
   renderProxy.sprite.setOrigin( spriteComponent.localBounds.width * spriteComponent.origin.x,
                                 spriteComponent.localBounds.height * spriteComponent.origin.y );

   return renderProxy;
}

void SpriteSystem::eraseFromProxies( std::vector<SpriteRenderProxy>& v, Entity entity )
{
   std::erase_if( v, [entity]( const SpriteRenderProxy& p ) { return p.owner == entity; } );
}

void SpriteSystem::refreshSprites( std::vector<SpriteRenderProxy>& v ) const
{
   for( auto& sprite: v )
   {
      auto& transform = gameContext->scene->getComponentRegistry().getComponent<TransformComponent>( sprite.owner );
      sprite.sprite.setPosition( transform.getGlobalPosition() );
      sprite.sprite.setRotation( transform.getGlobalRotation() );
      sprite.sprite.setScale( transform.getGlobalScale() );

      SpriteComponent& spriteComp = spriteContainer->getComponent( sprite.owner );

      spriteComp.globalBounds = sprite.sprite.getGlobalBounds();
      checkOrigin( spriteComp, sprite );
   }
}

void SpriteSystem::checkOrigin( SpriteComponent& spriteComponent, SpriteRenderProxy& sprite )
{
   if( spriteComponent.isOriginDirty() )
   {
      sprite.sprite.setOrigin( spriteComponent.origin );
      spriteComponent.setUndirty();
   }
}

void SpriteSystem::setSpriteTransform( SpriteRenderProxy& proxy, const TransformComponent& transform )
{
   proxy.sortKey = transform.getGlobalPosition().y;
   proxy.sprite.setPosition( transform.getGlobalPosition() );
   proxy.sprite.setRotation( transform.getGlobalRotation() );
   proxy.sprite.setScale( transform.getGlobalScale() );
}
