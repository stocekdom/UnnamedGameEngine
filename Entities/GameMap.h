//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_GAMEMAP_H
#define GAME1_GAMEMAP_H

#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include "MapTile.h"
#include "../Base/Input/Clickable.h"

   class GameMap : public Clickable, public std::enable_shared_from_this<GameMap>
{
   public:
      GameMap( TextureManager& textureManager, size_t mapHeight, size_t mapWidth, const sf::Vector2f& mapStart );

      ~GameMap() = default;

      void init( GameScene& scene, CollisionSystem& collisionSystem );

      bool onClick( const sf::Vector2f& location ) override;

   private:

      size_t mapHeight;
      size_t mapWidth;
      // These values only work for dimetric projection. If you need any other projection (true isometric), you'll have to recalculate them.
      const static constexpr float SPRITE_WIDTH = 256;
      const static constexpr float SPRITE_HEIGHT = SPRITE_WIDTH / 2;
      const static constexpr float WORLD_TILE_WIDTH = SPRITE_WIDTH / 4;
      // ====================================================================
      sf::Vector2f mapStart;
      std::vector<std::weak_ptr<MapTile>> gameMap;
      TextureManager& textureManager_;
};

#endif //GAME1_GAMEMAP_H
