#include <iostream>
#include <chrono>
#include <thread>
#include <curses.h>
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
	char tmp = UP;
	char oldInput = 0;

	// Create snake object with wait time in mills
	Snake snake(400);
	
	// Exit with 'q'
	while(tmp!='q'){
		// Check if nothing or wrong key was pressed, then keep previous command
		if(tmp==ERR || (tmp!=UP && tmp!=DOWN && tmp!=RIGHT && tmp!=LEFT)){
			tmp = oldInput;
		}
		else{
			oldInput = tmp;
		}
		switch(tmp){
			case UP: 
				snake.goUp();
				break;
			case DOWN:
				snake.goDown();
				break;
			case LEFT: 
				snake.goLeft();
				break;
			case RIGHT: 
				snake.goRight();
				break;
			default: // do nothing
				break;
		}
		// Get direction from input
		tmp = getch();
	}

	// Return to original screen
	snake.clearScreen();
	
	return 0;
}