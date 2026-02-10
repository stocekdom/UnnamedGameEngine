//
// Created by dominik on 08.02.26.
//

#ifndef GAME1_CONSTRUCTIONSYSTEM_H
#define GAME1_CONSTRUCTIONSYSTEM_H

#include "../../../Base/GameMap/TileTypes.h"
#include "../../../Base/System.h"
#include <memory>

class Building;
class MapTile;

class ConstructionSystem : public System
{
   public:
      void init( GameContext* context ) override;

      void onStart() override;

      void update( float dt ) override;

      [[nodiscard]] bool canConstruct( const std::shared_ptr<Building>& building, const std::shared_ptr<MapTile>& tile ) const;

      [[nodiscard]] bool tryConstruct( std::shared_ptr<Building>& building, std::shared_ptr<MapTile>& tile,
                                       const TileIndex& index ) const;

   private:
      GameContext* context_ = nullptr;

      static constexpr unsigned int DISCOVER_RADIUS_ON_BUILD = 4;
};

#endif //GAME1_CONSTRUCTIONSYSTEM_H
