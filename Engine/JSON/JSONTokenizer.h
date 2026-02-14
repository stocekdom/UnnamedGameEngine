//
// Created by dominik on 14.02.26.
//

#ifndef GAME1_JSONTOKENIZER_H
#define GAME1_JSONTOKENIZER_H
#include <string_view>

#include "JSONTypes.h"

/**
 * This class tokenizes the input string.
 * For optimization the tokens use string_view for the values, and the tokenizer also works with a string_view of a passed string
 * @warning The caller must ensure the string passed into the tokenizer is valid when calling getNextToken. Otherwise, it's undefined behavior
 */
class JSONTokenizer
{
   public:
      explicit JSONTokenizer( const std::string_view& input );

      Token getNextToken();

   private:
      std::string_view inputView;
      unsigned int readCharsOnLine = 0;
      unsigned int currentLine = 1;

      Token processSimpleToken( TokenType type );

      Token processString();

      Token processLiteral( const std::string& literal, TokenType type );

      Token processNumber();
};

#endif //GAME1_JSONTOKENIZER_H
