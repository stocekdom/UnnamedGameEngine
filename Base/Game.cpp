//
// Created by dominik on 03.10.25.
//
#include "Game.h"
#include "GameMap/GameMap.h"
#include "../Src/Controllers/PlayerController.h"
#include "UI/UIRoot.h"
#include "../Src/Entities/Buildings/BuildingPlacementButton.h"
#include "../Src/Entities/Buildings/BuildingFactory.h"
#include "../Src/GameItemRegistry.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game()
{
   context = std::make_shared<GameContext>();
   renderer = std::make_shared<Renderer>();
   context->resourceManager = std::make_shared<ResourceManager>();
   context->inputSystem = std::make_shared<InputSystem>();
   context->eventSystem = std::make_shared<EventSystem>();
   context->collisionSystem = std::make_shared<CollisionSystem>();
   context->scene = std::make_shared<GameScene>();
   context->gameMapSystem = std::make_shared<GameMapSystem>();
   context->uiSystem = std::make_shared<UISystem>();
   context->itemRegistry = std::make_shared<GameItemRegistry>();
}

void Game::start()
{
   const int WINDOW_WIDTH = 1920;
   const int WINDOW_HEIGHT = 1080;
   sf::RenderWindow window( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Game" );
   sf::Clock clock;
   const float FIXED_DT = 1.0f / 128.0f;
   float accumulator = 0.f;

   context->inputSystem->registerController( std::make_unique<PlayerController>( context ) );

   {
      auto uiUpperBlock = std::make_shared<UIBlock>( sf::Vector2f{ WINDOW_WIDTH, 80 }, sf::Color( 100, 10, 10, 155 ),
                                                     sf::Vector2f{ 0.f, 0.f } );
      auto uiLowerBlock = std::make_shared<UIBlock>( sf::Vector2f{ WINDOW_WIDTH, 100 }, sf::Color( 100, 10, 10 ),
                                                     sf::Vector2f{ 0.f, ( float )window.getSize().y - 100.f } );
      auto menuButton = std::make_shared<UIButton<GamePaused>>( "Assets/Icons/menu.png",
                                                                sf::Vector2f{ WINDOW_WIDTH - 60.f, 40.f } );

      auto buildingButton = std::make_shared<BuildingPlacementButton<BuildingType::PEASANT_HOUSE>>( "Assets/Icons/houseIcon.png",
                                                                                                    sf::Vector2f{ 60.f, 50.f } );

      auto uiText = std::make_shared<UIElementText>( "Assets/TheGoldBachelor.ttf", "Info bar", 24, sf::Color::White,
                                                     sf::Vector2f{ 10.f, 10.f } );

      auto placeholderMenu = std::make_shared<UIButton<GameResumed>>( "Assets/Icons/menu.png",
                                                                      sf::Vector2f{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, 0,
                                                                      sf::Vector2f{ 5.f, 5.f } );
      auto uiRoot = std::make_shared<UIRoot>( placeholderMenu );
      uiUpperBlock->addChild( uiText );
      uiUpperBlock->addChild( menuButton );
      uiLowerBlock->addChild( buildingButton );

      uiRoot->addChild( uiLowerBlock );
      uiRoot->addChild( uiUpperBlock );
      context->uiSystem->addUiRootComponent( uiRoot );
   }

   context->gameMapSystem->generateMap( 6, 6, sf::Vector2f{ WINDOW_WIDTH / 2 - 128, 0 } );
   context->gameMapSystem->onStart( context.get() );
   context->uiSystem->onStart( window, context.get() );
   context->scene->onStart( window );

   std::cout << "\033[92m[INFO]: Game starting!" << "\033[0m" << std::endl;
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

      context->inputSystem->update( frameTime );
      context->scene->update( frameTime );
      window.clear();
      context->scene->renderScene( window, *renderer );
      context->uiSystem->renderUI( window, *renderer );
      window.display();
   }

   std::cout << "\033[96m[INFO]: Game ending!" << "\033[0m" << std::endl;
}

