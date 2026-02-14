//
// Created by dominik on 14.02.26.
//

#ifndef GAME1_TESTFRAMEWORK_H
#define GAME1_TESTFRAMEWORK_H

#include <cassert>
#include <functional>
#include <vector>

struct TestRegistry
{
   static std::vector<std::pair<const char*, std::function<void()>>>& tests()
   {
      static std::vector<std::pair<const char*, std::function<void()>>> t;
      return t;
   }
};

#define TEST(name)      \
void name();            \
                        \
inline struct name##_reg {     \
   name##_reg(){ TestRegistry::tests().emplace_back(#name, name); } \
} name##_instance;      \
inline void name()

#define ASSERT_THROWS( code )                         \
{                                                     \
bool exceptionThrown = false;                         \
\
try{ code; } catch( ... ){ exceptionThrown = true; }  \
assert( exceptionThrown );                            \
}

#endif //GAME1_TESTFRAMEWORK_H
