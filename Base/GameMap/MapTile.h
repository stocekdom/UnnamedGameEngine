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
      MapTile( REQ_ARGS, const std::string& texturePath, Tile type, const ActorParams& params = ActorParams() );

      [[nodiscard]] bool isOccupied() const;

      [[nodiscard]] Resources::Resource getResourceType() const;

      [[nodiscard]] std::weak_ptr<ResourceActor> getResource() const;

      void setBuilding( const std::shared_ptr<Building>& newBuilding );

      void setResource( const std::shared_ptr<ResourceActor>& newResource );

      [[nodiscard]] Tile getType() const;

   protected:
      Tile type;
      std::weak_ptr<ResourceActor> resource;
      std::weak_ptr<Building> building;
};

#endif //GAME1_MAPTILE_H
