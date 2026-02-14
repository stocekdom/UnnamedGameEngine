//
// Created by dominik on 14.02.26.
//

#include "TestFramework.h"
#include <iostream>

int main()
{
   for( auto& [ name, test ]: TestRegistry::tests() )
   {
      std::cout << "Running test " << name << " -----------------------------" << std::endl;
      test();
      std::cout << "Test " << name << " finished successfully!" << std::endl;
      std::cout << std::endl;
   }

   std::cout << std::endl;
   std::cout << "All tests finished successfully!" << std::endl;
}
