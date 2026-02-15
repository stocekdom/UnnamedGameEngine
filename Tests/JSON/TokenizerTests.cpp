//
// Created by dominik on 14.02.26.
//

#include "../TestFramework.h"
#include "../../Engine/JSON/JSONTokenizer.h"
#include <string>

TEST( JSONTokenizerBasicTest )
{
   std::string basicJson = R"( { "name": "Tester", "data": ["x"], "num": 100, "sciNum": -2.2e-3, "decNum": 12.3 } )";
   JSONTokenizer t( basicJson );
   assert( t.getNextToken().type == TokenType::LBrace );
   auto token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == "name" );
   assert( t.getNextToken().type == TokenType::Colon );
   token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == "Tester" );
   assert( t.getNextToken().type == TokenType::Comma );
   token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == "data" );
   assert( t.getNextToken().type == TokenType::Colon );
   assert( t.getNextToken().type == TokenType::LBracket );
   token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == "x" );
   assert( t.getNextToken().type == TokenType::RBracket );
   assert( t.getNextToken().type == TokenType::Comma );
   token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == "num" );
   assert( t.getNextToken().type == TokenType::Colon );
   token = t.getNextToken();
   assert( token.type == TokenType::Number && token.text == "100" );
   assert( t.getNextToken().type == TokenType::Comma );
   token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == "sciNum" );
   assert( t.getNextToken().type == TokenType::Colon );
   token = t.getNextToken();
   assert( token.type == TokenType::Number && token.text == "-2.2e-3" );
   assert( t.getNextToken().type == TokenType::Comma );
   token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == "decNum" );
   assert( t.getNextToken().type == TokenType::Colon );
   token = t.getNextToken();
   assert( token.type == TokenType::Number && token.text == "12.3" );
   assert( t.getNextToken().type == TokenType::RBrace );
}

TEST( JSONTokenizerAdvancedTest )
{
   std::string basicJson = R"({"flag":true,"flag2":false,"nullArray":[null,null],"nested":{"x":-1.4}})";
   JSONTokenizer t( basicJson );
   assert( t.getNextToken().type == TokenType::LBrace );
   auto token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == "flag" );
   assert( t.getNextToken().type == TokenType::Colon );
   token = t.getNextToken();
   assert( token.type == TokenType::True && token.text == "true" );
   assert( t.getNextToken().type == TokenType::Comma );
   token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == "flag2" );
   assert( t.getNextToken().type == TokenType::Colon );
   token = t.getNextToken();
   assert( token.type == TokenType::False && token.text == "false" );
   assert( t.getNextToken().type == TokenType::Comma );
   token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == "nullArray" );
   assert( t.getNextToken().type == TokenType::Colon );
   assert( t.getNextToken().type == TokenType::LBracket );
   token = t.getNextToken();
   assert( token.type == TokenType::Null && token.text == "null" );
   assert( t.getNextToken().type == TokenType::Comma );
   token = t.getNextToken();
   assert( token.type == TokenType::Null && token.text == "null" );
   assert( t.getNextToken().type == TokenType::RBracket );
   assert( t.getNextToken().type == TokenType::Comma );
   token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == "nested" );
   assert( t.getNextToken().type == TokenType::Colon );
   assert( t.getNextToken().type == TokenType::LBrace );
   token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == "x" );
   assert( t.getNextToken().type == TokenType::Colon );
   token = t.getNextToken();
   assert( token.type == TokenType::Number && token.text == "-1.4" );
   assert( t.getNextToken().type == TokenType::RBrace );
   assert( t.getNextToken().type == TokenType::RBrace );
}

void invalidJSONPreTest( JSONTokenizer& t, const std::string& fieldName )
{
   assert( t.getNextToken().type == TokenType::LBrace );
   auto token = t.getNextToken();
   assert( token.type == TokenType::String && token.text == fieldName );
   assert( t.getNextToken().type == TokenType::Colon );
}

TEST( JSONTokenizerInvalidNumber )
{
   std::string invalidJson = R"( {"num": -1.5-5})";
   JSONTokenizer t( invalidJson );
   invalidJSONPreTest( t, "num" );
   assert_throws( t.getNextToken(), JSONException );

   std::string invalidJson2 = R"( {"num": -1.5-e2})";
   JSONTokenizer t2( invalidJson2 );
   invalidJSONPreTest( t2, "num" );
   assert_throws( t2.getNextToken(), JSONException );

   std::string invalidJson3 = R"( {"num": 1e})";
   JSONTokenizer t3( invalidJson3 );
   invalidJSONPreTest( t3, "num" );
   assert_throws( t3.getNextToken(), JSONException );

   std::string invalidJson4 = R"( {"num": 1.5.6})";
   JSONTokenizer t4( invalidJson4 );
   invalidJSONPreTest( t4, "num" );
   assert_throws( t4.getNextToken(), JSONException );

   std::string invalidJson5 = R"( {"num": 1e-})";
   JSONTokenizer t5( invalidJson5 );
   invalidJSONPreTest( t5, "num" );
   assert_throws( t5.getNextToken(), JSONException );
}

TEST( JSONTokenizerInvalidLiteralTest )
{
   std::string lit1 = R"( {"name": falsee )";
   JSONTokenizer t( lit1 );
   invalidJSONPreTest( t, "name" );
   auto token = t.getNextToken();
   assert( token.type == TokenType::False && token.text == "false" );
   assert_throws( t.getNextToken(), JSONException );

   std::string lit2 = R"( {"name": x )";
   JSONTokenizer t2( lit2 );
   invalidJSONPreTest( t2, "name" );
   assert_throws( t2.getNextToken(), JSONException );
}

TEST( JSONTokenizerUnterminatedStringTest )
{
   std::string st1 = R"( {"name": "Tester )";
   JSONTokenizer t( st1 );
   invalidJSONPreTest( t, "name" );
   assert_throws( t.getNextToken(), JSONException );
}
