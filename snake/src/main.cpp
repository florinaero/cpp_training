#include <iostream>
#include <chrono>
#include <thread>
#include "snake.hpp"

using namespace std;

int main(){
	const int size = 0;
	const char UP = 'w';
	const char DOWN = 's';
	const char LEFT = 'a';
	const char RIGHT = 'd';
	int width = 0;
	int height = 0;
	char tmp = 0;

	// Create snake object 
	Snake snake;

	snake.intitScreen();

	// Return to original screen
	snake.clearScreen();
	
	return 0;
}