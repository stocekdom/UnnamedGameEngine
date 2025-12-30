//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_MAPTILE_H
#define GAME1_MAPTILE_H

#include "../../Src/Entities/ResourceActor.h"
#include "../Entity/SpriteActor.h"

class Building;

class MapTile : public SpriteActor
{
   public:
      MapTile( REQ_ARGS, const std::string& texturePath, const ActorParams& params = ActorParams() );

      bool isOccupied() const;

      Resources::Resource getResourceType() const;

      std::weak_ptr<ResourceActor> getResource() const;

      void setBuilding( const std::shared_ptr<Building>& newBuilding );

      void setResource( const std::shared_ptr<ResourceActor>& newResource );

   protected:
      std::weak_ptr<ResourceActor> resource;
      std::weak_ptr<Building> building;
};

#endif //GAME1_MAPTILE_H
