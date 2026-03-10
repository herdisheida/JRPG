CXX      := clang++
CXXFLAGS := -std=c++23 -Wall -Wextra -pedantic # newest version

SRC = main.cpp \
	src/Battle.cpp \
	src/CreatureSelection.cpp \
	src/Encounters.cpp \
	src/EnemyField.cpp \
	src/GameEnd.cpp \
	src/GameSettings.cpp \
	src/Input.cpp \
	src/OverworldMap.cpp

OUT:= run

all: $(OUT) info

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

.PHONY: all clean info

