//
// Created by dominik on 15.12.25.
//

#ifndef GAME1_RESOURCEACTOR_H
#define GAME1_RESOURCEACTOR_H

#include "../GameItems.h"
#include "../../Base/Entity/SpriteActor.h"

class ResourceActor : public SpriteActor
{
   public:
      ResourceActor( REQ_ARGS, Resources::Resource resource, Resources::ResourceSource source, float harvestTime,
                     unsigned int harvestAmount = 1, unsigned int amount = 9999, const ActorParams& params = ActorParams() );

      [[nodiscard]] unsigned int getAmount() const;

      [[nodiscard]] float getHarvestTime() const;

      [[nodiscard]] Resources::Resource getResource() const;

      /**
       * Harvest the resource. Works like inventory.removeItem()
       * @return Return
       */
      [[nodiscard]] unsigned int harvest() const;

   private:
      unsigned int amount;
      Resources::Resource resource;
      Resources::ResourceSource source;
      // Time to harvest the resource in seconds
      float harvestTime;
      unsigned int harvestAmount;
};
#endif //GAME1_RESOURCEACTOR_H
