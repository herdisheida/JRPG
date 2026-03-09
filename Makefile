CXX      := clang++
CXXFLAGS := -std=c++23 -Wall -Wextra -pedantic -Iinclude # newest version

BUILD_NAME := JRPG
SRC = main.cpp src/Battle.cpp
OUT = game

SRCS := main.cpp ast.cpp
OBJS := $(SRCS:.cpp=.o)

all: $(OUT) info

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)

.PHONY: all clean info

