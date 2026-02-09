//
// Created by dominik on 15.11.25.
//

#include "PlayerController.h"
#include "../../Base/Core/Math.h"
#include "../../Base/GameMap/MapTile.h"
#include "../../Base/Input/ContextFactory.h"
#include "../Entities/Buildings/BuildingFactory.h"

// We initialize everything in the constructor since systems are already created at this point, and we don't need onStart
PlayerController::PlayerController( GameContext* context ) : Controller( context ), cameraSpeed( 0.f, 0.f )
{
   context->eventSystem->subscribe<GamePaused>( [this]( const GamePaused& event ) { onPauseGame( event ); } );
   context->eventSystem->subscribe<GameResumed>( [this]( const GameResumed& event ) { onResumeGame( event ); } );
   context->eventSystem->subscribe<BuildingPlacingStarted>(
      [this]( const BuildingPlacingStarted& event ) { onBuildingPlacingStart( event ); } );
   menuContext = ContextFactory::createPauseContext();
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
      gameContext->scene->moveCamera( cameraSpeed * getCameraZoomSpeedMultiplier() * CAMERA_SPEED * dt );

   if( targetZoom != currentZoom )
   {
      float prevZoom = currentZoom;
      float delta = targetZoom - currentZoom;
      float change = dt * ZOOM_PER_SECOND;

      if( delta < 0 )
         currentZoom = std::max( targetZoom, currentZoom - change );
      else
         currentZoom = std::min( targetZoom, currentZoom + change );

      gameContext->scene->zoomCamera( currentZoom / prevZoom );
   }
}

void PlayerController::onLeftClick( const ActionData& event ) const
{
}

// TODO currently pausing doesn't fully pause the game but only shows the menu and switches contexts. Add actual gameplay pausing
void PlayerController::onPauseGame( const GamePaused& event )
{
   beforePauseContext = activeContext;
   activeContext = menuContext;
}

void PlayerController::onResumeGame( const GameResumed& event )
{
   activeContext = beforePauseContext;
}

void PlayerController::onMouseMove( const sf::Vector2i& position )
{
   // Snap to tile
   auto snapResult = gameContext->gameMapSystem->snapToMapTile( position );
   // Offset from the tile center to be closer to the bottom left corner of the tile
   snapResult.position.y += Math::IsometricConstants::BUILDING_TILE_CENTER_Y_OFFSET;
   auto& pawnTransform = gameContext->scene->getComponentRegistry().getComponent<TransformComponent>(
      buildingPawn->getEntityId() );
   pawnTransform.setPosition( snapResult.position );

   auto sharedTile = snapResult.tile.lock();

   if( !sharedTile )
   {
      // Make sure to set the right color if we previously had a valid position, and now the tile is invalid
      updatePawnPlacingState( false );
      return;
   }

   auto canBePlaced = gameContext->constructionSystem->canConstruct( buildingPawn, sharedTile );
   updatePawnPlacingState( canBePlaced );
}

void PlayerController::onBuildingPlacingStart( const BuildingPlacingStarted& event )
{
   activeContext = placingContext;

   // Delete the previous pawn if we click on the button without placing the previous one
   // Optimization: If we click on the same building type, do nothing to avoid creating an entity of the same type
   if( buildingPawn )
   {
      if( buildingPawn->getType() == event.type )
         return;

      gameContext->scene->deleteEntity( buildingPawn->getEntityId() );
   }

   // Add an overlay house. This is the ghost house that follows the mouse. Overlay component is included from the factory
   buildingPawn = BuildingFactory::createBuilding( gameContext->scene.get(), event.type, event.position );

   auto& overlay = gameContext->scene->getComponentRegistry().getComponent<OverlaySpriteComponent>( buildingPawn->getEntityId() );
   // Set overlay and placement status so we can work with it in onMouseMove
   previousBuildingPlacingState = false;
   overlay.sprite.setColor( RedOverlay );
   // Direct origin manipulation, since overlays can be moved during runtime unlike static sprites, and we also have direct access to the sprite
   overlay.sprite.setOrigin( overlay.sprite.getLocalBounds().width / 2, overlay.sprite.getLocalBounds().height );
}

void PlayerController::onBuildingPlacingCancel()
{
   gameContext->scene->deleteEntity( buildingPawn->getEntityId() );
   buildingPawn = nullptr;
   activeContext = mainContext;
}

void PlayerController::onBuildingPlaced( const sf::Vector2i& position )
{
   // The position of the click should be enough, since in mouse move, we're snapping the house to the map tile and the pawn stays in that position
   auto tile = gameContext->gameMapSystem->getMapTile( position ).lock();

   if( !tile )
      return;

   if( !gameContext->constructionSystem->tryConstruct( buildingPawn, tile ) )
      return;

   // The house transform should be at the location of the last mouse move, so we don't need to update it here, unless there are position inconsistencies when moving and placing
   buildingPawn = nullptr;
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

float PlayerController::getCameraZoomSpeedMultiplier() const
{
   return std::max( 1.0f, currentZoom );
}

void PlayerController::updatePawnPlacingState( bool newState )
{
   if( newState != previousBuildingPlacingState )
   {
      auto& overlayComp = gameContext->scene->getComponentRegistry().getComponent<OverlaySpriteComponent>(
         buildingPawn->getEntityId() );

      if( newState )
         overlayComp.sprite.setColor( GreenOverlay );
      else
         overlayComp.sprite.setColor( RedOverlay );
   }

   previousBuildingPlacingState = newState;
}
