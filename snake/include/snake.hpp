#include <vector>
#include <utility>
using namespace std;

// Define keys(inline constexpr available only for c++17) 
inline constexpr wchar_t UP = 'w';
inline constexpr wchar_t DOWN = 's';
inline constexpr wchar_t LEFT = 'a';
inline constexpr wchar_t RIGHT = 'd';
inline constexpr wchar_t STOP_KEY = 'q';

class Snake{
private:
	struct Coord{
		int x_coord;
		int y_coord;
		Coord(int x_coord, int y_coord);
	};
	wchar_t head_position_;
public:
	int width_;
	int height_;
	int wait_time_mills_;
	
	// Coordinates of snake on screen
	vector<pair<int,int> > snake_coord_;
	// Snake symbol
	static const vector<char> snake_symbol_;
	// Origin point 
	static const int m_originPoint;

	// Ctor
	Snake(int waitTimeMills, wchar_t head_position);

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
	// Update position of chars on screen 
	void moveChar(int yCoord, int xCoord, char symbol); 
	void goDown();
	void goUp();
	void goLeft();
	void goRight();
};