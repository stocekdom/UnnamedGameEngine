//
// Created by dominik on 15.11.25.
//
#include "PlayerController.h"
#include "../../Base/Core/Math.h"
#include "../../Base/GameMap/MapTile.h"
#include "../../Base/Input/ContextFactory.h"
#include "../Entities/Buildings/BuildingFactory.h"

// We initialize everything in the constructor since systems are already created at this point, and we don't need onStart
PlayerController::PlayerController( const std::shared_ptr<GameContext>& context ) : cameraSpeed( 0.f, 0.f ),
                                                                                    context( context.get() )
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
   // Added if condition to prevent camera stopping if the user holds the opposite buttons (holding A and starts holding D) and releases one of them, setting the camera speed to 0
   actions[ GameAction::CAMERA_MOVE_RIGHT ] = [this]( const ActionData& event ) {
      if( cameraSpeed.x >= 0.f || event.value != 0.f )
         updateCameraSpeedX( event.value );
   };
   actions[ GameAction::CAMERA_MOVE_LEFT ] = [this]( const ActionData& event ) {
      if( cameraSpeed.x <= 0.f || event.value != 0.f )
         updateCameraSpeedX( -event.value );
   };
   actions[ GameAction::CAMERA_MOVE_UP ] = [this]( const ActionData& event ) {
      if( cameraSpeed.y <= 0.f || event.value != 0.f )
         updateCameraSpeedY( -event.value );
   };
   actions[ GameAction::CAMERA_MOVE_DOWN ] = [this]( const ActionData& event ) {
      if( cameraSpeed.y >= 0.f || event.value != 0.f )
         updateCameraSpeedY( event.value );
   };
   actions[ GameAction::CAMERA_ZOOM ] = [this]( const ActionData& event ) { updateCameraZoom( event.value ); };
   actions[ GameAction::MOUSE_MOVE ] = [this]( const ActionData& event ) { onMouseMove( event.position ); };
   actions[ GameAction::PLACEMENT_CANCEL ] = [this]( const ActionData& event ) { onBuildingPlacingCancel(); };
   actions[ GameAction::PLACE_BUILDING ] = [this]( const ActionData& event ) { onBuildingPlaced( event.position ); };
}

void PlayerController::tick( float dt )
{
   if( cameraSpeed.x != 0.f || cameraSpeed.y != 0.f )
      context->scene->moveCamera( cameraSpeed * CAMERA_SPEED * dt );

   if( targetZoom != currentZoom )
   {
      float prevZoom = currentZoom;
      float delta = targetZoom - currentZoom;
      float change = dt * ZOOM_PER_SECOND;

      if( delta < 0 )
         currentZoom = std::max( targetZoom, currentZoom - change );
      else
         currentZoom = std::min( targetZoom, currentZoom + change );

      context->scene->zoomCamera( currentZoom / prevZoom );
   }
}

void PlayerController::onLeftClick( const ActionData& event ) const
{
   // ReSharper disable once CppExpressionWithoutSideEffects
   context->uiSystem->onLeftClick( event.position );
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
void PlayerController::onMouseMove( const sf::Vector2i& position )
{
   /*
   auto sharedPawn = buildingPawn.lock();

   if( !sharedPawn )
      return;

   auto snapResult = context->gameMapSystem->snapToMapTile( position );
   // Offset from the tile center to be closer to the bottom left corner of the ile
   snapResult.position.y += Math::IsometricConstants::BUILDING_TILE_CENTER_Y_OFFSET;
   sharedPawn->setPosition( snapResult.position );

   auto sharedTile = snapResult.tile.lock();

   if( !sharedTile )
      return;

   auto canBePlaced = sharedPawn->canBePlaced( sharedTile );

   if( canBePlaced != previousBuildingPlacingState )
   {
      if( canBePlaced )
         sharedPawn->setOverlayColor( GreenOverlay );
      else
         sharedPawn->setOverlayColor( RedOverlay );
   }

   previousBuildingPlacingState = canBePlaced;*/
}

void PlayerController::onBuildingPlacingStart( const BuildingPlacingStarted& event )
{
   /*
   // TODO properly handle left click on UI even in this context
   activeContext = placingContext;

   // Delete previous pawn if we click on UI without placing the previous one
   if( auto prevPawn = buildingPawn.lock() )
      context->scene->deleteOverlayEntityById( prevPawn->getId() );

   auto building = BuildingFactory::createBuilding( event.type, event.position );
   // TODO temporary hack to make the ghost house movable
   building->setMobility( Mobility::MOVABLE );
   building->onStart( context );

   // Set overlay and placement status so we can work with it in onMouseMove
   previousBuildingPlacingState = false;
   building->setOverlayColor( RedOverlay );
   buildingPawn = building;*/
}

void PlayerController::onBuildingPlacingCancel()
{
   /*
   auto sharedPawn = buildingPawn.lock();

   if( !sharedPawn )
      return;

   context->scene->deleteOverlayEntityById( sharedPawn->getId() );
   buildingPawn.reset();*/
}

void PlayerController::onBuildingPlaced( const sf::Vector2i& position )
{
   /*
   // TODO do this in main controller class
   // UI handled first
   if( context->uiSystem->onLeftClick( position ) )
      return;

   auto sharedPawn = buildingPawn.lock();

   if( !sharedPawn )
      return;

   // The position of the click should be enough, since in mouse move, we're snapping the house to the map tile
   if( !context->gameMapSystem->placeBuilding( position, sharedPawn ) )
      return;

   // TODO this shouldn't be done here. Switch to ECS
   movePawnFromOverlayToWorld( sharedPawn );
   */
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

void PlayerController::movePawnFromOverlayToWorld( const std::shared_ptr<Building>& building )
{
   /*
   context->scene->deleteOverlayEntityById( building->getId() );
   building->setSpawnCategory( SpawnCategory::WORLD );
   building->setMobility( Mobility::STATIC );
   context->scene->addEntityToScene( building );
   building->setOverlayColor( DefaultOverlay );
   buildingPawn.reset();
   activeContext = mainContext;
   */
}
