//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_MAPTILE_H
#define GAME1_MAPTILE_H

#include "../Base/Entity/IsometricActor.h"

class MapTile : public IsometricActor
{
   public:
      MapTile( std::string texturePath, Mobility mobilityStatus, const sf::Vector2f& position = { 0.f, 0.f }, float rotation = 0,
               const sf::Vector2f& scale = { 1.0f, 1.0f }, float height = 0, bool isVisible = true );

      void onStart( std::shared_ptr<GameContext>& context ) override;

   protected:
      std::string tileTexture;
};

#endif //GAME1_MAPTILE_H
