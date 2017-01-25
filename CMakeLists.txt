cmake_minimum_required(VERSION 3.3)
project(ex6)

set(core_sockets sockets/Socket.cpp sockets/Udp.cpp sockets/Tcp.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
find_package(Threads REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_library(sockets ${core_sockets})

set(SOURCE_FILES
        BFS.cpp BFS.h
        Cab.cpp Cab.h
        Driver.cpp Driver.h
        Grid2D.cpp Grid2D.h
        Intersection.cpp Intersection.h
        LuxuryCab.cpp LuxuryCab.h
        Map.cpp Map.h
        Passenger.cpp Passenger.h
        Point.cpp Point.h
        StandartCab.cpp StandartCab.h
        TaxiCenter.cpp TaxiCenter.h
        Trip.cpp Trip.h)

add_executable(client DriverClient.cpp ${SOURCE_FILES})
add_executable(main main.cpp ${SOURCE_FILES})

target_link_libraries(main ${Boost_LIBRARIES} sockets Threads::Threads)
target_link_libraries(client ${Boost_LIBRARIES} sockets Threads::Threads)
