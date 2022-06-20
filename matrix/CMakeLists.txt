cmake_minimum_required(VERSION 3.16)
project(Lexer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(lib_tests
  ./tests/vector_tests.cc
  ./tests/matrix_tests.cc
  )
target_link_libraries(lib_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(lib_tests)

add_library(matrix_lib STATIC
  main.cpp
  factory.cpp
)

# cmake -B build .

# valgrind -s --leak-check=full ./Lexer
