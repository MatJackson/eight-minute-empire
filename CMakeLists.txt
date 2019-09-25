cmake_minimum_required(VERSION 3.14)
project(eight_minute_empire)

set(CMAKE_CXX_STANDARD 14)
find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

add_executable(eight_minute_empire main.cpp Maps/Map.cpp Maps/Map.h Maps/MapDriver.cpp Maps/MapDriver.h Maps/MapLoader.cpp Maps/MapLoader.h Players/Player.cpp Players/Player.h Cards/Cards.cpp Cards/Cards.h Cards/CardsDriver.cpp Cards/CardsDriver.h)
target_link_libraries(eight_minute_empire Qt5::Widgets)