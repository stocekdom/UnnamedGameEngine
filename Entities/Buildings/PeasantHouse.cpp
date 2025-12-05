//
// Created by dominik on 03.12.25.
//
#include "../../Base/Entity/IsometricActor.h"
#include "PeasantHouse.h"

PeasantHouse::PeasantHouse( SpawnCategory spawnCategory, const sf::Vector2f& position, float rotation, const sf::Vector2f& scale,
                            float height, bool isVisible )
      : Building( spawnCategory, position, rotation, scale, height, isVisible )
{
}

void PeasantHouse::onStart( GameContext* context )
{
   // TODO add random variants
   sprite.setTexture( context->textureManager->loadTexture( "Assets/Buildings/house1.png" ) );
   Building::onStart( context );
}
