//
// Created by dominik on 15.12.25.
//

#include "ResourceActor.h"

ResourceActor::ResourceActor( const sf::Vector2f& position, float rotation, const sf::Vector2f& scale, bool isVisible,
                              unsigned int amount, Resources::Resource resource, Resources::ResourceSource source,
                              float harvestTime, unsigned int harvestAmount )
   : IsometricActor( SpawnCategory::WORLD, Mobility::STATIC, position, rotation, scale, 0, isVisible ),
     amount( amount ),
     resource( resource ),
     source( source ),
     harvestTime( harvestTime ),
     harvestAmount( harvestAmount )
{
}

void ResourceActor::onStart( GameContext* context )
{
   sprite.setTexture( context->resourceManager->loadTexture( Resources::SOURCE_TEXTURE_ARRAY[ source ] ) );
   IsometricActor::onStart( context );
   sprite.setOrigin( sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height );
}

unsigned int ResourceActor::getAmount() const
{
   return amount;
}

float ResourceActor::getHarvestTime() const
{
   return harvestTime;
}

Resources::Resource ResourceActor::getResource() const
{
   return resource;
}

unsigned int ResourceActor::harvest() const
{
   // add removal from amount
   return harvestAmount;
}
