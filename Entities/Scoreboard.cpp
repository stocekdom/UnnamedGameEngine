//
// Created by dominik on 15.10.25.
//
#include <iostream>
#include "Scoreboard.h"

Scoreboard::Scoreboard( const std::string& fontPath, const std::string& inText, int size, sf::Color color, sf::Vector2f position, float rotation,
                        sf::Vector2f scale ) : UIElementText( fontPath, inText, size, color, position, rotation, scale ), score( 0 )
{
   updateText();
}

void Scoreboard::addScore( size_t amount )
{
   score += amount;
   updateText();
}

void Scoreboard::reduceScore( size_t amount )
{
   score -= amount;
   updateText();
}

void Scoreboard::updateText()
{
   std::cout << "Score: " << score << " String: " << std::to_string( score ) << std::endl;
   text.setString( "Current score: " + std::to_string( score ) );
}

std::size_t Scoreboard::getScore() const
{
   return score;
}

