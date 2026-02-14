This is a simple game engine with 2D graphics using SFML

Required setup: 
1. sudo apt install libsfml-dev

Manual compilation:
1. cmake -S . -B build
2. cmake --build build

Previous commands build the entire project. To build individual use:

> For building just the game
> cmake --build build --target game

> For building the tests
> cmake --build build --target engineTests

To run tests compile using the previous command and either use:

> ./engineTests
> To manually run the test binary

> ctest --test-dir build 
> To run tests using Cmake
