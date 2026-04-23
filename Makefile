# ============================================================
#  Makefile — Breakout C++ / SFML
#  Usage : make         → compile
#          make run     → compile + lancer
#          make clean   → nettoyer
# ============================================================

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LIBS     = -lsfml-graphics -lsfml-window -lsfml-system
TARGET   = breakout

SRCS = main.cpp Ball.cpp Paddle.cpp Brick.cpp Game.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
