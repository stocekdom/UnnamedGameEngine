//
// Created by dominik on 03.12.25.
//

#ifndef GAME1_BUILDING_H
#define GAME1_BUILDING_H

#include "../../../Base/Entity/IsometricActor.h"

class Building : public IsometricActor
{
   public:
      Building( SpawnCategory spawnCategory, const sf::Vector2f& position, float rotation, const sf::Vector2f& scale,
                float height, bool isVisible );

      void onStart( GameContext* context ) override;
};

#endif //GAME1_BUILDING_H
