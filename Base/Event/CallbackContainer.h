//
// Created by dominik on 22.11.25.
//

#ifndef GAME1_CALLBACKCONTAINER_H
#define GAME1_CALLBACKCONTAINER_H

#include <functional>

//Interface for all callback containers for type erasure
struct ICallbackContainer
{
   virtual ~ICallbackContainer() = default;
};

// Wrapper for storing callbacks of a specific type
template<typename T>
struct CallbackContainer : public ICallbackContainer
{
   public:
      std::vector<std::function<void( T& )>> callbackContainer;
};
#endif //GAME1_CALLBACKCONTAINER_H
