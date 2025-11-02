//
// Created by dominik on 03.10.25.
//
#include "Game.h"
#include "Entity/Actor.h"
#include "Collision/ColliderRect.h"
#include "../Entities/Bow.h"
#include "../Controllers/BowController.h"
#include "../Entities/Target.h"
#include "../Entities/Scoreboard.h"
#include "Observers/UpdateScoreboardObserver.h"
#include <SFML/Graphics.hpp>

void Game::start()
{
   const int WINDOW_WIDTH = 1920;
   const int WINDOW_HEIGHT = 1080;
   sf::RenderWindow window( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Game" );
   sf::Clock clock;
   const float FIXED_DT = 1.0f / 128.0f;
   float accumulator = 0.f;

   // TODO move these to factories
   // Add background
   {
      auto background = std::make_shared<Actor>( "Assets/origbig.png", sf::Vector2f( 0, -200 ) );
      background->init( scene, collisionSystem );
   }

   // Add bow
   {
      auto bow = std::make_shared<Bow>( "Assets/bow.png", sf::Vector2f( 30, ( float )WINDOW_HEIGHT / 2 ), 0, sf::Vector2f( 0.12, 0.12 ) );
      bow->init( scene, collisionSystem );
      scene.addController( std::make_unique<BowController>( bow ) );
   }

   // Add target, Scoreboard and observer
   {
      auto scoreboard = std::make_shared<Scoreboard>( "Assets/TTT-Regular.otf", "", 40, sf::Color::Black, sf::Vector2f( 15, 15 ) );
      scoreboard->init( scene, collisionSystem );

      auto target = std::make_shared<Target>( "Assets/target.png" );
      target->init( scene, collisionSystem );
      target->randomize();
      auto observer = std::make_shared<UpdateScoreboardObserver>( scoreboard );
      scene.addObserver( observer );
      target->addObserver( observer );
   }

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

