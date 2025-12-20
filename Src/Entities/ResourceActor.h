//
// Created by dominik on 15.12.25.
//

#ifndef GAME1_RESOURCEACTOR_H
#define GAME1_RESOURCEACTOR_H
#include "../GameItems.h"
#include "../../Base/Entity/IsometricActor.h"

class ResourceActor : public IsometricActor
{
   public:
      ResourceActor( const sf::Vector2f& position, float rotation, const sf::Vector2f& scale, bool isVisible, unsigned int amount,
                     Resources::Resource resource, Resources::ResourceSource source, float harvestTime,
                     unsigned int harvestAmount = 1 );

      void onStart( GameContext* context ) override;

      unsigned int getAmount() const;

      float getHarvestTime() const;

      Resources::Resource getResource() const;

      /**
       * Harvest the resource. Works like inventory.removeItem()
       * @return Return
       */
      unsigned int harvest() const;

   private:
      unsigned int amount;
      Resources::Resource resource;
      Resources::ResourceSource source;
      // Time to harvest the resource in seconds
      float harvestTime;
      unsigned int harvestAmount;
};
#endif //GAME1_RESOURCEACTOR_H
