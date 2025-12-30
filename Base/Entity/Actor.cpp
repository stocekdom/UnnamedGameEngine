//
// Created by dominik on 03.10.25.
//
#include "Actor.h"

#include "../Scene.h"
#include "../Transform/TransformComponent.h"

Actor::Actor( Entity id, GameScene* scene, const ActorParams& params )
   : FunctionalEntity( id, scene )
{
   scene->addComponent<TransformComponent>( id, params.position, params.rotation, params.scale );
}

void Actor::onStart( GameContext* context )
{
}

void Actor::tick( float deltaTime )
{
}
