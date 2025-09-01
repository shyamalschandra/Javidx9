# Makefile for macOS Tetris Game
# Uses ncurses for terminal manipulation

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
LIBS = -lncurses

# Target executable name
TARGET = tetris

# Source files
SOURCES = OneLoneCoder_Tetris_macOS.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Install ncurses if not present (macOS)
install-deps:
	brew install ncurses

# Run the game
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean install-deps run
