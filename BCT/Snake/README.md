# Snake Game

## Team Name
TEAM GLITCH

## Team Members
- RAM KRISHNA YADAV (BCT 057)
- REMANT ROHAN JHA (BCT 059)
- UNISH SHIWAKOTI (BCT 095)
- ROHIT THAKUR (BCT 061)

## Platform
- Windows
- Developed in C using the Windows API for console manipulation

## How to Run/Use

### Prerequisites
- Windows operating system
- C compiler (e.g., GCC, MinGW, or Visual Studio)

### Compilation
`gcc snakegame.c -o snakegame.exe`

### Running the Game
1. Double-click the compiled executable or run it from the command prompt
2. From the main menu:
   - Select option 1 to view previous game records
   - Select option 2 to start a new game
3. Enter your name when prompted, or press Enter to play as "Player"

### Controls
- **W**: Move Up
- **A**: Move Left
- **S**: Move Down
- **D**: Move Right
- **X**: Quit the game

## About the Project
Snake Game is a classic arcade game implemented in C for the Windows console. Players control a snake (represented by "O" for the head and "o" for the tail) that moves around a bordered playing field. The objective is to eat fruits (represented by "*") to grow longer and achieve the highest possible score without colliding with walls or the snake's own tail.

### Features
- Interactive console-based gameplay with ASCII graphics
- Scoring system that increases by 10 points per fruit eaten
- Snake growth mechanics that increase difficulty as you progress
- High score tracking with player names
- Persistent game records stored in "game_records.txt"
- User-friendly menu interface
- Adjustable game speed via Sleep() function
- Cursor visibility management for a cleaner interface

The implementation utilizes Windows-specific functions for console manipulation, allowing precise cursor positioning and screen updates. The game loop runs at approximately 30 frames per second, providing smooth gameplay while maintaining responsiveness to player input.