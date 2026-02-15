//
// Created by dominik on 15.02.26.
//

#include "../TestFramework.h"
#include "../../Engine/Core/Util.h"
#include "../../Engine/JSON/JSONParser.h"

template<typename T>
void testValue( const Json::Value& value, const T& expectedValue )
{
   assert( std::holds_alternative<T>( value ) );
   const auto& actualValue = std::get<T>( value );
   assert( actualValue == expectedValue );
}

template<typename T>
void testKeyValue( const JsonObject& object, const std::string& key, const T& expectedValue )
{
   static_assert( Util::does_variant_contain_v<T, Json::Value>, "Type T is not an alternative of a JSON value variant" );
   assert( object.contains( key ) );
   testValue( object.at( key ).value, expectedValue );
}

TEST( JSONBasicParsingTest )
{
   std::string basicJson =
         R"( { "name": "Tester", "flag": true, "num": 100, "sciNum": 2e3, "sciNum2": -100e-2, "decNum": 12.3 } )";
   JSONParser parser;
   auto json = parser.parseFromString( basicJson );
   assert( std::holds_alternative<JsonObject>( json.value ) );
   const auto& jsonObject = std::get<JsonObject>( json.value );
   testKeyValue<std::string>( jsonObject, "name", "Tester" );
   testKeyValue( jsonObject, "flag", true );
   testKeyValue( jsonObject, "num", 100.0 );
   testKeyValue( jsonObject, "sciNum", 2000.0 );
   testKeyValue( jsonObject, "sciNum2", -1.0 );
   testKeyValue( jsonObject, "decNum", 12.3 );
}

TEST( JSONArrayParsingTest )
{
   std::string jsonString = R"( [ "Tester", true, 100, 2e3, {"x": 1, "y":2}, 12.3, ["x", "y"], [] ] )";
   JSONParser parser;
   auto json = parser.parseFromString( jsonString );
   assert( std::holds_alternative<JsonArray>( json.value ) );
   const auto& jsonArray = std::get<JsonArray>( json.value );
   assert( jsonArray.size() == 8 );
   testValue<std::string>( jsonArray[ 0 ].value, "Tester" );
   testValue( jsonArray[ 1 ].value, true );
   testValue( jsonArray[ 2 ].value, 100.0 );
   testValue( jsonArray[ 3 ].value, 2000.0 );
   assert( std::holds_alternative<JsonObject>( jsonArray[4].value ) );
   const auto& jsonObject = std::get<JsonObject>( jsonArray[ 4 ].value );
   testKeyValue( jsonObject, "x", 1.0 );
   testKeyValue( jsonObject, "y", 2.0 );
   testValue( jsonArray[ 5 ].value, 12.3 );
   assert( std::holds_alternative<JsonArray>( jsonArray[6].value ) );
   const auto& jsonArray2 = std::get<JsonArray>( jsonArray[ 6 ].value );

   assert( jsonArray2.size() == 2 );
   testValue<std::string>( jsonArray2[ 0 ].value, "x" );
   testValue<std::string>( jsonArray2[ 1 ].value, "y" );

   assert( std::holds_alternative<JsonArray>( jsonArray[7].value ) );
   const auto& jsonArray3 = std::get<JsonArray>( jsonArray[ 7 ].value );
   assert( jsonArray3.empty() );
}

TEST( JSONObjectParsingTest )
{
   std::string jsonString = R"( { "nested": { "nested2": {"x": 1, "y": 2 },"empty": {}, "flag": false } } )";
   JSONParser parser;
   auto json = parser.parseFromString( jsonString );
   assert( std::holds_alternative<JsonObject>( json.value ) );
   const auto& jsonObject = std::get<JsonObject>( json.value );
   assert( jsonObject.contains( "nested" ) );
   assert( std::holds_alternative<JsonObject>( jsonObject.at( "nested" ).value ) );
   const auto& nestedObject = std::get<JsonObject>( jsonObject.at( "nested" ).value );
   assert( nestedObject.contains( "nested2" ) );
   assert( std::holds_alternative<JsonObject>( nestedObject.at( "nested2" ).value ) );
   const auto& nestedObject2 = std::get<JsonObject>( nestedObject.at( "nested2" ).value );
   testKeyValue( nestedObject2, "x", 1.0 );
   testKeyValue( nestedObject2, "y", 2.0 );
   assert( nestedObject.contains( "empty" ) );
   assert( std::holds_alternative<JsonObject>( nestedObject.at( "empty" ).value ) );
   const auto& emptyObject = std::get<JsonObject>( nestedObject.at( "empty" ).value );
   assert( emptyObject.empty() );
   testKeyValue( nestedObject, "flag", false );
}

TEST( InvalidJSONParsingTests )
{
   std::string invalidValue = R"( :{ "name": "Tester"} )";
   JSONParser parser;
   assert_throws( parser.parseFromString( invalidValue ), JSONException );

   std::string invalidObject = R"( {"name": "Tester", "flag": true, "num": 100, "sciNum": 2e3, "decNum": 12.3, } )";
   assert_throws( parser.parseFromString( invalidObject ), JSONException );

   std::string duplicateKey = R"( {"name": "Tester", "flag": true, "num": 100, "name": "Tester2"} )";
   assert_throws( parser.parseFromString( duplicateKey ), JSONException );

   std::string invalid = R"( {"name": "Tester": "tt")";
   assert_throws( parser.parseFromString( invalid ), JSONException );

   std::string invalid2 = R"( {"name": "Tester",,"name2": "Tester2"} )";
   assert_throws( parser.parseFromString( invalid2 ), JSONException );

   std::string invalid3 = R"( {"name": "Tester", "flag": } )";
   assert_throws( parser.parseFromString( invalid3 ), JSONException );

   std::string invalid4 = R"( ["1", "2",,"3"] )";
   assert_throws( parser.parseFromString( invalid4 ), JSONException );
}
