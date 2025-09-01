# 🎮 Colorful Tetris Game - macOS Enhanced Version

This is a **visually enhanced** macOS port of the original Windows console Tetris game by OneLoneCoder (@Javidx9), featuring **colors**, **Unicode blocks**, and **emojis**!

## ✨ What's New in the Colorful Version?

### 🎨 **Visual Enhancements**
- **7 distinct colors** for each tetromino piece type
- **Unicode block characters** (█) instead of ASCII letters
- **Beautiful borders** with Unicode box-drawing characters
- **Color-coded UI elements** for better readability

### 🎯 **Gameplay Improvements**
- **Next piece preview** with color coding
- **Enhanced statistics panel** showing score, lines, and level
- **Better visual feedback** for line clearing
- **Emoji representations** for each piece type

### 🔧 **Technical Features**
- **Full color support** using ncurses color pairs
- **Unicode support** for modern terminal emulators
- **Responsive design** that adapts to terminal size
- **Enhanced random number generation** for piece selection

## 🎲 Piece Types & Colors

| Piece | Shape | Color | Emoji | Description |
|-------|-------|-------|-------|-------------|
| I | ████ | 🔵 Blue | Long straight piece |
| O | ██<br>██ | 🟡 Yellow | Square piece |
| T |  █<br>███ | 🟣 Magenta | T-shaped piece |
| S |  ██<br> ██ | 🟢 Green | S-shaped piece |
| Z | ██<br>  ██ | 🔴 Red | Z-shaped piece |
| J | █<br>███ | 🔷 Cyan | J-shaped piece |
| L |   █<br>███ | ⚪ White | L-shaped piece |

## 🚀 Getting Started

### Prerequisites
```bash
# Install ncurses (required for colors and terminal manipulation)
brew install ncurses
```

### Compilation
```bash
# Build both versions
make

# Or build just the colorful version
make tetris-colorful
```

### Running
```bash
# Run the colorful version
./tetris-colorful

# Or use the make target
make run-colorful
```

## 🎮 Controls

- **Arrow Keys**: Move the tetromino piece
  - ⬅️ Left Arrow: Move left
  - ➡️ Right Arrow: Move right  
  - ⬇️ Down Arrow: Move down faster
- **Z**: Rotate the piece
- **Q**: Quit the game

## 🏆 Game Features

- **Classic Tetris gameplay** with modern visual enhancements
- **Color-coded scoring system** (25 points per piece + bonus for line clears)
- **Progressive difficulty** (speed increases every 50 pieces)
- **Animated line clearing** with visual feedback
- **Real-time statistics** display
- **Next piece preview** for strategic planning
- **Level progression** system

## 🎨 Color Scheme

The game uses a carefully designed color palette:
- **Piece colors**: Each tetromino has its own distinct color
- **UI colors**: 
  - White text on black background for readability
  - Yellow highlights for important information
  - Green for instructions and helpful text
  - Black borders with white backgrounds for contrast

## 🔧 Technical Details

### Unicode Support
- Uses Unicode block characters (█) for solid pieces
- Box-drawing characters for borders (╔╗╚╝═║)
- Emoji support for piece identification

### Color Implementation
- **7 color pairs** for different piece types
- **4 additional pairs** for UI elements
- Automatic fallback for terminals without color support

### Performance Optimizations
- Efficient screen refresh using ncurses
- Minimal memory allocation
- Optimized drawing routines

## 🐛 Troubleshooting

### Colors not displaying
- Ensure your terminal supports 256 colors
- Try using iTerm2 or Terminal.app on macOS
- Check that ncurses was compiled with color support

### Unicode characters not showing
- Use a modern terminal emulator
- Ensure your terminal font supports Unicode
- Try setting `LC_ALL=en_US.UTF-8` in your shell

### Game runs slowly
- Reduce terminal window size
- Close other resource-intensive applications
- Ensure you're using the latest ncurses version

## 🌟 Why This Version?

The colorful version transforms the basic ASCII Tetris into a **modern, engaging experience**:

1. **Visual Appeal**: Colors and Unicode make the game much more attractive
2. **Better UX**: Clear visual feedback and improved readability
3. **Modern Standards**: Uses contemporary terminal capabilities
4. **Educational Value**: Demonstrates advanced ncurses features
5. **Cross-Platform**: Works on any Unix-like system with color support

## 🔄 Comparison with Basic Version

| Feature | Basic Version | Colorful Version |
|---------|---------------|------------------|
| Colors | ❌ Monochrome | ✅ Full color support |
| Characters | ASCII letters | Unicode blocks (█) |
| Borders | Simple lines | Beautiful Unicode borders |
| Next piece | ❌ Not shown | ✅ Color-coded preview |
| Statistics | Basic score | Score + Lines + Level |
| Visual feedback | Minimal | Enhanced with colors |
| Emojis | ❌ None | ✅ Piece identification |

## 🚀 Future Enhancements

Potential improvements for future versions:
- **Sound effects** using terminal bell or external audio
- **Particle effects** for line clearing
- **High score persistence** across game sessions
- **Custom color themes** for different preferences
- **Animation sequences** for special events

## 📚 Original Game

This is an enhanced port of the original game from:
- **Author**: @Javidx9 (OneLoneCoder)
- **Original Video**: https://youtu.be/8OK8_tHeCIA
- **GitHub**: https://www.github.com/onelonecoder
- **License**: GNU GPLv3

## 🤝 Contributing

Feel free to enhance this version further! Some ideas:
- Add more color themes
- Implement additional game modes
- Create custom piece designs
- Add multiplayer support
- Optimize performance

---

**Enjoy the colorful Tetris experience! 🎮✨**
