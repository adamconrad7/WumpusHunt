CC = g++ -std=c++11
CXXFLAGS = -g -Wall

all:WumpusHunt

WumpusHunt: hunt.o dungeon.o room.o pitfall.o bats.o gold.o wumpus.o explorer.o
	$(CC) $(CXXFLAGS) -o WumpusHunt hunt.o dungeon.o room.o pitfall.o bats.o gold.o wumpus.o


pitfall.o: pitfall.cpp event.hpp
	$(CC) $(CXXFLAGS) -c pitfall.cpp

bats.o: bats.cpp event.hpp
	$(CC) $(CXXFLAGS) -c bats.cpp

gold.o: gold.cpp event.hpp
	$(CC) $(CXXFLAGS) -c gold.cpp

wumpus.o: wumpus.cpp event.hpp
	$(CC) $(CXXFLAGS) -c wumpus.cpp

hunt.o: hunt.cpp dungeon.cpp room.cpp explorer.cpp
	$(CC) $(CXXFLAGS) -c hunt.cpp explorer.cpp

dungeon.o: dungeon.cpp room.cpp explorer.cpp bats.cpp
	$(CC) $(CXXFLAGS) -c dungeon.cpp explorer.cpp bats.cpp

room.o: room.cpp pitfall.cpp bats.cpp gold.cpp wumpus.cpp event.cpp
		$(CC) $(CXXFLAGS) -c room.cpp

explorer.o: explorer.cpp
		$(CC) $(CXXFLAGS) -c explorer.cpp

clean:
	rm -rf *.o *.out
