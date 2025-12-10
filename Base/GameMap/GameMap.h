//
// Created by dominik on 14.11.25.
//

#ifndef GAME1_GAMEMAP_H
#define GAME1_GAMEMAP_H

#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include "MapTile.h"
#include "../Input/Clickable.h"

class GameMap : public Clickable, public std::enable_shared_from_this<GameMap>
{
   public:
      GameMap( size_t mapHeight, size_t mapWidth, const sf::Vector2f& mapStart );

      void init( GameContext* context );

      bool onClick( const sf::Vector2f& location ) override;

      sf::Vector2f snapToMapTile( const sf::Vector2f& mousePosition ) const;

      std::weak_ptr<MapTile> getMapTile( const sf::Vector2f& mousePosition );

   private:
      size_t mapWidth;
      std::vector<std::weak_ptr<MapTile>> gameMap;
      size_t mapHeight;
      sf::Vector2f mapStart;

      sf::Vector2i getTileIndex( const sf::Vector2f& position ) const;

      sf::Vector2f getScreenCoords( const sf::Vector2i& tile ) const;
};

#endif //GAME1_GAMEMAP_H
