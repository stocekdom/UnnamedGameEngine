//
// Created by dominik on 03.10.25.
//
#include "Game.h"
#include "GameMap/GameMap.h"
#include "../Src/Controllers/PlayerController.h"
#include "../Src/UI/ResourceBar.h"
#include "Data/PlayerInventoryComponent.h"
#include "UI/UIRoot.h"
#include "../Src/Entities/Buildings/BuildingPlacementButton.h"
#include "../Src/Entities/Buildings/BuildingFactory.h"
#include "../Src/GameItemRegistry.h"
#include "Logging/Logger.h"
#include <SFML/Graphics.hpp>

Game::Game()
{
   context = std::make_shared<GameContext>();
   renderer = std::make_shared<Renderer>();
   context->player = std::make_shared<PlayerInventoryComponent>();
   context->resourceManager = std::make_shared<ResourceManager>();
   context->spriteSystem = std::make_shared<SpriteSystem>();
   context->overlaySystem = std::make_shared<OverlaySystem>();
   context->transformSystem = std::make_shared<TransformSystem>();
   context->inputSystem = std::make_shared<InputSystem>();
   context->eventSystem = std::make_shared<EventSystem>();
   //context->collisionSystem = std::make_shared<CollisionSystem>();
   context->scene = std::make_shared<GameScene>();
   context->gameMapSystem = std::make_shared<GameMapSystem>();
   context->uiSystem = std::make_shared<UISystem>();
   context->itemRegistry = std::make_shared<GameItemRegistry>();
   context->timeManager = std::make_shared<TimeManager>();
}

void Game::start()
{
   constexpr int WINDOW_WIDTH = 1920;
   constexpr int WINDOW_HEIGHT = 1080;
   sf::RenderWindow window( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Game" );
   sf::Clock clock;
   constexpr float FIXED_DT = 1.0f / 128.0f;
   float accumulator = 0.f;

   initSystems();

   // TODO add level classes and load them
   {
      auto uiUpperBlock = std::make_shared<ResourceBar>( sf::Vector2f{ WINDOW_WIDTH, 80 }, sf::Color( 100, 10, 10, 155 ),
                                                         sf::Vector2f{ 0.f, 0.f } );
      auto uiLowerBlock = std::make_shared<UIBlock>( sf::Vector2f{ WINDOW_WIDTH, 100 }, sf::Color( 100, 10, 10 ),
                                                     sf::Vector2f{ 0.f, static_cast<float>( window.getSize().y ) - 100.f } );
      auto menuButton = std::make_shared<UIButton<GamePaused>>( "Assets/Icons/menu.png",
                                                                sf::Vector2f{ WINDOW_WIDTH - 60.f, 40.f } );

      // TODO add a separate component for building buttons
      auto buildingButton = std::make_shared<BuildingPlacementButton<BuildingType::PEASANT_HOUSE>>( "Assets/Icons/houseIcon.png",
         sf::Vector2f{ 60.f, 50.f } );
      auto minerButton = std::make_shared<BuildingPlacementButton<BuildingType::STONE_MINER>>( "Assets/Icons/stoneMinerIco.png",
         sf::Vector2f{ 134.f, 50.f } );

      auto placeholderMenu = std::make_shared<UIButton<GameResumed>>( "Assets/Icons/menu.png",
                                                                      sf::Vector2f{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, 0,
                                                                      sf::Vector2f{ 5.f, 5.f } );
      auto uiRoot = std::make_shared<UIRoot>( placeholderMenu );
      uiUpperBlock->addChild( menuButton );
      uiLowerBlock->addChild( buildingButton );
      uiLowerBlock->addChild( minerButton );

      uiRoot->addChild( uiLowerBlock );
      uiRoot->addChild( uiUpperBlock );
      context->uiSystem->addUiRootComponent( uiRoot );
   }

   context->gameMapSystem->generateMap( 6, 6, sf::Vector2f{ WINDOW_WIDTH / 2 - 128, 0 } );
   LOG_INFO( "Game map generated" );
   context->gameMapSystem->onStart( context.get() );
   LOG_INFO( "Game map system started" )
   context->uiSystem->onStart( window, context.get() );
   LOG_INFO( "UI system started" );
   context->player->onStart( context.get() );
   LOG_INFO( "Player class started" );
   context->transformSystem->onStart();
   LOG_INFO( "Transform system started" );
   context->spriteSystem->onStart();
   LOG_INFO( "Sprite system started" );
   context->overlaySystem->onStart();
   LOG_INFO( "Overlay system started" );
   context->scene->onStart( window );
   LOG_INFO( "Scene started" );
   LOG_INFO( "Game starting" );
   LOG_INFO( "============================================================" );

   // TODO temporary
   context->player->addItem( "res_wood", 20 );
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
         updateSystems( FIXED_DT );
         accumulator -= FIXED_DT;
      }

      context->inputSystem->update( frameTime );
      window.clear();
      // Rendering -------------------------------------------------
      context->spriteSystem->render( window, *renderer );
      context->overlaySystem->render( window, *renderer );
      context->uiSystem->render( window, *renderer );
      // -----------------------------------------------------------
      window.display();
   }

   LOG_INFO( "Game ending!" );
}

void Game::initSystems() const
{
   LOG_INFO( "============================================================" );
   LOG_INFO( "Initializing systems" );
   context->scene->init( context.get() );
   LOG_INFO( "Scene initialized" );
   context->transformSystem->init( context.get() );
   LOG_INFO( "Transform system initialized" );
   context->spriteSystem->init( context.get() );
   LOG_INFO( "Sprite system initialized" );
   context->overlaySystem->init( context.get() );
   LOG_INFO( "Overlay system initialized" );
   context->inputSystem->registerController( std::make_unique<PlayerController>( context ) );
   LOG_INFO( "PlayerController registered" );
   LOG_INFO( "All systems initialized" );
   LOG_INFO( "============================================================" );

}

void Game::updateSystems( float dt ) const
{
   // IMPORTANT always update the transform system first
   context->transformSystem->update( dt );
   context->timeManager->update( dt );
   context->scene->updateFixed( dt );
   context->spriteSystem->update( dt );
   context->overlaySystem->update( dt );
}
