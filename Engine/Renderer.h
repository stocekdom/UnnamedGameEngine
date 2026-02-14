//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_RENDERER_H
#define GAME1_RENDERER_H

#include <SFML/Graphics/RenderTarget.hpp>

class Renderer
{
   public:
      void render( const sf::Drawable& drawable, sf::RenderTarget& target ) const;
};

#endif //GAME1_RENDERER_H
