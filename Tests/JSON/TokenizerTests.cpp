//
// Created by dominik on 14.02.26.
//

#include "../TestFramework.h"
#include "../../Engine/JSON/JSONTokenizer.h"
#include <string>

TEST( JSONTokenizerBasicTest )
{
   std::string basicJson = R"( { "name": "Tester", "data": ["x"], "num": 100, "sciNum": 2e3, "decNum": 12.3 } )";
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
   assert( token.type == TokenType::Number && token.text == "2e3" );
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