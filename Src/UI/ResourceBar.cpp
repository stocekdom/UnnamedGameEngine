//
// Created by dominik on 08.12.25.
//
#include "ResourceBar.h"
#include "../GameItems.h"

ResourceBar::ResourceBar( const sf::Vector2f& extents, const sf::Color& fillColor, const sf::Vector2f& position, float rotation,
                          bool isVisible )
   : UIBlock( extents, fillColor, position, rotation, isVisible )
{
   //if( extents.x < 400.f )
   // TODO log - value too small icons might be wrong
}

void ResourceBar::onStart( GameContext* context )
{
   for( int i = 0; i < Utility::enumToIndex( Resources::Resource::ITEM_COUNT ); ++i )
   {
      // Left padding + (padding between counters * index) + half of the counter's width to get the center * ( index + 1 )
      float buttonX = X_PADDING + ( COUNTER_WIDTH / 2 ) +
                      ( INNER_PADDING * static_cast<float>( i ) + COUNTER_WIDTH * static_cast<float>( i ) );
      // Add a counter for each resource. Calculate position to account for the centered pivotal point
      auto counter = std::make_shared<ResourceCounter>( Resources::ResourceManager::getResourceId( i ), COUNTER_WIDTH,
                                                        sf::Vector2f{ buttonX, block.getLocalBounds().height / 2.f - 5.f } );

      counters.push_back( counter );
      addChild( counter );
   }

   // Register events for removing and adding items to player inventory
   context->eventSystem->subscribe<PlayerInventoryItemAdded>(
      [this]( const PlayerInventoryItemAdded& data ) { onResourceAdd( data ); } );
   context->eventSystem->subscribe<PlayerInventoryItemRemoved>(
      [this]( const PlayerInventoryItemRemoved& data ) { onResourceRemove( data ); } );

   UIBlock::onStart( context );
}

void ResourceBar::onResourceAdd( const PlayerInventoryItemAdded& data ) const
{
   counterUpdateImpl( data.itemId, data.currentAmount );
}

void ResourceBar::onResourceRemove( const PlayerInventoryItemRemoved& data ) const
{
   counterUpdateImpl( data.itemId, data.currentAmount );
}

void ResourceBar::counterUpdateImpl( const std::string& id, unsigned int amount ) const
{
   for( auto& counter: counters )
      if( counter->getCountedItemId() == id )
         counter->updateCounterAmount( amount );
}
