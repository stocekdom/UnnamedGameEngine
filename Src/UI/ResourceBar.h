//
// Created by dominik on 08.12.25.
//

#ifndef GAME1_RESOURCEBAR_H
#define GAME1_RESOURCEBAR_H

#include "../../Base/Data/ItemEvents.h"
#include "../../Base/UI/UIBlock.h"
#include "ResourceCounter.h"

class ResourceBar : public UIBlock
{
   public:
      ResourceBar( const sf::Vector2f& extents, const sf::Color& fillColor, const sf::Vector2f& position, float rotation = 0,
                   bool isVisible = true );

      void onStart( GameContext* context ) override;

   private:
      const float INNER_PADDING = 10.f;
      static constexpr float COUNTER_WIDTH = 48.f;
      static constexpr float X_PADDING = 64.f;
      std::vector<std::shared_ptr<ResourceCounter>> counters;

      void onResourceAdd( const PlayerInventoryItemAdded& data ) const;

      void onResourceRemove( const PlayerInventoryItemRemoved& data ) const;

      void counterUpdateImpl( const std::string& id, unsigned int amount ) const;
};

#endif //GAME1_RESOURCEBAR_H
