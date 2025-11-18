//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_UIELEMENT_H
#define GAME1_UIELEMENT_H

#include <vector>
#include <memory>
#include "../Input/Clickable.h"
#include "../Renderer.h"

/**
 * Base class for all UI elements with lightweight spacial information.
 * Doesnt provide any component that will get drawn. It's up to the derived classes to implement how they will get drawn
 */
   class UIElement : public Clickable, public std::enable_shared_from_this<UIElement>
{
   public:
      UIElement( const sf::Vector2f& position, float rotation, bool isVisible );

      virtual ~UIElement() = default;

      // TODO currently just simple UI. might add tick function in the future

      [[nodiscard]] virtual bool isVisible() const;

      [[nodiscard]] virtual sf::Vector2f getPosition() const;

      [[nodiscard]] virtual float getRotation() const;

      virtual void setIsVisibleElement( bool isVisible );

      virtual void addChild( const std::shared_ptr<UIElement>& child );

      virtual void setParent( const std::shared_ptr<UIElement>& newParent );

      virtual void move( const sf::Vector2f& offset );

      virtual void rotate( float rotation );

      virtual void draw( sf::RenderTarget& target, const Renderer& renderer );

   protected:
      sf::Vector2f localPosition;
      float localRotation;
      bool isVisibleElement;
      std::weak_ptr<UIElement> parent;
      std::vector<std::shared_ptr<UIElement>> children;
};
#endif //GAME1_UIELEMENT_H
