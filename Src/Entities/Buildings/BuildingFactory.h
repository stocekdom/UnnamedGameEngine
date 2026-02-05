//
// Created by dominik on 03.12.25.
//

#ifndef GAME1_BUILDINGFACTORY_H
#define GAME1_BUILDINGFACTORY_H

#include "Building.h"
#include "Buildings.h"
#include <memory>

class BuildingFactory
{
   public:
      static std::shared_ptr<Building> createBuilding( GameScene* scene, Buildings::BuildingType type, const sf::Vector2f& position = { 0.f, 0.f } );

   private:
      static void addComponent( GameScene* scene, Entity entity, Buildings::BuildingType type );
};
#endif //GAME1_BUILDINGFACTORY_H
