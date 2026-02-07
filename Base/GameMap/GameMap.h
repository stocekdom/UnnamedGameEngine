//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_GAMEMAP_H
#define GAME1_GAMEMAP_H

#include "MapGenerator.h"
#include <SFML/System/Vector2.hpp>
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

   private:
      int mapWidth;
      int mapHeight;
      sf::Vector2f mapStart;
      size_t seed;
      // Currently hardcoded. In the future add DI
      MapGenerator generator;
      std::vector<std::weak_ptr<MapTile>> gameMap;

      [[nodiscard]] sf::Vector2i getTileIndex( const sf::Vector2f& position ) const;

      [[nodiscard]] sf::Vector2f getScreenCoords( const sf::Vector2i& tile ) const;
};

#endif //GAME1_GAMEMAP_H
