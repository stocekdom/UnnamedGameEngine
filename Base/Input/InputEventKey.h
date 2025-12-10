//
// Created by dominik on 27.11.25.
//

#ifndef GAME1_INPUTEVENTKEY_H
#define GAME1_INPUTEVENTKEY_H

struct InputEventKey
{
   enum class Type
   {
      KeyboardPress,
      KeyboardRelease,
      MouseButtonPress,
      MouseButtonRelease,
      MouseMove,
      MouseWheel,
      None
   };

   Type type = Type::None;
   // Use -1 for events with no code
   int code = -1;

   bool operator==( const InputEventKey& other ) const
   {
      return type == other.type && code == other.code;
   }
};

struct InputEventKeyHash
{
   size_t operator()( const InputEventKey& k ) const noexcept
   {
      return static_cast<size_t>( k.type ) * 1024 + static_cast<size_t>( k.code + 1 );
   }
};

#endif //GAME1_INPUTEVENTKEY_H
