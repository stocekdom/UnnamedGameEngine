//
// Created by dominik on 03.10.25.
//
#include "Game.h"
#include "Collision/ColliderRect.h"
#include "Entity/IsometricActor.h"
#include "../Controllers/PlayerController.h"
#include "UI/UIBlock.h"
#include <SFML/Graphics.hpp>

void Game::start()
{
   const int WINDOW_WIDTH = 1920;
   const int WINDOW_HEIGHT = 1080;
   sf::RenderWindow window( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Game" );
   sf::Clock clock;
   const float FIXED_DT = 1.0f / 128.0f;
   float accumulator = 0.f;

   inputSystem.registerController( std::make_unique<PlayerController>( scene ) );
   /*
   auto tile1 = std::make_shared<IsometricActor>( textureManager, "Assets/grass1.png", sf::Vector2f{ 128, 128 } );
   tile1->setHeight( 16 );
   tile1->init( scene, collisionSystem );
   // only temporary test. Position must be calculated more consistently
   auto tile2 = std::make_shared<IsometricActor>( textureManager, "Assets/grass1.png", sf::Vector2f{ 256, 192 } );
   tile2->init( scene, collisionSystem );
   auto tile3 = std::make_shared<IsometricActor>( textureManager, "Assets/grass1.png", sf::Vector2f{ 0, 192 } );
   tile3->init( scene, collisionSystem );
   auto tile4 = std::make_shared<IsometricActor>( textureManager, "Assets/grass1.png", sf::Vector2f{ 128, 256 } );
   tile4->onStart( scene, collisionSystem );
*/

   {
      auto building = std::make_shared<IsometricActor>( textureManager, "Assets/gov_center.png", Mobility::STATIC,
                                                        sf::Vector2f{ 1024, 256 }, 0, sf::Vector2f{ 0.25f, 0.25f } );
      building->onStart( scene, collisionSystem );
   }

   {
      auto map = std::make_shared<GameMap>( textureManager, 6, 6, sf::Vector2f{ WINDOW_WIDTH / 2 - 128, 0 } );
      map->init( scene, collisionSystem );
   }

   {
      auto uiRoot = std::make_shared<UIBlock>( sf::Vector2f{ WINDOW_WIDTH, 100 }, sf::Color( 100, 10, 10 ),
                                               sf::Vector2f{ 0.f, ( float )window.getSize().y - 100.f } );
      auto text = std::make_shared<ClickableText>( "Assets/TheGoldBachelor.ttf", "Clickable text is: ", 24, sf::Color::White,
                                                   sf::Vector2f{ 10.f, ( float )window.getSize().y - 70.f } );

      uiRoot->addChild( text );
      scene.addUIRootComponent( uiRoot );
   }

   scene.init( window );

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

         inputSystem.handleInput( event );
      }

      while( accumulator >= FIXED_DT )
      {
         scene.updateFixed( FIXED_DT );
         collisionSystem.update( FIXED_DT );
         accumulator -= FIXED_DT;
      }

      scene.update( frameTime );
      window.clear();
      scene.renderScene( window, renderer );
      window.display();
   }
}

