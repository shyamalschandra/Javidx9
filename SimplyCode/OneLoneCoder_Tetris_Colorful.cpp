/*
	OneLoneCoder.com - Command Line Tetris (Colorful macOS Version)
	"Put Your Money Where Your Mouth Is" - @Javidx9
	
	License
	~~~~~~~
	Copyright (C) 2018  Javidx9
	This program comes with ABSOLUTELY NO WARRANTY.
	This is free software, and you are welcome to redistribute it
	under certain conditions; See license for details. 
	Original works located at:
	https://www.github.com/onelonecoder
	https://www.onelonecoder.com
	https://www.youtube.com/javidx9

	GNU GPLv3
	https://github.com/OneLoneCoder/videos/blob/master/LICENSE

	From Javidx9 :)
	~~~~~~~~~~~~~~~
	Hello! Ultimately I don't care what you use this for. It's intended to be 
	educational, and perhaps to the oddly minded - a little bit of fun. 
	Please hack this, change it and use it in any way you see fit. You acknowledge 
	that I am not responsible for anything bad that happens as a result of 
	your actions. However this code is protected by GNU GPLv3, see the license in the
	github repo. This means you must attribute me if you use it. You can view this
	license here: https://github.com/OneLoneCoder/videos/blob/master/LICENSE
	Cheers!
	
	Background
	~~~~~~~~~~
	I made a video "8-Bits of advice for new programmers" (https://youtu.be/vVRCJ52g5m4)
	and suggested that building a tetris clone instead of Dark Sould IV might be a better 
	approach to learning to code. Tetris is nice as it makes you think about algorithms. 
	
	Controls are Arrow keys Left, Right & Down. Use Z to rotate the piece. 
	You score 25pts per tetronimo, and 2^(number of lines)*100 when you get lines.
	
	Future Modifications
	~~~~~~~~~~~~~~~~~~~~
	1) Show next block and line counter
	
	Author
	~~~~~~
	Twitter: @javidx9
	Blog: www.onelonecoder.com
	
	Video:
	~~~~~~
	https://youtu.be/8OK8_tHeCIA
	
	Last Updated: 30/03/2017
	
	macOS Colorful Port: Enhanced with colors and emojis
*/

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <random>
using namespace std;

// ncurses headers for terminal manipulation
#include <ncurses.h>

int nScreenWidth = 80;			// Console Screen Size X (columns)
int nScreenHeight = 30;			// Console Screen Size Y (rows)
wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char *pField = nullptr;

// Color definitions for different tetromino pieces
const int PIECE_COLORS[7] = {
    1,  // I-piece: Blue
    2,  // O-piece: Yellow  
    3,  // T-piece: Magenta
    4,  // S-piece: Green
    5,  // Z-piece: Red
    6,  // J-piece: Cyan
    7   // L-piece: White
};

// Block characters for visual representation
const char* BLOCK_CHARS[8] = {
    " ",      // Empty space
    "#",      // I-piece (blue)
    "#",      // O-piece (yellow)
    "#",      // T-piece (magenta)
    "#",      // S-piece (green)
    "#",      // Z-piece (red)
    "#",      // J-piece (cyan)
    "#"       // L-piece (white)
};

// Emoji representations for different pieces
const char* PIECE_EMOJIS[7] = {
    "🔵",  // I-piece (blue)
    "🟡",  // O-piece (yellow)
    "🟣",  // T-piece (magenta)
    "🟢",  // S-piece (green)
    "🔴",  // Z-piece (red)
    "🔷",  // J-piece (cyan)
    "⚪"   // L-piece (white)
};

