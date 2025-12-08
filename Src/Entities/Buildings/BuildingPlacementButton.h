//
// Created by dominik on 03.12.25.
//

#ifndef GAME1_BUILDINGPLACEMENTBUTTON_H
#define GAME1_BUILDINGPLACEMENTBUTTON_H

#include "BuildingEvents.h"
#include "../../../Base/UI/UIButton.h"

template<BuildingType T>
class BuildingPlacementButton : public UIButton<BuildingPlacingStarted>
{
   public:
      explicit BuildingPlacementButton( const std::string& texturePath, const sf::Vector2f& position = { 0.f, 0.f },
                                        float rotation = 0,
                                        const sf::Vector2f& scale = { 1.f, 1.f }, bool isVisible = true );

      bool onClick( const sf::Vector2f& position ) override;
};

template<BuildingType T>
BuildingPlacementButton<T>::BuildingPlacementButton( const std::string& texturePath, const sf::Vector2f& position, float rotation,
                                                     const sf::Vector2f& scale, bool isVisible )
      : UIButton( texturePath, position, rotation, scale, isVisible )
{
}

template<BuildingType T>
bool BuildingPlacementButton<T>::onClick( const sf::Vector2f& position )
{
   if( buttonSprite.getGlobalBounds().contains( position ) )
   {
      gameContext->eventSystem->publish<BuildingPlacingStarted>( BuildingPlacingStarted{ T, position } );
      return true;
   }

   return UIElement::onClick( position );
}

#endif //GAME1_BUILDINGPLACEMENTBUTTON_H
