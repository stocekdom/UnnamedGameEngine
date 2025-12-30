//
// Created by dominik on 15.12.25.
//

#include "ResourceActor.h"

ResourceActor::ResourceActor( Entity id, GameScene* scene, Resources::Resource resource, Resources::ResourceSource source,
                              float harvestTime, unsigned int harvestAmount, unsigned int amount, const ActorParams& params )
   : SpriteActor( id, scene, std::string{ Resources::SOURCE_TEXTURE_ARRAY[ source ] }, params ),
     amount( amount ),
     resource( resource ),
     source( source ),
     harvestTime( harvestTime ),
     harvestAmount( harvestAmount )
{
   auto spriteComp = scene->getComponentRegistry().getComponent<SpriteComponent>( id );
   spriteComp.setOrigin( { spriteComp.getLocalBounds().width / 2, spriteComp.getLocalBounds().height } );
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
