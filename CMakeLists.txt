cmake_minimum_required(VERSION 3.14)
project(eight_minute_empire)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        eight_minute_empire
        Maps/Map.h
        Maps/Map.cpp
#       Maps/MapDriver.cpp
        Maps/MapLoader.h
        Maps/MapLoader.cpp
        Players/Player.h
        Players/Player.cpp
#       Players/PlayerDriver.cpp
        Cards/Cards.h
        Cards/Cards.cpp
#        Cards/CardsDriver.cpp
        Bidding/BiddingFacility.h
        Bidding/BiddingFacility.cpp
#        Bidding/BiddingFacilityDriver.cpp
        Game/GameEngine.cpp
        Game/GameEngine.h
#        Game/GameDriver.cpp
        Players/PlayerStrategies.cpp
        Players/PlayerStrategies.h
#        Players/PlayerStrategiesDriver.cpp
#        Maps/MapSingletonDriver.cpp
        Game/GameObservers.cpp
        Game/GameObservers.h
#        Game/GameStatsDriver.cpp
        Cards/Factory/CardsFactory.h
        Cards/Factory/GameCard.cpp
        Cards/Factory/CardFactoryDriver.cpp)
