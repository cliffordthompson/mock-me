# mock-me
Bare C function mocking utility. This is currently a work in progress and only works in 
very specific scenarios.

## Building

This project uses [CMake](https://cmake.org/) to generate supported native build files.

 - cmake .
 - cmake --build . --config Debug

 ## Using

 The main.cp shows a few examples, but basically something like this:

 ``` cpp
 FunctionMocker mocker(testFunc, mockFunc);
 testFunc(); // Will call mockFunc() instead
 ```