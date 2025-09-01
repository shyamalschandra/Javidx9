# Makefile for macOS Tetris Games
# Uses ncurses for terminal manipulation

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
LIBS = -lncurses

# Target executable names
TARGET_BASIC = tetris
TARGET_COLORFUL = tetris-colorful

# Source files
SOURCES_BASIC = OneLoneCoder_Tetris_macOS.cpp
SOURCES_COLORFUL = OneLoneCoder_Tetris_Colorful.cpp

# Object files
OBJECTS_BASIC = $(SOURCES_BASIC:.cpp=.o)
OBJECTS_COLORFUL = $(SOURCES_COLORFUL:.cpp=.o)

# Default target
all: $(TARGET_BASIC) $(TARGET_COLORFUL)

# Link the basic executable
$(TARGET_BASIC): $(OBJECTS_BASIC)
	$(CXX) $(OBJECTS_BASIC) -o $(TARGET_BASIC) $(LIBS)

# Link the colorful executable
$(TARGET_COLORFUL): $(OBJECTS_COLORFUL)
	$(CXX) $(OBJECTS_COLORFUL) -o $(TARGET_COLORFUL) $(LIBS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS_BASIC) $(OBJECTS_COLORFUL) $(TARGET_BASIC) $(TARGET_COLORFUL)

# Install ncurses if not present (macOS)
install-deps:
	brew install ncurses

# Run the basic game
run: $(TARGET_BASIC)
	./$(TARGET_BASIC)

# Run the colorful game
run-colorful: $(TARGET_COLORFUL)
	./$(TARGET_COLORFUL)

# Phony targets
.PHONY: all clean install-deps run run-colorful
