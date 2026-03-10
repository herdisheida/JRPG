CXX      := clang++
CXXFLAGS := -std=c++23 -Wall -Wextra -pedantic -Iinclude # newest version

BUILD_NAME := JRPG
SRC = main.cpp src/Battle.cpp src/OverworldMap.cpp src/EnemyField.cpp src/Helpers.cpp src/Encounters.cpp
OUT = game

all: $(OUT) info

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

.PHONY: all clean info

