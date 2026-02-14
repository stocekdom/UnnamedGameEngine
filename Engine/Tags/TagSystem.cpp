//
// Created by dominik on 06.02.26.
//

#include "TagSystem.h"

#include "Tags.h"
#include "../GameContext.h"

void TagSystem::init( GameContext* context )
{
   context->scene->getComponentRegistry().registerComponentType<PlayerTag>();
   context->scene->getComponentRegistry().registerComponentType<BuildingTag>();
}

void TagSystem::onStart()
{
}

void TagSystem::update( float dt )
{
}

void TagSystem::onBeforeComponentsDestroyed( Entity entity )
{
}

void TagSystem::onComponentAdded( Entity entity )
{
}
