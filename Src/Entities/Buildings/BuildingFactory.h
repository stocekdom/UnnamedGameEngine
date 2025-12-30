//
// Created by dominik on 03.12.25.
//

#ifndef GAME1_BUILDINGFACTORY_H
#define GAME1_BUILDINGFACTORY_H

#include <memory>
#include "Building.h"
#include "BuildingType.h"

class BuildingFactory
{
   public:
      static std::shared_ptr<Building> createBuilding( GameScene* scene, BuildingType type, const sf::Vector2f& position = { 0.f, 0.f } );

   private:
      static void addComponent( GameScene* scene, Entity entity, BuildingType type );
};
#endif //GAME1_BUILDINGFACTORY_H
