//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_RENDERER_H
#define GAME1_RENDERER_H

#include <SFML/Graphics/RenderTarget.hpp>

class Renderer
{
   public:
      inline void render( const sf::Drawable& drawable, sf::RenderTarget& target ) const;

   private:
};

#endif //GAME1_RENDERER_H
