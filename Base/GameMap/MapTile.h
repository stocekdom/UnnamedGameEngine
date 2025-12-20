//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_MAPTILE_H
#define GAME1_MAPTILE_H

#include "../../Src/Entities/ResourceActor.h"

class Building;

class MapTile : public IsometricActor
{
   public:
      MapTile( std::string texturePath, SpawnCategory spawnCategory, Mobility mobilityStatus,
               const sf::Vector2f& position = { 0.f, 0.f }, float rotation = 0, const sf::Vector2f& scale = { 1.0f, 1.0f },
               float height = 0, bool isVisible = true );

      void onStart( GameContext* context ) override;

      bool isOccupied() const;

      Resources::Resource getResourceType() const;

      std::weak_ptr<ResourceActor> getResource() const;

      void setBuilding( const std::shared_ptr<Building>& newBuilding );

      void setResource( const std::shared_ptr<ResourceActor>& newResource );

   protected:
      std::string tileTexture;
      std::weak_ptr<ResourceActor> resource;
      std::weak_ptr<Building> building;
};

#endif //GAME1_MAPTILE_H
