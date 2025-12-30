//
// Created by dominik on 20.12.25.
//

#ifndef GAME1_COMPONENTCONTAINER_H
#define GAME1_COMPONENTCONTAINER_H

#include <algorithm>

#include "Entity.h"
#include "Logging/Logger.h"
#include <unordered_map>
#include <functional>
#include <numeric>
#include <ranges>
#include <vector>

class IComponentContainer
{
   public:
      virtual ~IComponentContainer() = default;

      virtual void onEntityDestroyed( Entity entity ) = 0;
};

/**
 * Main container class for containing components of the same type
 * Stores components continuous storage and provides fast ID lookups
 * @tparam TC The components type
 */
template<typename TC>
class ComponentContainer : public IComponentContainer
{
   public:
      bool addComponent( Entity id, TC component );

      template<typename... Args>
      bool addComponent( Entity id, Args&&... args );

      bool removeComponent( Entity entity );

      void onEntityDestroyed( Entity entity ) override;

      TC& getComponent( Entity id );

      bool hasComponent( Entity entity ) const;

      template<typename Compare>
      void sort( Compare comp );

      // Expose iterators ===========================================

      auto begin() { return components.begin(); }
      auto end() { return components.end(); }

      // Const iterator support
      auto begin() const { return components.begin(); }
      auto end() const { return components.end(); }

      auto cbegin() const { return components.cbegin(); }
      auto cend() const { return components.cend(); }

   private:
      std::vector<TC> components;
      std::unordered_map<Entity, size_t> entityToIndex;
      std::unordered_map<size_t, Entity> indexToEntity;

      bool addComponentIndexHandler( Entity id );
};

template<typename TC>
bool ComponentContainer<TC>::addComponent( const Entity id, TC component )
{
   auto res = addComponentIndexHandler( id );

   if( res )
      components.push_back( std::move( component ) );

   return res;
}

template<typename TC>
template<typename... Args>
bool ComponentContainer<TC>::addComponent( const Entity id, Args&&... args )
{
   // TODO no strong exception quarantee
   auto res = addComponentIndexHandler( id );

   if( res )
      components.emplace_back( std::forward<Args>( args )... );

   return res;
}

template<typename TC>
bool ComponentContainer<TC>::removeComponent( const Entity entity )
{
   if( !entityToIndex.contains( entity ) )
   {
      LOG_INFO( "Cannot remove component of entity: " + std::to_string( entity ) + ". Component doesn't exist" );
      return false;
   }

   auto index = entityToIndex[ entity ];
   // Swap and pop
   std::swap( components[ index ], components.back() );
   // Erase index of current entity and erase the last index from maps
   entityToIndex.erase( entity );
   indexToEntity.erase( components.size() - 1 );

   auto lastEntity = indexToEntity[ components.size() - 1 ];
   entityToIndex[ lastEntity ] = index;
   indexToEntity[ index ] = lastEntity;
   components.pop_back();
   return true;
}

template<typename TC>
void ComponentContainer<TC>::onEntityDestroyed( const Entity entity )
{
   if( entityToIndex.contains( entity ) )
      removeComponent( entity );
}

template<typename TC>
TC& ComponentContainer<TC>::getComponent( const Entity id )
{
   if( !entityToIndex.contains( id ) )
      LOG_ERROR( "Entity: " + std::to_string( id ) + " does not have a component of type " + std::string( typeid( TC ).name() ) );

   return components[ entityToIndex[ id ] ];
}

template<typename TC>
bool ComponentContainer<TC>::hasComponent( Entity entity ) const
{
   return entityToIndex.contains( entity );
}

template<typename TC>
template<typename Compare>
void ComponentContainer<TC>::sort( Compare comp )
{
   // Initialize the vector of indices with the proper size.
   // Since TC doesn't have info about its entity, we need to sort indices and swap elements to properly sort the packed array
   std::vector<size_t> indices( components.size() );
   // Fill the vector with current indices [0, 1, 2...]
   std::iota( indices.begin(), indices.end(), 0 );

   // Sort the indices by comparing their components
   std::ranges::sort( indices.begin(), indices.end(), [&]( size_t a, size_t b ) {
      return comp( components[ a ], components[ b ] );
   } );

   // Shuffle, according to the sorted indices
   for( int i = 0; i < indices.size(); ++i )
   {
      Entity entityAtTarget = indexToEntity[ i ];
      Entity entityAtSource = indexToEntity[ indices[ i ] ];

      std::swap( components[ i ], components[ indices[ i ] ] );
      // Update maps
      entityToIndex[ entityAtSource ] = i;
      entityToIndex[ entityAtTarget ] = indices[ i ];
      indexToEntity[ i ] = entityAtSource;
      indexToEntity[ indices[ i ] ] = entityAtTarget;

      for( size_t j = i + 1; j < indices.size(); ++j )
      {
         if( indices[ j ] == i )
         {
            indices[ j ] = indices[ i ];
            break;
         }
      }
   }
}

template<typename TC>
bool ComponentContainer<TC>::addComponentIndexHandler( Entity id )
{
   if( entityToIndex.contains( id ) )
   {
      LOG_WARNING( "Entity: " + std::to_string( id ) + " already has a component of type " + std::string( typeid( TC ).name() ) );
      return false;
   }

   auto newIndex = components.size();
   entityToIndex[ id ] = newIndex;
   indexToEntity[ newIndex ] = id;
   return true;
}

#endif //GAME1_COMPONENTCONTAINER_H
