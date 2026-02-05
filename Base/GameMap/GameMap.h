//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_GAMEMAP_H
#define GAME1_GAMEMAP_H

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

struct GameContext;
class MapTile;

class GameMap
{
   public:
      GameMap( size_t mapHeight, size_t mapWidth, const sf::Vector2f& mapStart );

      void init( GameContext* context );

      //bool onClick( const sf::Vector2f& location ) override;

      [[nodiscard]] sf::Vector2f snapToMapTile( const sf::Vector2f& mousePosition ) const;

      std::weak_ptr<MapTile> getMapTile( const sf::Vector2f& mousePosition );

   private:
      size_t mapWidth;
      size_t mapHeight;
      sf::Vector2f mapStart;
      std::vector<std::weak_ptr<MapTile>> gameMap;

      sf::Vector2i getTileIndex( const sf::Vector2f& position ) const;

      sf::Vector2f getScreenCoords( const sf::Vector2i& tile ) const;
};

#endif //GAME1_GAMEMAP_H
