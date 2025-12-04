//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_MAPTILE_H
#define GAME1_MAPTILE_H

#include "Buildings/Building.h"

class MapTile : public IsometricActor
{
   public:
      MapTile( std::string texturePath, SpawnCategory spawnCategory, Mobility mobilityStatus,
               const sf::Vector2f& position = { 0.f, 0.f }, float rotation = 0, const sf::Vector2f& scale = { 1.0f, 1.0f },
               float height = 0, bool isVisible = true );

      void onStart( std::shared_ptr<GameContext>& context ) override;

      void setBuilding( const std::shared_ptr<Building>& newBuilding );

   protected:
      std::string tileTexture;
      std::weak_ptr<Building> building;
};

#endif //GAME1_MAPTILE_H
