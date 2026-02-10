//
// Created by dominik on 14.11.25.
//

#include "MapTile.h"
#include "../Core/Math.h"

MapTile::MapTile( Entity id, GameContext* context, const std::string& texturePath, Tile tile, const ActorParams& params )
   : SpriteActor( id, context, texturePath, params ), tile( tile )
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

// TODO temporary. delete after and make a button for showing regions + Add borders
void MapTile::onStart( GameContext* context )
{
   SpriteActor::onStart( context );
   // Default state = undiscovered -> black tile
   context->spriteSystem->setSpriteColor( entity, sf::Color::Black );
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

TileType MapTile::getType() const
{
   return tile.type;
}

void MapTile::onDiscovered() const
{
   setColorByRegion();
}

void MapTile::setColorByRegion() const
{
   sf::Color color;
   uint8_t alpha = 245;
   switch( tile.regionId % 12 )
   {
      case 0: color = sf::Color( 255, 0, 0, alpha );
         break;
      case 1: color = sf::Color( 255, 255, 255, alpha );
         break;
      case 2: color = sf::Color( 0, 0, 255, alpha );;
         break;
      case 3: color = sf::Color( 255, 255, 0, alpha );;
         break;
      case 4: color = sf::Color( 255, 0, 255, alpha );;
         break;
      case 5: color = sf::Color( 0, 255, 0, alpha );
         break;
      case 6: color = sf::Color( 0, 255, 255, alpha );
         break;
      case 7: color = sf::Color( 120, 255, 120, alpha );
         break;
      case 8: color = sf::Color( 255, 100, 100, alpha );
         break;
      case 9: color = sf::Color( 255, 255, 100, alpha );
         break;
      case 10: color = sf::Color( 100, 255, 255, alpha );
         break;
      case 11: color = sf::Color( 255, 100, 255, alpha );
         break;
      default: color = sf::Color::White;
         break;
   }

   if( tile.regionId == 0 )
      color = sf::Color::White;

   context_->spriteSystem->setSpriteColor( entity, color );
}
