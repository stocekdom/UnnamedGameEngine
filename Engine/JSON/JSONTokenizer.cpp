//
// Created by dominik on 14.02.26.
//

#include "JSONTokenizer.h"
#include <charconv>
#include <stdexcept>

JSONTokenizer::JSONTokenizer( const std::string_view& input ) : inputView( input )
{
}

Token JSONTokenizer::getNextToken()
{
   while( true )
   {
      if( inputView.empty() )
         return Token( std::string_view(), TokenType::EndOfFile );

      if( inputView.front() == '\n' )
      {
         ++currentLine;
         readCharsOnLine = 0;
         inputView.remove_prefix( 1 );
      }

      if( std::isspace( inputView.front() ) )
      {
         ++readCharsOnLine;
         inputView.remove_prefix( 1 );
         continue;
      }

      switch( inputView.front() )
      {
         case '{': return processSimpleToken( TokenType::LBrace );
         case '}': return processSimpleToken( TokenType::RBrace );
         case '[': return processSimpleToken( TokenType::LBracket );
         case ']': return processSimpleToken( TokenType::RBracket );
         case ':': return processSimpleToken( TokenType::Colon );
         case ',': return processSimpleToken( TokenType::Comma );
         case '"': return processString();
         case 'n': return processLiteral( "null", TokenType::Null );
         case 't': return processLiteral( "true", TokenType::True );
         case 'f': return processLiteral( "false", TokenType::False );
         default:
         {
            if( isdigit( inputView.front() ) || inputView.front() == '-' )
               return processNumber();

            throw JSONException(
               "Unexpected character '" + std::string( 1, inputView.front() ) + "' on line " + std::to_string( currentLine ) +
               " position " + std::to_string( readCharsOnLine + 1 ) );
         }
      }
   }
}

Token JSONTokenizer::processSimpleToken( TokenType type )
{
   auto token = Token( inputView.substr( 0, 1 ), type, currentLine, readCharsOnLine );
   ++readCharsOnLine;
   inputView.remove_prefix( 1 );
   return token;
}

Token JSONTokenizer::processString()
{
   // Remove the initial " character
   ++readCharsOnLine;
   inputView.remove_prefix( 1 );

   auto endQuoteIndex = inputView.find( '"' );

   if( endQuoteIndex == std::string_view::npos )
      throw JSONException(
         "Unterminated JSON string on line " + std::to_string( currentLine ) + " position " +
         std::to_string( readCharsOnLine + 1 ) );

   auto token = Token( inputView.substr( 0, endQuoteIndex ), TokenType::String, currentLine, readCharsOnLine );
   readCharsOnLine += endQuoteIndex + 1;
   inputView.remove_prefix( endQuoteIndex + 1 );
   return token;
}

Token JSONTokenizer::processLiteral( const std::string& literal, TokenType type )
{
   size_t currentViewIndex = 0;

   for( auto c: literal )
   {
      ++readCharsOnLine;
      if( inputView.at( currentViewIndex++ ) != c )
         throw JSONException(
            "Expected " + literal + " on line " + std::to_string( currentLine ) + " position " +
            std::to_string( readCharsOnLine ) );
   }

   auto token = Token( inputView.substr( 0, literal.size() ), type, currentLine, readCharsOnLine - literal.size() );
   inputView.remove_prefix( literal.size() );
   return token;
}

Token JSONTokenizer::processNumber()
{
   auto endIndex = inputView.find_first_not_of( "0123456789.-e" );

   double dummyValue;
   auto [ ptr, errc ] = std::from_chars( inputView.data(), inputView.data() + endIndex, dummyValue, std::chars_format::general );

   if( errc != std::errc() || ptr != inputView.data() + endIndex )
      throw JSONException(
         "Invalid number on line " + std::to_string( currentLine ) + " position " + std::to_string( readCharsOnLine + 1 ) );

   auto token = Token( inputView.substr( 0, endIndex ), TokenType::Number, currentLine, readCharsOnLine );
   readCharsOnLine += endIndex;
   inputView.remove_prefix( endIndex );
   return token;
}
