//
// Created by dominik on 03.12.25.
//

#include "Building.h"

Building::Building( SpawnCategory spawnCategory, const sf::Vector2f& position, float rotation, const sf::Vector2f& scale,
                    float height, bool isVisible )
      : IsometricActor( spawnCategory, Mobility::STATIC, position, rotation, scale, height, isVisible )
{
}

void Building::onStart( std::shared_ptr<GameContext>& context )
{
   // Ensures all building have the same pivot point.
   sprite.setOrigin( sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height );
   IsometricActor::onStart( context );
}