// Initialize ncurses colors
void initColors() {
    if (has_colors()) {
        start_color();
        use_default_colors();
        
        // Define color pairs for different pieces
        init_pair(1, COLOR_BLUE, COLOR_BLUE);      // I-piece
        init_pair(2, COLOR_YELLOW, COLOR_YELLOW);  // O-piece
        init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA); // T-piece
        init_pair(4, COLOR_GREEN, COLOR_GREEN);    // S-piece
        init_pair(5, COLOR_RED, COLOR_RED);        // Z-piece
        init_pair(6, COLOR_CYAN, COLOR_CYAN);      // J-piece
        init_pair(7, COLOR_WHITE, COLOR_WHITE);    // L-piece
        
        // Special colors
        init_pair(8, COLOR_WHITE, COLOR_BLACK);    // Text
        init_pair(9, COLOR_BLACK, COLOR_WHITE);    // Border
        init_pair(10, COLOR_YELLOW, COLOR_BLACK);  // Score
        init_pair(11, COLOR_GREEN, COLOR_BLACK);   // Instructions
    }
}

int Rotate(int px, int py, int r)
{
	int pi = 0;
	switch (r % 4)
	{
	case 0: // 0 degrees			// 0  1  2  3
		pi = py * 4 + px;			// 4  5  6  7
		break;						// 8  9 10 11
									//12 13 14 15

	case 1: // 90 degrees			//12  8  4  0
		pi = 12 + py - (px * 4);	//13  9  5  1
		break;						//14 10  6  2
									//15 11  7  3

	case 2: // 180 degrees			//15 14 13 12
		pi = 15 - (py * 4) - px;	//11 10  9  8
		break;						// 7  6  5  4
									// 3  2  1  0

	case 3: // 270 degrees			// 3  7 11 15
		pi = 3 - py + (px * 4);		// 2  6 10 14
		break;						// 1  5  9 13
	}								// 0  4  8 12

	return pi;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
	// All Field cells >0 are occupied
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
		{
			// Get index into piece
			int pi = Rotate(px, py, nRotation);

			// Get index into field
			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

			// Check that test is in bounds. Note out of bounds does
			// not necessarily mean a fail, as the long vertical piece
			// can have cells that lie outside the boundary, so we'll
			// just ignore them
			if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
			{
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
				{
					// In Bounds so do collision check
					if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
						return false; // fail on first hit
				}
			}
		}

	return true;
}

// Draw a colorful border around the game area
void drawBorder() {
    attron(COLOR_PAIR(9));
    // Top border
    for (int x = 1; x < nFieldWidth + 1; x++) {
        mvaddch(1, x + 1, '-');
    }
    // Bottom border
    for (int x = 1; x < nFieldWidth + 1; x++) {
        mvaddch(nFieldHeight + 2, x + 1, '-');
    }
    // Left border
    for (int y = 1; y < nFieldHeight + 2; y++) {
        mvaddch(y + 1, 1, '|');
    }
    // Right border
    for (int y = 1; y < nFieldHeight + 2; y++) {
        mvaddch(y + 1, nFieldWidth + 2, '|');
    }
    // Corners
    mvaddch(1, 1, '+');
    mvaddch(1, nFieldWidth + 2, '+');
    mvaddch(nFieldHeight + 2, 1, '+');
    mvaddch(nFieldHeight + 2, nFieldWidth + 2, '+');
    attroff(COLOR_PAIR(9));
}

// Draw the next piece preview
void drawNextPiece(int nextPiece) {
    attron(COLOR_PAIR(8));
    mvprintw(2, nFieldWidth + 6, "NEXT PIECE:");
    attroff(COLOR_PAIR(8));
    
    // Draw the next piece in a small box
    for (int px = 0; px < 4; px++) {
        for (int py = 0; py < 4; py++) {
            if (tetromino[nextPiece][py * 4 + px] != L'.') {
                attron(COLOR_PAIR(PIECE_COLORS[nextPiece]));
                mvaddch(4 + py, nFieldWidth + 8 + px, '#');
                attroff(COLOR_PAIR(PIECE_COLORS[nextPiece]));
            }
        }
    }
    
    // Show emoji representation
    attron(COLOR_PAIR(8));
    mvprintw(9, nFieldWidth + 8, "Piece: %s", PIECE_EMOJIS[nextPiece]);
    attroff(COLOR_PAIR(8));
}

