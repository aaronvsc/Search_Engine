cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

<<<<<<< HEAD
add_executable(tests_Document test_DocumentParser.cpp)
add_test(NAME TestsDocument COMMAND tests_Document)
=======
add_executable(AvlTest AvlTreeTest.cpp AvlTree.h)
>>>>>>> d74a44d79f88b187d1434d22f7880f99622d7f17
add_executable(rapidJSONExample rapidJSONExample.cpp)
add_executable(supersearch main.cpp)

# this makes sure we also link rapidjson
target_include_directories(rapidJSONExample PRIVATE rapidjson/)

set(CMAKE_VERBOSE_MAKEFILE OFF)
