//
// Created by dominik on 24.11.25.
//

#ifndef GAME1_UIBUTTON_H
#define GAME1_UIBUTTON_H

#include <SFML/Graphics/Sprite.hpp>
#include <utility>
#include "UIElement.h"

/**
 * Basic button UI class that can be clicked and trigger an event.
 * When the event is triggered, empty event data is sent to the event system. To add custom event with data, override the onClick method.
 * @tparam EventType A type of event that is triggered when the button is clicked and sent to event system
 */
template<typename EventType>
class UIButton : public UIElement
{
   public:
      explicit UIButton( std::string texturePath, const sf::Vector2f& position = { 0.f, 0.f }, float rotation = 0,
                         const sf::Vector2f& scale = { 1.f, 1.f }, bool isVisible = true );

      void onStart( std::shared_ptr<GameContext>& context ) override;

      void draw( sf::RenderTarget& target, const Renderer& renderer ) override;

      bool onClick( const sf::Vector2f& position ) override;

   protected:
      // TODO pointer to context. Better way?
      // Raw pointer since context is not owned by this class and outlives this object. Nullptr means critical error and program should stop.
      GameContext* gameContext;
      std::string texturePath;
      sf::Sprite buttonSprite;
};

// Templated implementation

template<typename EventType>
UIButton<EventType>::UIButton( std::string texturePath, const sf::Vector2f& position, float rotation, const sf::Vector2f& scale,
                               bool isVisible )
      : UIElement( position, rotation, scale, isVisible ), gameContext( nullptr ), texturePath( std::move( texturePath ) )
{
}

template<typename EventType>
void UIButton<EventType>::onStart( std::shared_ptr<GameContext>& context )
{
   gameContext = context.get();
   buttonSprite.setTexture( context->textureManager->loadTexture( texturePath ) );
   buttonSprite.setPosition( getPosition() );
   buttonSprite.setRotation( getRotation() );
   buttonSprite.setScale( getScale() );
   // Buttons origin centered by default
   buttonSprite.setOrigin( buttonSprite.getLocalBounds().width / 2, buttonSprite.getLocalBounds().height / 2 );
   UIElement::onStart( context );
}

template<typename EventType>
void UIButton<EventType>::draw( sf::RenderTarget& target, const Renderer& renderer )
{
   renderer.render( buttonSprite, target );
   UIElement::draw( target, renderer );
}

template<typename EventType>
bool UIButton<EventType>::onClick( const sf::Vector2f& position )
{
   if( buttonSprite.getGlobalBounds().contains( position ) )
   {
      gameContext->eventSystem->publish<EventType>( EventType{} );
      return true;
   }

   return UIElement::onClick( position );
}



#endif //GAME1_UIBUTTON_H
