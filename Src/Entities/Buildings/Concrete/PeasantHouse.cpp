//
// Created by dominik on 03.12.25.
//

#include "PeasantHouse.h"

PeasantHouse::PeasantHouse( SpawnCategory spawnCategory, const sf::Vector2f& position, float rotation, const sf::Vector2f& scale,
                            float height, bool isVisible )
   : Building( spawnCategory, position, rotation, scale, height, isVisible )
{
}

void PeasantHouse::onStart( GameContext* context )
{
   // TODO add random variants
   sprite.setTexture( context->resourceManager->loadTexture( "Assets/Buildings/house1.png" ) );
   Building::onStart( context );
}

bool PeasantHouse::canBePlaced( const std::shared_ptr<MapTile>& tile )
{
   // Houses can't override resources and be placed on tiles with a resource
   return Building::canBePlaced( tile ) && tile->getResourceType() == Resources::ITEM_NONE;
}
