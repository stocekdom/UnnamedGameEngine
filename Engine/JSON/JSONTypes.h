//
// Created by dominik on 14.02.26.
//

#ifndef GAME1_JSONTYPES_H
#define GAME1_JSONTYPES_H
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

struct Json;

using JsonObject = std::unordered_map<std::string, Json>;
using JsonArray = std::vector<Json>;
using JsonNull = std::nullopt_t;

struct Json
{
   using Value = std::variant<double, JsonNull, bool, JsonObject, JsonArray, std::string>;

   Json() : value( std::nullopt )
   {
   }

   explicit Json( Value&& v ) : value( std::move( v ) )
   {
   }

   explicit Json( const Value& v ) : value( v )
   {
   }

   Json( const Json& other ) = default;

   Json( Json&& other ) noexcept = default;

   Json& operator=( const Json& other ) = default;

   Json& operator=( Json&& other ) noexcept = default;

   Value value;
};

enum class TokenType
{
   LBrace, // {
   RBrace, // }
   LBracket, // [
   RBracket, // ]
   Colon, // :
   Comma, // ,

   String,
   Number,
   True,
   False,
   Null,

   EndOfFile,
   Error
};

struct Token
{
   std::string_view text;
   TokenType type;
   size_t line = 0;
   size_t column = 0;
};

class JSONException : public std::runtime_error
{
   public:
      explicit JSONException( const std::string& message ) : std::runtime_error( message )
      {
      }
};

#endif //GAME1_JSONTYPES_H
