CXX = g++
CXXFLAGS = -g -Wall -std=c++11
TARGET = SettlersOfCatan
SRCS = main.cpp Catan.cpp Player.cpp Board.cpp vertex.cpp edge.cpp hex_tile.cpp Resource.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = Catan.hpp Player.hpp Board.hpp vertex.hpp edge.hpp hex_tile.hpp Resource.hpp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
