#define DEBUG 0

#include <iostream>
#include <chrono>
#include <thread>
#include <curses.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "snake.hpp"

/*
todo: Remove duplicated lines of changing direction func
todo: Remove fixed dimmension of snake_symbol_
todo: Define window size from begining
todo: Check why arrows are not working(keypad())
Solved: todo: Implement smooth transition for direction change
Solved: bug: Wrong transition at end of screen's right
		-> not observed on ubuntu
Solved: bug: When sense is changed on same direction then the direction's
		change is happening at the opposite head.
Solved: bug: Direction change one after another makes symbols to dissapear. 
*/
using namespace std;

// Snake symbol
// const vector<char> Snake::snake_symbol_={'0', '1', '2', '3'};
const vector<char> Snake::snake_symbol_={'*', '*', '*','*', '*', '*', 'o'};

// Coordinates constructor
Snake::Coord::Coord(int x_coord, int y_coord):
	x_coord(x_coord),
	y_coord(y_coord)
	{}

Snake::Snake(int waitTimeMills, wchar_t head_position):
head_position_(head_position),
width_(0),
height_(0),
wait_time_mills_(waitTimeMills)
{
	// Init screen for ncurses
	Snake::intitScreen();
	// Define coordinates of snake on vertical
	for(size_t i=0;i<snake_symbol_.size();i++){
		// Start from middle of window
		snake_coord_.push_back(make_pair(width_/2, height_/2+i));
	} 
}

void Snake::intitScreen(){
	// Initialize screen 
	initscr();
	// Disables buffer and makes chars to immediately appear on screen 
	cbreak();
	// Disable printing input on screen 
	noecho();
	// getch() not waits for input, it returns ERR if key is not ready
	nodelay(stdscr,true);
	// Enable special keys in order to use arrows; todo: is not working 
	keypad(stdscr, true);
	// Hide cursor
	curs_set(0);
	// Get size of terminal window
	getScreenSize();
}

void Snake::clearScreen(){
	// Return to original window
	endwin();
}

void Snake::getScreenSize(){
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	height_ = w.ws_row;
	width_ = w.ws_col;
	// cout << "width: "<<width_ << "  height: \n" << height_;
}

void Snake::refreshAndWait(){
	// Refresh screen 
	refresh();
	// Wait time
	this_thread::sleep_for(chrono::milliseconds(wait_time_mills_));
	// Clear screen
	clear();
}

void Snake::moveChar(int yCoord, int xCoord, char symbol){
	mvaddch(yCoord, xCoord, symbol);
}

void Snake::goDown(){
	bool first = true;
	auto temp = snake_coord_.at(0);

	// Update head position
	head_position_ = UP;

	// Update coordinates of symbols by changing head's coord and copying coordinates
	//	of symbols from tail to head, follow head.
	for(int i=snake_coord_.size()-1;i>=0;i--){
		auto coord = snake_coord_.at(i);
		// Change coordinate just for head, for the rest copy the previous coord
		// 	of head, head-1
		if(first){
			first = false;
			// Store previous value before changing coord
			temp = snake_coord_.at(i);
			// Decrease y coordinate to move to top of screen
			coord.second++;
			// Check for bottom of screen and move to top 
			if(coord.second == height_){
				coord.second = 0;
			}	
		}
		else{
			// Assign previous coordinates
			coord = temp;
			temp = snake_coord_.at(i);
		}
		// Store new coordinates
		snake_coord_.at(i) = coord;
		moveChar(coord.second, coord.first, snake_symbol_.at(i)); 

	}
	refreshAndWait();
}

void Snake::goUp(){
	bool first = true;
	auto temp = snake_coord_.at(0);

	// Update head position
	head_position_ = UP;

	// Update coordinates of symbols by changing head's coord and copying coordinates
	//	of symbols from tail to head, follow head.
	for(int i=snake_coord_.size()-1;i>=0;i--){
		auto coord = snake_coord_.at(i);
		// Change coordinate just for head, for the rest copy the previous coord
		// 	of head, head-1
		if(first){
			first = false;
			// Store previous value before changing coord
			temp = snake_coord_.at(i);
			// Decrease y coordinate to move to top of screen
			coord.second--;
			// Check for bottom of screen and move to top 
			if(coord.second == 0){
				coord.second = height_ - 1;
			}	
		}
		else{
			// Assign previous coordinates
			coord = temp;
			temp = snake_coord_.at(i);
		}
		// Store new coordinates
		snake_coord_.at(i) = coord;
		moveChar(coord.second, coord.first, snake_symbol_.at(i)); 
	}
	refreshAndWait();
}

void Snake::goLeft(){
	bool first = true;
	auto temp = snake_coord_.at(0);

	// Update head position
	head_position_ = LEFT;

	// Update coordinates of symbols by changing head's coord and copying coordinates
	//	of symbols from tail to head, follow head.
	for(int i=snake_coord_.size()-1;i>=0;i--){
		auto coord = snake_coord_.at(i);
		// Change coordinate just for head, for the rest copy the previous coord
		// 	of head, head-1
		if(first){
			first = false;
			// Store previous value before changing coord
			temp = snake_coord_.at(i);
			// Decrease y coordinate to move to top of screen
			coord.first--;
			// Check for bottom of screen and move to top 
			if(coord.first == 0){
				coord.first = width_ - 1;
			}	
		}
		else{
			// Assign previous coordinates
			coord = temp;
			temp = snake_coord_.at(i);
		}
		// Store new coordinates
		snake_coord_.at(i) = coord;
		moveChar(coord.second, coord.first, snake_symbol_.at(i)); 
	}
	refreshAndWait();
}

void Snake::goRight(){
	bool first = true;
	auto temp = snake_coord_.at(0);

	// Update head position
	head_position_ = RIGHT;

	// Update coordinates of symbols by changing head's coord and copying coordinates
	//	of symbols from tail to head, follow head.
	for(int i=snake_coord_.size()-1;i>=0;i--){
		auto coord = snake_coord_.at(i);
		// Change coordinate just for head, for the rest copy the previous coord
		// 	of head, head-1
		if(first){
			first = false;
			// Store previous value before changing coord
			temp = snake_coord_.at(i);
			// Decrease y coordinate to move to top of screen
			coord.first++;
			// Check for bottom of screen and move to top 
			if(coord.first == width_){
				coord.first = 0;
			}	
		}
		else{
			// Assign previous coordinates
			coord = temp;
			temp = snake_coord_.at(i);
		}
		// Store new coordinates
		snake_coord_.at(i) = coord;
		
		moveChar(coord.second, coord.first, snake_symbol_.at(i)); 


	}
	refreshAndWait();
}
