//
// Created by dominik on 31.10.25.
//
#include "Entity.h"

void Entity::onStart( GameContext* context )
{
   for( auto& child: children )
      if( auto c = child.lock() )
         c->onStart( context );
}

std::weak_ptr<Entity> Entity::getParent()
{
   return parent;
}

void Entity::setParent( const std::shared_ptr<Entity>& entity )
{
   parent = entity;
}

bool Entity::isDirty() const
{
   return isEntityDirty;
}

void Entity::setDirty()
{
   isEntityDirty = true;

   for( auto& child: children )
   {
      if( auto c = child.lock() )
         c->setDirty();
   }
}

void Entity::addChild( const std::shared_ptr<Entity>& child )
{
   children.push_back( child );
   child->setParent( shared_from_this() );
}

UUID Entity::getId() const
{
   return id;
}
