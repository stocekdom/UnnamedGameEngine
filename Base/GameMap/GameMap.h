//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_GAMEMAP_H
#define GAME1_GAMEMAP_H

#include "MapGenerator.h"
#include "TileTypes.h"
#include <memory>
#include <vector>

struct GameContext;

class GameMap
{
   public:
      GameMap( int mapHeight, int mapWidth, const sf::Vector2f& mapStart, size_t seed = 0 );

      void generate( GameContext* context );

      //bool onClick( const sf::Vector2f& location ) override;

      [[nodiscard]] sf::Vector2f snapToMapTile( const sf::Vector2f& mousePosition ) const;

      std::weak_ptr<MapTile> getMapTile( const sf::Vector2f& mousePosition );

      [[nodiscard]] TileIndex getTileIndex( const sf::Vector2f& screenPosition ) const;

      TileIndex generateStartingRegion();

      [[nodiscard]] sf::Vector2f getScreenCoords( const TileIndex& tile ) const;

      void discoverTiles( const TileIndex& tile, unsigned int radius ) const;

   private:
      int mapWidth;
      int mapHeight;
      sf::Vector2f mapStart;
      size_t seed;
      // Currently hardcoded. In the future add DI
      MapGenerator generator;
      std::vector<std::shared_ptr<MapTile>> gameMap;
      std::vector<Region> regions;
};

#endif //GAME1_GAMEMAP_H
