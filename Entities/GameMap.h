//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_GAMEMAP_H
#define GAME1_GAMEMAP_H

#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include "../Base/Scene.h"

class GameMap
{
   public:
      GameMap( TextureManager& textureManager, size_t mapHeight, size_t mapWidth, const sf::Vector2f& mapStart );

      void init( GameScene& scene, CollisionSystem& collisionSystem );

   private:

      size_t mapHeight;
      size_t mapWidth;
      const static constexpr float SPRITE_WIDTH = 256;
      const static constexpr float SPRITE_HEIGHT = SPRITE_WIDTH / 2;
      const static constexpr float WORLD_TILE_WIDTH = SPRITE_WIDTH / 2;
      sf::Vector2f mapStart;
      std::vector<float> gameMap;
      TextureManager& textureManager_;
};

#endif //GAME1_GAMEMAP_H
