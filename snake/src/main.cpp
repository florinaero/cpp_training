#include <iostream>
#include <chrono>
#include <thread>
#include <curses.h>
#include "snake.hpp"

using namespace std;

int main(){
	const int size = 0;

	int width = 0;
	int height = 0;
	wchar_t initial_direction = UP;
	char key_start = ERR;
	char oldInput = 0;

		// Create snake object with wait time in mills and initial direction
	Snake snake(400, initial_direction);
	
	// Exit with STOP_KEY
	while(initial_direction!=STOP_KEY){
		// Check if nothing or wrong key was pressed, then keep previous command
		if(initial_direction==ERR || (initial_direction!=UP && initial_direction!=DOWN && initial_direction!=RIGHT && initial_direction!=LEFT)){
			initial_direction = oldInput;
		}
		else{
			oldInput = initial_direction;
		}
		switch(initial_direction){
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
		initial_direction = getch();
	}

	// Return to original screen
	snake.clearScreen();
	
	return 0;
}