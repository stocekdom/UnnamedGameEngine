//
// Created by dominik on 03.12.25.
//

#ifndef GAME1_PEASANTHOUSE_H
#define GAME1_PEASANTHOUSE_H

#include "Building.h"

class PeasantHouse : public Building
{
   public:
      explicit PeasantHouse( SpawnCategory spawnCategory, const sf::Vector2f& position = { 0.f, 0.f }, float rotation = 0,
                             const sf::Vector2f& scale = { 1.f, 1.f }, float height = 0, bool isVisible = true );

      void onStart( GameContext* context ) override;
};

#endif //GAME1_PEASANTHOUSE_H
