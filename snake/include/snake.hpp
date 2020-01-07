#include <vector>
#include <utility>
using namespace std;

class Snake{
public:
	int m_width;
	int m_height;
	static const int m_snakeSize;
	// Coordinates of snake on screen
	vector<pair<int,int>> m_snakeCoord;
	// Snake symbol
	static const vector<char> m_snakeSymbol;
	// Origin point 
	static const int m_originPoint;

	// Ctor
	Snake();

	// Intialize screen using curses
	void intitScreen();
	// Return to original screen
	void clearScreen();
	// Define start position of snake on screen 
	void defineStartPosition();

	// Get window size 
	void getScreenSize();

	void goDown();
	void goUp();
	void goLeft();
	void goRight();

};