//
// Created by dominik on 14.02.26.
//

#include "JSONParser.h"
#include "../Logging/Logger.h"
#include <charconv>
#include <fstream>

Json JSONParser::parseFromFile( const std::string& path )
{
   std::ifstream file( path, std::ios::binary );

   if( !file )
      LOG_ERROR( "Couldn't open JSON file " + path );

   file.seekg( 0, std::ios::end );
   auto size = file.tellg();
   file.seekg( 0 );

   // TODO implement streaming solution for large files
   if( size > MAX_JSON_IN_MEMORY_SIZE )
      throw JSONException( "JSON file is too large to process" );

   std::string buffer( size, '\0' );
   file.read( buffer.data(), size );

   return parseFromString( buffer );
}

Json JSONParser::parseFromString( const std::string& jsonString )
{
   tokenizer = std::make_unique<JSONTokenizer>( jsonString );
   // Initialize the token to the first token of the string
   currentToken = tokenizer->getNextToken();

   return parseValue();
}

Token JSONParser::matchToken( const TokenType type )
{
   if( currentToken.type != type )
      throw JSONException(
         "Invalid token " + std::string( currentToken.text ) + " at line " + std::to_string( currentToken.line ) + " position " +
         std::to_string( currentToken.column ) );

   auto prev = currentToken;
   currentToken = tokenizer->getNextToken();
   return prev;
}

void JSONParser::expectToken( TokenType type )
{
   // Silences the no_discard warning
   ( void )matchToken( type );
}

Json JSONParser::parseNumber()
{
   auto prevToken = matchToken( TokenType::Number );

   double value{};
   const auto& s = prevToken.text;
   auto [ ptr, ec ] = std::from_chars( s.data(), s.data() + s.size(), value );

   if( ec == std::errc() && ptr == s.data() + s.size() )
      return Json{ value };

   throw JSONException(
      "Invalid number at line " + std::to_string( prevToken.line ) + " position " + std::to_string( prevToken.column ) );
}

Json JSONParser::parseString()
{
   auto prevToken = matchToken( TokenType::String );
   return Json{ std::string( prevToken.text ) };
}

Json JSONParser::parseObject()
{
   expectToken( TokenType::LBrace );
   JsonObject object;

   // Handle empty object {}
   if( currentToken.type == TokenType::RBrace )
   {
      expectToken( TokenType::RBrace );
      return Json{ std::move( object ) };
   }

   while( true )
   {
      auto key = matchToken( TokenType::String );
      expectToken( TokenType::Colon );
      auto val = parseValue();
      auto [ it, inserted ] = object.try_emplace( std::string( key.text ), std::move( val ) );

      if( !inserted )
         throw JSONException(
            "Duplicate key " + std::string( key.text ) + " at line " + std::to_string( key.line ) + " position " +
            std::to_string( key.column ) );

      if( currentToken.type == TokenType::RBrace )
         break;

      expectToken( TokenType::Comma );
   }

   expectToken( TokenType::RBrace );
   return Json{ std::move( object ) };
}

Json JSONParser::parseArray()
{
   expectToken( TokenType::LBracket );
   JsonArray array;

   // Handle empty array []
   if( currentToken.type == TokenType::RBracket )
   {
      expectToken( TokenType::RBracket );
      return Json{ std::move( array ) };
   }

   while( true )
   {
      array.emplace_back( parseValue() );

      if( currentToken.type == TokenType::RBracket )
         break;

      expectToken( TokenType::Comma );
   }

   expectToken( TokenType::RBracket );
   return Json{ std::move( array ) };
}

Json JSONParser::parseValue()
{
   switch( currentToken.type )
   {
      case TokenType::False:
      {
         auto val = currentToken.type == TokenType::True;
         expectToken( TokenType::False );
         return Json{ val };
      }
      case TokenType::True:
      {
         auto val = currentToken.type == TokenType::True;
         expectToken( TokenType::True );
         return Json{ val };
      }
      case TokenType::Null:
         return Json{ std::nullopt };
      case TokenType::Number:
         return parseNumber();
      case TokenType::String:
         return parseString();
      case TokenType::LBracket:
         return parseArray();
      case TokenType::LBrace:
         return parseObject();
      default:
         throw JSONException(
            "Invalid value at line " + std::to_string( currentToken.line ) + " position " +
            std::to_string( currentToken.column ) );
   }
}
