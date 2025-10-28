//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_RENDERER_H
#define GAME1_RENDERER_H

#include "Scene.h"
#include <SFML/Graphics/RenderTarget.hpp>

class Renderer
{
   public:
      void render( GameScene& scene, sf::RenderTarget& target );

   private:
};

#endif //GAME1_RENDERER_H
