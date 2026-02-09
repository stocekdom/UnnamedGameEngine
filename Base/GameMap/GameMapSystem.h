//
// Created by dominik on 04.12.25.
//

#ifndef GAME1_GAMEMAPSYSTEM_H
#define GAME1_GAMEMAPSYSTEM_H

#include "GameMap.h"
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "../System.h"

struct GameContext;
class MapTile;
class GameScene;
class Building;

// TODO use sharedptr for map tiles inside gamemap
struct SnapToTileResult
{
   sf::Vector2f position;
   std::weak_ptr<MapTile> tile;
};

// TODO make the map system generic and let the user specify gamemap class, so we dont have to modify base classes for more funcionalitydd
// TODO inherit from system and get the map size from game state
class GameMapSystem : public System
{
   public:

      void init( GameContext* context ) override;

      void onStart() override;

      void update( float dt ) override;

      void generateMap( size_t mapHeight, size_t mapWidth, const sf::Vector2f& mapStart, size_t seed = 0 );

      /**
       * Returns a position in the screen space of the tile center that is closest to the mouse position.
       * If the mouse position is outside the map, it returns the same position.
       * @return A structure with the position and the tile. If the position is out of bounds, the resulting position is the same as input position and tile is nullptr
       */
      [[nodiscard]] SnapToTileResult snapToMapTile( const sf::Vector2i& mousePosition ) const;

      /**
       * Gets the tile at the given position. If the position is out of the map bounds, returns an empty weak pointer.
       */
      [[nodiscard]] std::weak_ptr<MapTile> getMapTile( const sf::Vector2i& mousePosition ) const;

   private:
      std::unique_ptr<GameMap> map{};
      // Raw pointer to avoid overhead since all systems are managed by Game class which outlives this object.
      GameContext* context_ = nullptr;
};

#endif //GAME1_GAMEMAPSYSTEM_H
