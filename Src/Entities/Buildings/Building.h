//
// Created by dominik on 03.12.25.
//

#ifndef GAME1_BUILDING_H
#define GAME1_BUILDING_H

#include "../../../Base/Entity/IsometricActor.h"
#include "../../../Base/GameMap/MapTile.h"

class Building : public IsometricActor
{
   public:
      Building( SpawnCategory spawnCategory, const sf::Vector2f& position, float rotation, const sf::Vector2f& scale,
                float height, bool isVisible );

      void onStart( GameContext* context ) override;

      void setOverlayColor( const sf::Color& color );

      // TODO add a whole context instead of just on tile
      /**
       * Checks if the building can be placed on a tile
       * @param tile The tile to be tested
       * @return If a building can be placed on a tile
       */
      virtual bool canBePlaced( const std::shared_ptr<MapTile>& tile );

      /**
       * Runs a necessary setup for the building after it's been placed on a tile
       * @param tile A map tile this building is placed on
       */
      virtual void onPlaced( const std::shared_ptr<MapTile>& tile );
};

#endif //GAME1_BUILDING_H