// Draw statistics panel
void drawStats(int score, int lines, int level) {
    attron(COLOR_PAIR(8));
    mvprintw(12, nFieldWidth + 6, "STATISTICS:");
    attroff(COLOR_PAIR(8));
    
    attron(COLOR_PAIR(10));
    mvprintw(14, nFieldWidth + 6, "Score: %8d", score);
    mvprintw(15, nFieldWidth + 6, "Lines: %8d", lines);
    mvprintw(16, nFieldWidth + 6, "Level: %8d", level);
    attroff(COLOR_PAIR(10));
}

int main()
{
	// Initialize ncurses
	initscr();
	cbreak();           // Line buffering disabled
	noecho();           // Don't echo input
	keypad(stdscr, TRUE); // Enable keypad mode for arrow keys
	curs_set(0);        // Hide cursor
	timeout(0);         // Non-blocking input
	
	// Initialize colors
	initColors();
	
	// Get terminal size
	getmaxyx(stdscr, nScreenHeight, nScreenWidth);
	
	// Ensure minimum size
	if (nScreenWidth < 80) nScreenWidth = 80;
	if (nScreenHeight < 30) nScreenHeight = 30;
	
	tetromino[0].append(L"..X...X...X...X."); // Tetronimos 4x4
	tetromino[1].append(L"..X..XX...X.....");
	tetromino[2].append(L".....XX..XX.....");
	tetromino[3].append(L"..X..XX..X......");
	tetromino[4].append(L".X...XX...X.....");
	tetromino[5].append(L".X...X...XX.....");
	tetromino[6].append(L"..X...X..XX.....");

	pField = new unsigned char[nFieldWidth*nFieldHeight]; // Create play field buffer
	for (int x = 0; x < nFieldWidth; x++) // Board Boundary
		for (int y = 0; y < nFieldHeight; y++)
			pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

	// Game Logic
	bool bKey[4];
	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;
	int nSpeed = 20;
	int nSpeedCount = 0;
	bool bForceDown = false;
	bool bRotateHold = true;
	int nPieceCount = 0;
	int nScore = 0;
	int nLines = 0;
	int nLevel = 1;
	vector<int> vLines;
	bool bGameOver = false;
	
	// Random number generator for next piece
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 6);
	int nNextPiece = dis(gen);

	while (!bGameOver) // Main Loop
	{
		// Timing =======================
		this_thread::sleep_for(chrono::milliseconds(50)); // Small Step = 1 Game Tick
		nSpeedCount++;
		bForceDown = (nSpeedCount == nSpeed);

		// Input ========================
		// Clear key states
		for (int k = 0; k < 4; k++) bKey[k] = false;
		
		// Check for key presses (non-blocking)
		int ch = getch();
		if (ch != ERR) {
			switch (ch) {
				case KEY_RIGHT:  bKey[0] = true; break; // Right arrow
				case KEY_LEFT:   bKey[1] = true; break; // Left arrow
				case KEY_DOWN:   bKey[2] = true; break; // Down arrow
				case 'z':        bKey[3] = true; break; // Z key
				case 'Z':        bKey[3] = true; break; // Z key (uppercase)
				case 'q':        bGameOver = true; break; // Q to quit
				case 'Q':        bGameOver = true; break; // Q to quit (uppercase)
			}
		}
		
		// Game Logic ===================

		// Handle player movement
		nCurrentX += (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
		nCurrentX -= (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;		
		nCurrentY += (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;

		// Rotate, but latch to stop wild spinning
		if (bKey[3])
		{
			nCurrentRotation += (bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
			bRotateHold = false;
		}
		else
			bRotateHold = true;

		// Force the piece down the playfield if it's time
		if (bForceDown)
		{
			// Update difficulty every 50 pieces
			nSpeedCount = 0;
			nPieceCount++;
			if (nPieceCount % 50 == 0) {
				if (nSpeed >= 10) nSpeed--;
				nLevel++;
			}
			
			// Test if piece can be moved down
			if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
				nCurrentY++; // It can, so do it!
			else
			{
				// It can't! Lock the piece in place
				for (int px = 0; px < 4; px++)
					for (int py = 0; py < 4; py++)
						if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
							pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;

				// Check for lines
				for (int py = 0; py < 4; py++)
					if(nCurrentY + py < nFieldHeight - 1)
					{
						bool bLine = true;
						for (int px = 1; px < nFieldWidth - 1; px++)
							bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;

						if (bLine)
						{
							// Remove Line, set to =
							for (int px = 1; px < nFieldWidth - 1; px++)
								pField[(nCurrentY + py) * nFieldWidth + px] = 8;
							vLines.push_back(nCurrentY + py);
							nLines++;
						}						
					}

				nScore += 25;
				if(!vLines.empty())	nScore += (1 << vLines.size()) * 100;

				// Pick New Piece
				nCurrentX = nFieldWidth / 2;
				nCurrentY = 0;
				nCurrentRotation = 0;
				nCurrentPiece = nNextPiece;
				nNextPiece = dis(gen);

				// If piece does not fit straight away, game over!
				bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
			}
		}

		// Display ======================
		clear(); // Clear the screen

		// Draw border
		drawBorder();

		// Draw Field with colors
		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
			{
				unsigned char fieldValue = pField[y*nFieldWidth + x];
				if (fieldValue == 9) {
					// Border
					attron(COLOR_PAIR(9));
					mvaddch(y + 2, x + 2, '#');
					attroff(COLOR_PAIR(9));
				} else if (fieldValue == 8) {
					// Line to be cleared
					attron(COLOR_PAIR(10));
					mvaddch(y + 2, x + 2, '#');
					attroff(COLOR_PAIR(10));
				} else if (fieldValue > 0) {
					// Tetromino piece
					attron(COLOR_PAIR(PIECE_COLORS[fieldValue - 1]));
					mvaddch(y + 2, x + 2, '#');
					attroff(COLOR_PAIR(PIECE_COLORS[fieldValue - 1]));
				}
			}

		// Draw Current Piece
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
				{
					attron(COLOR_PAIR(PIECE_COLORS[nCurrentPiece]));
					mvaddch(nCurrentY + py + 2, nCurrentX + px + 2, '#');
					attroff(COLOR_PAIR(PIECE_COLORS[nCurrentPiece]));
				}

		// Draw UI elements
		drawNextPiece(nNextPiece);
		drawStats(nScore, nLines, nLevel);
		
		// Draw title
		attron(COLOR_PAIR(8));
		mvprintw(0, 2, "🎮 COLORFUL TETRIS 🎮");
		attroff(COLOR_PAIR(8));
		
		// Draw instructions
		attron(COLOR_PAIR(11));
		mvprintw(nFieldHeight + 4, 2, "🎯 Controls: Arrow Keys = Move, Z = Rotate, Q = Quit");
		mvprintw(nFieldHeight + 5, 2, "🎨 Each piece has its own color and emoji!");
		attroff(COLOR_PAIR(11));
		
		// Refresh the screen
		refresh();

		// Animate Line Completion
		if (!vLines.empty())
		{
			// Display Frame (cheekily to draw lines)
			refresh();
			this_thread::sleep_for(chrono::milliseconds(400)); // Delay a bit

			for (auto &v : vLines)
				for (int px = 1; px < nFieldWidth - 1; px++)
				{
					for (int py = v; py > 0; py--)
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
					pField[px] = 0;
				}

			vLines.clear();
		}
	}

	// Clean up ncurses
	endwin();
	
	// Game Over
	cout << "🎮 Game Over!! 🎮" << endl;
	cout << "🏆 Final Score: " << nScore << endl;
	cout << "📊 Lines Cleared: " << nLines << endl;
	cout << "⭐ Level Reached: " << nLevel << endl;
	cout << "Press Enter to continue..." << endl;
	cin.get();
	
	// Clean up memory
	delete[] pField;
	
	return 0;
}
