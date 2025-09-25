cmake_minimum_required(VERSION 3.16)
project(FormulaFrenzy)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)

# Automatically grab all .cpp files in src/
file(GLOB SOURCES src/*.cpp)

add_executable(FormulaFrenzy ${SOURCES})

target_link_libraries(FormulaFrenzy PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
