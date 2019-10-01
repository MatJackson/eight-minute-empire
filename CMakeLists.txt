cmake_minimum_required(VERSION 3.14)
project(eight_minute_empire)

set(CMAKE_CXX_STANDARD 14)

add_executable(eight_minute_empire Maps/Map.cpp Maps/Map.h Maps/MapDriver.cpp Maps/MapLoader.cpp Maps/MapLoader.h Players/Player.cpp Players/Player.h Cards/Cards.cpp Cards/Cards.h Cards/CardsDriver.cpp Players/PlayerDriver.cpp)
