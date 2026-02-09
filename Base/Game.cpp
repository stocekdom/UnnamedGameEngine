//
// Created by dominik on 03.10.25.
//
#include "Game.h"
#include "../Src/Controllers/PlayerController.h"
#include "../Src/UI/ResourceBar.h"
#include "UI/UIRoot.h"
#include "../Src/Entities/Buildings/BuildingPlacementButton.h"
#include "../Src/Entities/Buildings/BuildingFactory.h"
#include "Logging/Logger.h"
#include <SFML/Graphics.hpp>

#include "../Src/MainGamePlayer.h"
#include "Input/UIController.h"

Game::Game()
{
   context = std::make_shared<GameContext>();
   renderer = std::make_shared<Renderer>();
}

void Game::start()
{
   constexpr int WINDOW_WIDTH = 1920;
   constexpr int WINDOW_HEIGHT = 1080;
   sf::RenderWindow window( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ), "Game" );
   auto uiView = std::make_unique<sf::View>( window.getDefaultView() );
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
      auto buildingButton = std::make_shared<BuildingPlacementButton<Buildings::BuildingType::PEASANT_HOUSE>>(
         "Assets/Icons/houseIcon.png",
         sf::Vector2f{ 60.f, 50.f } );
      auto minerButton = std::make_shared<BuildingPlacementButton<Buildings::BuildingType::STONE_MINER>>(
         "Assets/Icons/stoneMinerIco.png",
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

   auto player = context->scene->createFunctionalEntity<MainGamePlayer>();
   context->playerEntity = player->getEntityId();
   LOG_INFO( "Player entity created" );
   context->gameMapSystem->generateMap( 64, 64, sf::Vector2f{ WINDOW_WIDTH / 2 - 128, 0 } );
   LOG_INFO( "Game map generated" );
   context->gameMapSystem->onStart();
   LOG_INFO( "Game map system started" )
   context->uiSystem->onStart( window, context.get() );
   LOG_INFO( "UI system started" );
   context->inputSystem->onStart();
   LOG_INFO( "Input system started" );
   context->inventorySystem->onStart();
   LOG_INFO( "Inventory system started" );
   context->timeManager->onStart();
   LOG_INFO( "Time manager started" );
   context->transformSystem->onStart();
   LOG_INFO( "Transform system started" );
   context->spriteSystem->onStart();
   LOG_INFO( "Sprite system started" );
   context->overlaySystem->onStart();
   LOG_INFO( "Overlay system started" );
   context->tagSystem->onStart();
   LOG_INFO( "Tag system started" );
   // TODO do in a loop of user systems
   context->constructionSystem->onStart();
   LOG_INFO( "Construction system started" );
   context->scene->onStart( window );
   LOG_INFO( "Scene started" );
   LOG_INFO( "Game starting" );
   LOG_INFO( "============================================================" );

   // TODO temporary
   context->inventorySystem->addItem( player->getEntityId(), "res_wood", 5 );

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
      // Set the main scene view
      window.setView( context->scene->getSceneView() );
      context->spriteSystem->render( window, *renderer );
      context->overlaySystem->render( window, *renderer );
      // Set the UI view
      window.setView( *uiView );
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
   context->inventorySystem->init( context.get() );
   LOG_INFO( "Inventory system initialized" );
   context->inputSystem->init( context.get() );
   LOG_INFO( "Input system initialized" );
   context->gameMapSystem->init( context.get() );
   LOG_INFO( "Game map system initialized" );
   context->inputSystem->setUIController( std::make_unique<UIController>( context.get() ) );
   LOG_INFO( "UIController registered" );
   context->inputSystem->registerController( std::make_unique<PlayerController>( context.get() ) );
   LOG_INFO( "PlayerController registered" );
   context->timeManager->init( context.get() );
   LOG_INFO( "Time manager initialized" );
   context->tagSystem->init( context.get() );
   LOG_INFO( "Tag system initialized" );
   context->constructionSystem->init( context.get() );
   LOG_INFO( "Construction system initialized" );
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
