//
// Created by dominik on 03.10.25.
//
#include "Renderer.h"
#include <SFML/Graphics/RenderTarget.hpp>

void Renderer::render( const sf::Drawable& drawable, sf::RenderTarget& target ) const
{
   target.draw( drawable );
}
