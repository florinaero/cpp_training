#include <vector>
#include <utility>
using namespace std;

class Snake{
public:
	int m_width;
	int m_height;
	int m_waitTimeMills;
	static const int m_snakeSize;
	// Coordinates of snake on screen
	vector<pair<int,int> > m_snakeCoord;
	// Snake symbol
	static const vector<char> m_snakeSymbol;
	// Origin point 
	static const int m_originPoint;

	// Ctor
	Snake(int waitTimeMills);

	// Intialize screen using curses
	void intitScreen();
	// Return to original screen
	void clearScreen();
	// Define start position of snake on screen 
	void defineStartPosition();
	// Get window size 
	void getScreenSize();
	// Refresh screen and wait time 
	void refreshAndWait();
	void goDown();
	void goUp();
	void goLeft();
	void goRight();

};