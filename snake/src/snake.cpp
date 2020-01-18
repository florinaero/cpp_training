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
		snake_coord_.push_back(Coord(width_/2, height_/2+i));
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

void Snake::updateCoord(int new_xcoord, int new_ycoord){
	// Create a copy of head at the end of deque
	snake_coord_.emplace_back(snake_coord_.front());
	// Change y coordinate of the new head
	snake_coord_.back().y_coord = new_ycoord;
	// Change x coordinate of the new head
	snake_coord_.back().x_coord = new_xcoord;
	// Remove snake's tail
	snake_coord_.pop_front();

	// Update coordinates of symbols by changing head's coord and copying coordinates
	//	of symbols from tail to head, follow head.
	for(int i=snake_coord_.size()-1;i>=0;i--){
		moveChar(snake_coord_.at(i).y_coord, snake_coord_.at(i).x_coord, snake_symbol_.at(i)); 

	}
	refreshAndWait();
}

void Snake::goDown(){
	int new_ycoord = 0;
	// Update head position
	head_position_ = DOWN;

	new_ycoord = snake_coord_.back().y_coord;
	new_ycoord++;
	if(new_ycoord==height_){
		new_ycoord = 0;
	}
	
	updateCoord(snake_coord_.back().x_coord, new_ycoord);
}

void Snake::goUp(){
	int new_ycoord = 0;
	// Update head position
	head_position_ = UP;

	new_ycoord = snake_coord_.back().y_coord;
	new_ycoord--;
	if(new_ycoord==0){
		new_ycoord = height_ - 1;
	}
	
	updateCoord(snake_coord_.back().x_coord, new_ycoord);
}

void Snake::goLeft(){
	int new_xcoord = 0;
	// Update head position
	head_position_ = LEFT;

	new_xcoord = snake_coord_.back().x_coord;
	new_xcoord--;
	if(new_xcoord==0){
		new_xcoord = width_ - 1;
	}
	
	updateCoord(new_xcoord, snake_coord_.back().y_coord);
}

void Snake::goRight(){

	int new_xcoord = 0;
	// Update head position
	head_position_ = RIGHT;

	new_xcoord = snake_coord_.back().x_coord;
	new_xcoord++;
	if(new_xcoord==width_){
		new_xcoord = 0;
	}
	
	updateCoord(new_xcoord, snake_coord_.back().y_coord);
}
