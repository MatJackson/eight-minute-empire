cmake_minimum_required(VERSION 3.14)
project(eight_minute_empire)

set(CMAKE_CXX_STANDARD 14)
find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

add_executable(eight_minute_empire main.cpp)
target_link_libraries(eight_minute_empire Qt5::Widgets)