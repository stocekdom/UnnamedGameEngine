//
// Created by dominik on 03.10.25.
//
#include "Game.h"
#include "Collision/ColliderRect.h"
#include "Entity/IsometricActor.h"
#include <SFML/Graphics.hpp>

void Game::start()
{
   const int WINDOW_WIDTH = 1920;
   const int WINDOW_HEIGHT = 1080;
   sf::RenderWindow window( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Game" );
   sf::Clock clock;
   const float FIXED_DT = 1.0f / 128.0f;
   float accumulator = 0.f;

   auto tile1 = std::make_shared<IsometricActor>( textureManager, "Assets/grass1.png", sf::Vector2f{ 128, 128 } );
   tile1->setHeight( 16 );
   tile1->init( scene, collisionSystem );
   // only temporary test. Position must be calculated more consistently
   auto tile2 = std::make_shared<IsometricActor>( textureManager, "Assets/grass1.png", sf::Vector2f{ 256, 192 } );
   tile2->init( scene, collisionSystem );
   auto tile3 = std::make_shared<IsometricActor>( textureManager, "Assets/grass1.png", sf::Vector2f{ 0, 192 } );
   tile3->init( scene, collisionSystem );

   // Main loop
   while( window.isOpen() )
   {
      auto frameTime = clock.restart().asSeconds();
      accumulator += frameTime;

      sf::Event event;
      while( window.pollEvent( event ) )
      {
         if( event.type == sf::Event::Closed )
            window.close();

         scene.handleInput( event );
      }

      while( accumulator >= FIXED_DT )
      {
         scene.updateFixed( FIXED_DT );
         collisionSystem.update( FIXED_DT );
         accumulator -= FIXED_DT;
      }

      scene.update( frameTime );
      window.clear();
      renderer.render( scene, window );
      window.display();
   }
}

