//
// Created by dominik on 14.11.25.
//

#include "MapTile.h"
#include "../Core/Math.h"

MapTile::MapTile( Entity id, GameContext* context, const std::string& texturePath, Tile type, const ActorParams& params )
   : SpriteActor( id, context, texturePath, params ), type( type )
{
   // TODO add getComponent to scene?
   auto& spriteComponent = context->scene->getComponentRegistry().getComponent<SpriteComponent>( id );
   auto& transformComponent = context->scene->getComponentRegistry().getComponent<TransformComponent>( id );

   // Calculate scale based on tile width so all tiles have the same size.
   // We use width because all isometric tiles can be blocks and height tells us nothing about the tile.
   // We need to know the size of the base which is and the height is width/2.
   // See Assets/grass.png for an example. We need to know the dimensions of the isometric diamond.
   float scaleX = Math::IsometricConstants::SPRITE_WIDTH / spriteComponent.getLocalBounds().width;
   transformComponent.setScale( { scaleX, scaleX } );
}

bool MapTile::isOccupied() const
{
   return building.lock() != nullptr;
}

Resources::Resource MapTile::getResourceType() const
{
   if( auto r = resource.lock() )
      return r->getResource();

   return Resources::Resource::ITEM_NONE;
}

std::weak_ptr<ResourceActor> MapTile::getResource() const
{
   return resource;
}

void MapTile::setBuilding( const std::shared_ptr<Building>& newBuilding )
{
   building = newBuilding;
}

void MapTile::setResource( const std::shared_ptr<ResourceActor>& newResource )
{
   resource = newResource;
   // Add as child???
}

Tile MapTile::getType() const
{
   return type;
}
