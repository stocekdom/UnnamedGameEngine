//
// Created by dominik on 14.02.26.
//

#ifndef GAME1_JSONTYPES_H
#define GAME1_JSONTYPES_H
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

struct Json;

using JsonObject = std::unordered_map<std::string, Json>;
using JsonArray = std::vector<Json>;
using JsonNull = std::nullopt_t;

struct Json
{
   Json( Json&& other ) = default;

   Json& operator=( Json&& other ) = default;

   using Value = std::variant<JsonNull, bool, double, JsonObject, JsonArray, std::string>;

   Value value;
};

enum class TokenType {
   LBrace,     // {
   RBrace,     // }
   LBracket,   // [
   RBracket,   // ]
   Colon,      // :
   Comma,      // ,

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
};
#endif //GAME1_JSONTYPES_H
