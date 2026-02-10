//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_MAPTILE_H
#define GAME1_MAPTILE_H

#include "TileTypes.h"
#include "../../Src/Entities/ResourceActor.h"

class Building;

class MapTile : public SpriteActor
{
   public:
      MapTile( REQ_ARGS, const std::string& texturePath, Tile tile, const ActorParams& params = ActorParams() );

      void onStart( GameContext* context ) override;

      [[nodiscard]] bool isOccupied() const;

      [[nodiscard]] Resources::Resource getResourceType() const;

      [[nodiscard]] std::weak_ptr<ResourceActor> getResource() const;

      void setBuilding( const std::shared_ptr<Building>& newBuilding );

      void setResource( const std::shared_ptr<ResourceActor>& newResource );

      [[nodiscard]] TileType getType() const;

      void onDiscovered() const;

   protected:
      Tile tile;
      std::weak_ptr<ResourceActor> resource;
      std::weak_ptr<Building> building;

      void setColorByRegion() const;
};

#endif //GAME1_MAPTILE_H
