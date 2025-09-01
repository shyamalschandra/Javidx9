# macOS Tetris Game Port

This is a macOS-compatible port of the original Windows console Tetris game by OneLoneCoder (@Javidx9).

## What Changed

The original game used Windows-specific console API calls:
- `CreateConsoleScreenBuffer`
- `SetConsoleActiveScreenBuffer` 
- `WriteConsoleOutputCharacter`
- `GetAsyncKeyState`

These have been replaced with cross-platform `ncurses` library calls:
- `initscr()`, `endwin()` for screen management
- `mvaddch()`, `mvprintw()` for drawing
- `getch()` for input handling
- `refresh()` for screen updates

## Prerequisites

### Install ncurses
macOS doesn't come with ncurses by default. Install it using Homebrew:

```bash
brew install ncurses
```

If you don't have Homebrew installed:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## Compilation

### Option 1: Using Makefile (Recommended)
```bash
make
```

### Option 2: Manual compilation
```bash
g++ -std=c++11 -Wall -Wextra -O2 -o tetris OneLoneCoder_Tetris_macOS.cpp -lncurses
```

## Running the Game

```bash
./tetris
```

## Controls

- **Arrow Keys**: Move the tetromino piece
  - Left Arrow: Move left
  - Right Arrow: Move right  
  - Down Arrow: Move down faster
- **Z**: Rotate the piece
- **Q**: Quit the game

## Game Features

- Classic Tetris gameplay
- Score system (25 points per piece + bonus for line clears)
- Increasing difficulty (speed increases every 50 pieces)
- Line clearing animation
- Terminal size detection and adaptation

## Troubleshooting

### "ncurses.h not found" error
Make sure you've installed ncurses:
```bash
brew install ncurses
```

### Terminal size issues
The game automatically detects your terminal size. If you experience display issues, try:
1. Resize your terminal window
2. Restart the game
3. Ensure your terminal supports ncurses

### Arrow keys not working
Make sure your terminal supports keypad mode. Most modern terminals (Terminal.app, iTerm2) work fine.

## Why ncurses?

- **Cross-platform**: Works on macOS, Linux, BSD, and other Unix-like systems
- **Standard**: Part of the POSIX standard
- **Efficient**: Optimized for terminal applications
- **Well-documented**: Extensive documentation and examples available

## Original Game

This is a port of the original game from:
- **Author**: @Javidx9 (OneLoneCoder)
- **Original Video**: https://youtu.be/8OK8_tHeCIA
- **GitHub**: https://www.github.com/onelonecoder
- **License**: GNU GPLv3

## Building for Other Platforms

This code should work on any Unix-like system with ncurses:
- Linux (Ubuntu, CentOS, etc.)
- BSD variants
- macOS
- WSL (Windows Subsystem for Linux)

Just install ncurses using your package manager and compile with the same flags.
