//
// Created by dominik on 03.10.25.
//
#include "Game.h"
#include "../Entities/GameMap.h"
#include "../Controllers/PlayerController.h"
#include "UI/UIBlock.h"
#include "UI/UIButton.h"
#include "../Entities/ClickableText.h"
#include "Event/Events.h"
#include "UI/UIRoot.h"
#include <SFML/Graphics.hpp>

Game::Game()
{
   context = std::make_shared<GameContext>();
   renderer = std::make_shared<Renderer>();
   context->textureManager = std::make_shared<TextureManager>();
   context->inputSystem = std::make_shared<InputSystem>();
   context->eventSystem = std::make_shared<EventSystem>();
   context->collisionSystem = std::make_shared<CollisionSystem>();
   context->scene = std::make_shared<GameScene>();
}

void Game::start()
{
   const int WINDOW_WIDTH = 1920;
   const int WINDOW_HEIGHT = 1080;
   sf::RenderWindow window( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Game" );
   sf::Clock clock;
   const float FIXED_DT = 1.0f / 128.0f;
   float accumulator = 0.f;

   context->inputSystem->registerController( std::make_unique<PlayerController>( context->scene ) );

   {
      auto building = std::make_shared<IsometricActor>( Mobility::STATIC, sf::Vector2f{ 1024, 256 }, 0,
                                                        sf::Vector2f{ 0.25f, 0.25f } );
      // TODO Call on start from scene
      building->onStart( context );
   }

   {
      auto map = std::make_shared<GameMap>( 6, 6, sf::Vector2f{ WINDOW_WIDTH / 2 - 128, 0 } );
      map->init( context );
   }

   {
      auto uiUpperBlock = std::make_shared<UIBlock>( sf::Vector2f{ WINDOW_WIDTH, 80 }, sf::Color( 100, 10, 10 ),
                                                     sf::Vector2f{ 0.f, 0.f } );
      auto uiLowerBlock = std::make_shared<UIBlock>( sf::Vector2f{ WINDOW_WIDTH, 100 }, sf::Color( 100, 10, 10 ),
                                                     sf::Vector2f{ 0.f, ( float )window.getSize().y - 100.f } );
      auto text = std::make_shared<ClickableText>( "Assets/TheGoldBachelor.ttf", "Clickable text is: ", 24, sf::Color::White,
                                                   sf::Vector2f{ 10.f, ( float )window.getSize().y - 70.f } );
      auto menuButton = std::make_shared<UIButton<GamePaused>>( "Assets/menu.png", sf::Vector2f{ WINDOW_WIDTH - 60.f, 40.f } );

      auto uiText = std::make_shared<UIElementText>( "Assets/TheGoldBachelor.ttf", "Info bar", 24, sf::Color::White,
                                                     sf::Vector2f{ 10.f, 10.f } );

      auto placeholderMenu = std::make_shared<UIButton<GameResumed>>( "Assets/menu.png", sf::Vector2f{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, 0, sf::Vector2f{ 5.f, 5.f } );
      auto uiRoot = std::make_shared<UIRoot>( placeholderMenu );
      uiUpperBlock->addChild( uiText );
      uiUpperBlock->addChild( menuButton );
      uiLowerBlock->addChild( text );

      uiRoot->addChild( uiLowerBlock );
      uiRoot->addChild( uiUpperBlock );
      context->scene->addUIRootComponent( uiRoot );
   }

   context->scene->onStart( window, context );

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

         context->inputSystem->handleInput( event );
      }

      while( accumulator >= FIXED_DT )
      {
         context->scene->updateFixed( FIXED_DT );
         context->collisionSystem->update( FIXED_DT );
         accumulator -= FIXED_DT;
      }

      context->scene->update( frameTime );
      window.clear();
      context->scene->renderScene( window, *renderer );
      window.display();
   }
}

