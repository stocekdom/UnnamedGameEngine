//
// Created by dominik on 08.12.25.
//

#ifndef GAME1_PLAYERINVENTORYCOMPONENT_H
#define GAME1_PLAYERINVENTORYCOMPONENT_H

#include "InventoryComponent.h"

/**
 * Specialized InventoryComponent for player inventory which fires events when items are added or removed
 */
class PlayerInventoryComponent : public InventoryComponent
{
   public:
      bool addItem( const std::string& id, unsigned int amount ) override;

      unsigned int removeItem( const std::string& id, unsigned int amount ) override;
};

#endif //GAME1_PLAYERINVENTORYCOMPONENT_H
