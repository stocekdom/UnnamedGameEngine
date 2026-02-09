//
// Created by dominik on 08.02.26.
//

#ifndef GAME1_CONSTRUCTIONSYSTEM_H
#define GAME1_CONSTRUCTIONSYSTEM_H

#include "Buildings.h"
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

      bool canConstruct( const std::shared_ptr<Building>& building, const std::shared_ptr<MapTile>& tile ) const;

      bool tryConstruct( std::shared_ptr<Building>& building, std::shared_ptr<MapTile>& tile ) const;

   private:
      GameContext* context_ = nullptr;
};

#endif //GAME1_CONSTRUCTIONSYSTEM_H
