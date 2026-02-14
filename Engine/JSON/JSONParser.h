//
// Created by dominik on 14.02.26.
//

#ifndef GAME1_JSONPARSER_H
#define GAME1_JSONPARSER_H

#include "JSONTypes.h"

class JSONParser
{
   public:
      static JsonObject parseFromFile( const std::string& path );

      static JsonObject parseFromString( const std::string& jsonString );

   private:
      static JsonObject parseImpl( const std::string& data );
};

#endif //GAME1_JSONPARSER_H
