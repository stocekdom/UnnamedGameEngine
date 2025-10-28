//
// Created by dominik on 03.10.25.
//
#include "Renderer.h"
#include "Scene.h"
#include <SFML/Graphics/RenderTarget.hpp>

void Renderer::render( GameScene& scene, sf::RenderTarget& target )
{
   for( const auto& actor: scene.getActors() )
   {
      if( actor->isVisible() )
         target.draw( actor->getDrawable() );
   }

   for( const auto& tickableActor: scene.getTickableActors() )
   {
      if( tickableActor->isVisible() )
         target.draw( tickableActor->getDrawable() );
   }
}
