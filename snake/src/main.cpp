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
	wchar_t actual_direction = RIGHT;
	char key_start = ERR;
	char old_direction = 0;
	bool change_flag = false;

		// Create snake object with wait time in mills and initial direction
	Snake snake(500, actual_direction);
	
	// Exit with STOP_KEY
	while(actual_direction!=STOP_KEY){
		// Check if no key or wrong key was pressed, then keep previous command
		if(actual_direction==ERR || (actual_direction!=UP && actual_direction!=DOWN && 
										actual_direction!=RIGHT && actual_direction!=LEFT)){
			actual_direction = old_direction;
		}
		
		switch(actual_direction){
			case UP: 
				if(old_direction!=DOWN){
					snake.goUp();
					change_flag = true;
				}
				else{
					change_flag = false;
				}
				break;
			case DOWN:
				if(old_direction!=UP){
					snake.goDown();
					change_flag = true;
				}
				else{
					change_flag = false;
				}
				break;
			case LEFT: 
				if(old_direction!=RIGHT){
					snake.goLeft();
					change_flag = true;
				}
				else{
					change_flag = false;
				}
				break;
			case RIGHT: 
				if(old_direction!=LEFT){
					snake.goRight();
					change_flag = true;
				}
				else{
					change_flag = false;
				}
				break;
			default: // do nothing
				break;
		}
		if(change_flag){
			// Store direction that was selected 
			old_direction = actual_direction;
		}	
		// Get direction from input
		actual_direction = getch();
	}

	// Return to original screen
	snake.clearScreen();
	
	return 0;
}