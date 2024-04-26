cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)
file(COPY Trees/ DESTINATION Trees/)
configure_file(stopWords.txt stopWords.txt COPYONLY)



# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(SystemTest test_System.cpp)
add_test(NAME TestsDocument COMMAND tests_Document)
add_executable(AvlTest AvlTreeTest.cpp AvlTree.h)
add_executable(rapidJSONExample rapidJSONExample.cpp)
add_executable(supersearch main.cpp stopWords.txt)

# this makes sure we also link rapidjson
target_include_directories(rapidJSONExample PRIVATE rapidjson/)

set(CMAKE_VERBOSE_MAKEFILE OFF)
