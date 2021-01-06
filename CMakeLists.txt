cmake_minimum_required(VERSION 3.17)
project(conways_game_of_life)

set(CMAKE_CXX_STANDARD 17)

add_executable(conways_game_of_life src/main.cpp src/gameoflife.h src/gameoflife.cpp src/renderingengine/renderingengine.h src/renderingengine/renderingengine.cpp src/main_auxiliary.cpp src/main_auxiliary.h)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)


INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
