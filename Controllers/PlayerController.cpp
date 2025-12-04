//
// Created by dominik on 15.11.25.
//
#include "PlayerController.h"
#include "../Base/Core/Math.h"
#include "../Entities/MapTile.h"
#include "../Base/Input/ContextFactory.h"
#include "../Entities/Buildings/BuildingFactory.h"

// We initialize everything in the constructor since systems are already created at this point, and we don't need onStart
PlayerController::PlayerController( const std::shared_ptr<GameContext>& context ) : context( context ),
                                                                                    cameraSpeed( 0.f, 0.f )
{
   context->eventSystem->subscribe<GamePaused>( [this]( const GamePaused& event ) { onPauseGame( event ); } );
   context->eventSystem->subscribe<GameResumed>( [this]( const GameResumed& event ) { onResumeGame( event ); } );
   context->eventSystem->subscribe<BuildingPlacingStarted>(
         [this]( const BuildingPlacingStarted& event ) { onBuildingPlacingStart( event ); } );
   menuContext = ContextFactory::createMenuContext();
   mainContext = ContextFactory::createGameContext();
   placingContext = ContextFactory::createBuildingPlacingContext();
   activeContext = mainContext;
   actions[ GameAction::LEFT_CLICK ] = [this]( const ActionData& event ) { onLeftClick( event ); };
   actions[ GameAction::CAMERA_MOVE_RIGHT ] = [this]( const ActionData& event ) { updateCameraSpeedX( event.value ); };
   actions[ GameAction::CAMERA_MOVE_LEFT ] = [this]( const ActionData& event ) { updateCameraSpeedX( -event.value ); };
   actions[ GameAction::CAMERA_MOVE_UP ] = [this]( const ActionData& event ) { updateCameraSpeedY( -event.value ); };
   actions[ GameAction::CAMERA_MOVE_DOWN ] = [this]( const ActionData& event ) { updateCameraSpeedY( event.value ); };
   actions[ GameAction::CAMERA_ZOOM ] = [this]( const ActionData& event ) { updateCameraZoom( event.value ); };
   actions[ GameAction::MOUSE_MOVE ] = [this]( const ActionData& event ) { onMouseMove( event.position ); };
   actions[ GameAction::PLACEMENT_CANCEL ] = [this]( const ActionData& event ) { onBuildingPlacingCancel(); };
   actions[ GameAction::PLACE_BUILDING ] = [this]( const ActionData& event ) { onBuildingPlaced( event.position ); };
}

void PlayerController::tick( float dt )
{
   auto sharedContext = context.lock();

   // TODO Throw instead??
   if( !sharedContext )
      return;

   if( cameraSpeed.x != 0.f || cameraSpeed.y != 0.f )
      sharedContext->scene->moveCamera( cameraSpeed * CAMERA_SPEED * dt );

   if( targetZoom != currentZoom )
   {
      float prevZoom = currentZoom;
      float delta = targetZoom - currentZoom;
      float change = dt * ZOOM_PER_SECOND;

      if( delta < 0 )
         currentZoom = std::max( targetZoom, currentZoom - change );
      else
         currentZoom = std::min( targetZoom, currentZoom + change );

      sharedContext->scene->zoomCamera( currentZoom / prevZoom );
   }
}

void PlayerController::onLeftClick( const ActionData& event )
{
   if( auto sharedContext = context.lock() )
      sharedContext->scene->onLeftClick( event.position );
}

void PlayerController::onPauseGame( const GamePaused& event )
{
   activeContext = menuContext;
}

void PlayerController::onResumeGame( const GameResumed& event )
{
   activeContext = mainContext;
}

// TODO switch to ECS to make this cleaner
void PlayerController::onBuildingPlacingStart( const BuildingPlacingStarted& event )
{
   // TODO properly handle left click on UI even in this context
   activeContext = placingContext;

   if( auto sharedContext = context.lock() )
   {
      auto building = BuildingFactory::createBuilding( event.type, event.position );
      // TODO temporary hack to make the ghost house movable
      building->setMobility( Mobility::MOVABLE );
      building->onStart( sharedContext );
      buildingPawn = building;
   }
}

void PlayerController::onBuildingPlacingCancel()
{
   auto sharedContext = context.lock();
   auto sharedPawn = buildingPawn.lock();

   if( !sharedPawn || !sharedContext )
      return;

   sharedContext->scene->deleteOverlayEntityById( sharedPawn->getId() );
   buildingPawn.reset();
}

void PlayerController::onBuildingPlaced( const sf::Vector2i& position )
{
   auto sharedContext = context.lock();
   auto sharedPawn = buildingPawn.lock();

   if( !sharedPawn || !sharedContext )
      return;

   // The position of the click should be enough, since in mouse move, we're snapping the house to the map tile
   auto tile = sharedContext->scene->getMapTile( position );

   auto sharedTile = tile.lock();

   if( !sharedTile )
      return;

   // TODO this shouldn't be done here. Switch to ECS
   sharedContext->scene->deleteOverlayEntityById( sharedPawn->getId() );
   sharedPawn->setSpawnCategory( SpawnCategory::WORLD );
   sharedPawn->setMobility( Mobility::STATIC );
   sharedContext->scene->addEntityToScene( sharedPawn );
   sharedTile->setBuilding( sharedPawn );

   buildingPawn.reset();
   activeContext = mainContext;
}

void PlayerController::updateCameraSpeedX( float x )
{
   cameraSpeed.x = x;
   cameraSpeed = Math::normalize( cameraSpeed );
}

void PlayerController::updateCameraSpeedY( float y )
{
   cameraSpeed.y = y;
   cameraSpeed = Math::normalize( cameraSpeed );
}

void PlayerController::updateCameraZoom( float zoom )
{
   if( zoom > 0.f )
      targetZoom *= ( 1.f - ZOOM_STEP ); // Zoom in
   else
      targetZoom *= ( 1.f + ZOOM_STEP ); // Zoom out

   targetZoom = std::clamp( targetZoom, MIN_ZOOM, MAX_ZOOM );
}
