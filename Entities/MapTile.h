//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_MAPTILE_H
#define GAME1_MAPTILE_H

#include "../Base/Entity/Actor.h"

class MapTile : public Actor
{
   public:
      MapTile( TextureManager& textureManager, const std::string& texturePath, const sf::Vector2f& position, float rotation,
               const sf::Vector2f& scale, bool isVisible );

      void init( GameScene& scene, CollisionSystem& collisionSystem ) override;
};
#endif //GAME1_MAPTILE_H
