//
// Created by dominik on 03.10.25.
//
#include "Renderer.h"
#include "Scene.h"
#include <SFML/Graphics/RenderTarget.hpp>

void Renderer::render( GameScene& scene, sf::RenderTarget& target )
{
   // TODO this is trash. We need a tree structure based on depth and render from it
   for( const auto& actor: scene.getStaticEntities() )
   {
      if( actor->isVisible() )
         target.draw( actor->getDrawable() );
   }
}
