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
      GameMap( size_t mapHeight, size_t mapWidth, const sf::Vector2f& mapStart );

      ~GameMap() = default;

      void init( std::shared_ptr<GameContext>& context );

      bool onClick( const sf::Vector2f& location ) override;

      /**
       * Returns a position in screen space of the tile center that is closest to the mouse position.
       * If the mouse position is outside of the map, returns the same position.
       */
      sf::Vector2f snapToMapTile( const sf::Vector2f& mousePosition );

      /**
       * Gets the tile at the given position. If the position is out of the map bounds, returns an empty weak pointer.
       */
      std::weak_ptr<MapTile> getMapTile( const sf::Vector2f& mousePosition );

   private:

      size_t mapHeight;
      size_t mapWidth;
      sf::Vector2f mapStart;
      std::vector<std::weak_ptr<MapTile>> gameMap;

      sf::Vector2i getTile( const sf::Vector2f& position ) const;

      sf::Vector2f getScreenCoords( const sf::Vector2i& tile ) const;
};

#endif //GAME1_GAMEMAP_H
