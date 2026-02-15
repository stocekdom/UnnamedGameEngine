//
// Created by dominik on 14.02.26.
//

#ifndef GAME1_JSONPARSER_H
#define GAME1_JSONPARSER_H

#include <memory>

#include "JSONTokenizer.h"
#include "JSONTypes.h"

class JSONParser
{
   public:
      Json parseFromFile( const std::string& path );

      Json parseFromString( const std::string& jsonString );

   private:
      // This limits the size of the JSON we want to fit into a string. If the JSON is larger, we need to parse it using streams
      static constexpr long MAX_JSON_IN_MEMORY_SIZE = 16777216;
      Token currentToken = { {}, TokenType::Error };
      // Unique ptr since tokenizer is one time use only for one input
      std::unique_ptr<JSONTokenizer> tokenizer;

      /**
       * Tries to match the current token with a given type
       * If the tokens match, it loads another token into currentToken and returns the previous currentToken.
       * If the types don't match, an exception is thrown
       * @param type The token type to match
       * @return The matched token
       * @throws JSONException
       */
      [[nodiscard]] Token matchToken( TokenType type );

      /**
       * Tries to match the current token with a given type
       * If the tokens match, it loads another token into currentToken, but doesnt return anything, unlike matchToken
       * @see matchToken
       * If the types don't match, an exception is thrown
       * @param type
       */
      void expectToken( TokenType type );

      [[nodiscard]] Json parseNumber();

      [[nodiscard]] Json parseString();

      [[nodiscard]] Json parseObject();

      [[nodiscard]] Json parseArray();

      Json parseValue();
};

#endif //GAME1_JSONPARSER_H
