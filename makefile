
all: server client

# Put here all the common files which are being used both in client and server
COMMON_SOURCES = BFS.cpp BFS.h Cab.cpp Cab.h Driver.cpp Driver.h Grid2D.cpp Grid2D.h Intersection.cpp Intersection.h LuxuryCab.cpp LuxuryCab.h Map.cpp Map.h Passenger.cpp Passenger.h Point.cpp Point.h StandartCab.cpp StandartCab.h TaxiCenter.cpp TaxiCenter.h Trip.cpp Trip.h
server:
	g++ -std=c++0x main.cpp $(COMMON_SOURCES) -lboost_serialization -I. -o server.out
# (for example)
client:
	g++ -std=c++0x DriverClient.cpp $(COMMON_SOURCES) -lboost_serialization -I. -o client.out
