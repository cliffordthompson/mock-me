# CMakeList.txt : CMake project for FunctionMocker, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (FunctionMocker "main.cpp" "FunctionMocker.h" "FunctionMocker.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FunctionMocker PROPERTY CXX_STANDARD 20)
endif()

add_compile_definitions(_AMD64_)

# TODO: Add tests and install targets if needed.
