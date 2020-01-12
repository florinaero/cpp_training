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
todo: Implement smooth transition for direction change
bug: Wrong transition at end of screen's right
		-> not observed on ubuntu
bug: When sense is changed on same direction then the direction's
	cange is happening at the opposite head.
bug: Direction change one after another makes symbols to dissapear. 
*/
using namespace std;

const int Snake::snake_size_ = 4;
// Snake symbol
const vector<char> Snake::snake_symbol_={'*', '*', '*', 'o'};

// Coordinates constructor
Snake::Coord::Coord(int x_coord, int y_coord):
	x_coord(x_coord),
	y_coord(y_coord)
	{}

Snake::Snake(int waitTimeMills, wchar_t head_position):
head_position_(head_position),	// Initial head position
is_reverse_(false),
width_(0),
height_(0),
wait_time_mills_(waitTimeMills)
{
	// Init screen for ncurses
	Snake::intitScreen();
	// Define coordinates of snake on vertical
	for(int i=0;i<Snake::snake_size_;i++){
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

// Check if snake is going to move in reverse by comparing
//	actual head position with the opposite direction of choosen one.
//  e.g. if actual head position is UP and 
// 	is going to move DOWN it means is going reverse 
bool Snake::startingReverse(wchar_t opposite_direction){
	if(head_position_==opposite_direction){
		return true;
	}
	return false;
}

void Snake::goDown(){
	int yCoord = 0;
	int xCoord = 0;
	int head = 0;

	// Find if snake is starting to move in reverse by comparing 
	//	actual head position with opposite of chosen direction
	// Check only if it is not in reverse
	if(!is_reverse_){
		is_reverse_ = startingReverse(UP);
		cout << "reverse" << endl;
	}

	// Update head position
	head_position_ = DOWN;

	if(is_reverse_){
		// cout << "reverse:" << is_reverse_ << endl;
	}

	auto coord_start = snake_coord_.begin();
	auto symbol = snake_symbol_.begin();
	auto coord_end = snake_coord_.end();
	auto symbol_end = snake_symbol_.end();
		
	// Get position of head of previous snake's position on x axis
	head = snake_coord_.back().first;
	// Update coordinates of symbols by increasing y coord
	for(;coord_start!=coord_end&&symbol!=symbol_end;++coord_start,++symbol){
		xCoord = coord_start->first;
		yCoord = coord_start->second;
		// Keep same x axis as before(head) going down and modify
		//	the rest of body by shifting points to head coordinate
		if(head!=xCoord){
			// Check sense of movement of snake, 1st case move to left
			if(head<xCoord){
				// Move point to left
				xCoord--; 
			}
			else{
				// Move point to right
				xCoord++;
			}
		}
		else{
			xCoord = head;
			// Move point to bottom
			yCoord += 1;
		}
#if DEBUG	
		cout << "  " << "symbol: " << *symbol;
		cout << "---head: " << head;
		cout << "  " << "coord->first: " << coord_start->first;
		cout << "  " << "yCoord: " << yCoord;
#endif
		// Check for bottom of screen and move to top 
		if(yCoord == height_-1){
			yCoord = 0;
		}
		// Store coordinates to vector
		coord_start->first = xCoord;
		coord_start->second = yCoord;
		// Move characters to next position(y,x)
		mvaddch(yCoord, xCoord, *symbol); 
	}

	refreshAndWait();
}

void Snake::goUp(){
	auto coord = snake_coord_.begin();
	auto symbol =  snake_symbol_.begin();
	int yCoord = 0;
	int xCoord = 0;
	int head = 0;

	// Update head position
	head_position_ = UP;

	// Get actual x coord in order to define column number used for
	//	vertical movement
	head = snake_coord_.back().first;
	// Update coordinates of symbols by decreasing y coord
	for(;coord!=snake_coord_.end()&&symbol!=snake_symbol_.end();++coord,++symbol){
		xCoord = coord->first;
		yCoord = coord->second;
		// Keep same x axis as before(head) going down and modify
		//	the rest of body by shifting points to head coordinate
		if(head!=xCoord){
			// Check sense of movement of snake, 1st case move to left
			if(head<xCoord){
				// Move point to left
				xCoord--; 
			}
			else{
				// Move point to right
				xCoord++;
			}
		}
		else{
			xCoord = head;
			// Move point to top
			yCoord--;
		}
#if DEBUG
		cout << "  " << "symbol: " << *symbol;
		cout << "---head: " << head;
		cout << "  " << "coord->first: " << coord->first;
		cout << "  " << "yCoord: " << yCoord;
#endif
		// Check for bottom of screen and move to top 
		if(yCoord == 0){
			yCoord = height_-1;
		}
		// Store coordinates to vector
		coord->first = xCoord;
		coord->second = yCoord;
		// Move characters to next position(y,x)
		mvaddch(yCoord, xCoord, *symbol); 
	}
	refreshAndWait();
}

void Snake::goLeft(){
	auto coord = snake_coord_.begin();
	auto symbol =  snake_symbol_.begin();
	int yCoord = 0;
	int xCoord = 0;
	int head = 0;

	// Update head position
	head_position_ = LEFT;

	// Get actual y coord in order to define column number used for
	//	horizontal movement
	head = snake_coord_.back().second;
		
	// Update coordinates of symbols by decreasing x coord
	for(;coord!=snake_coord_.end()&&symbol!=snake_symbol_.end();++coord,++symbol){
		xCoord = coord->first;
		yCoord = coord->second;
		// Keep same y axis as before(head) and modify
		//	the rest of body by shifting points to head coordinate
		if(head!=yCoord){
			// Check sense of movement of snake
			if(head<yCoord){
				yCoord--; 
			}
			else{
				yCoord++;
			}
		}
		else{
			yCoord = head;
			// Move point to chosen sense of movement
			xCoord--;
		}
#if DEBUG
		cout << "  " << "symbol: " << *symbol;
		cout << "---head: " << head;
		cout << "  " << "coord->first: " << coord->first;
		cout << "  " << "yCoord: " << yCoord;
#endif
		// Check for edge of screen and move to oposite 
		if(xCoord == 0){
			xCoord = width_-1;
		}
		// Store coordinates to vector
		coord->first = xCoord;
		coord->second = yCoord;
		// Move characters to next position(y,x)
		mvaddch(yCoord, xCoord, *symbol); 
	}
	
	refreshAndWait();
}

void Snake::goRight(){
	auto coord = snake_coord_.begin();
	auto symbol =  snake_symbol_.begin();
	int yCoord = 0;
	int xCoord = 0;
	int head = 0;

	// Update head position
	head_position_ = RIGHT;

	// Get actual y coord in order to define column number used for
	//	horizontal movement
	head = snake_coord_.back().second;
		
	// Update coordinates of symbols by decreasing x coord
	for(;coord!=snake_coord_.end()&&symbol!=snake_symbol_.end();++coord,++symbol){
		xCoord = coord->first;
		yCoord = coord->second;
		// Keep same y axis as before(head) and modify
		//	the rest of body by shifting points to head coordinate
		if(head!=yCoord){
			// Check sense of movement of snake
			if(head<yCoord){
				yCoord--; 
			}
			else{
				yCoord++;
			}
		}
		else{
			yCoord = head;
			// Move point to chosen sense of movement
			xCoord++;
		}
#if DEBUG
		// cout << "  " << "symbol: " << *symbol;
		// cout << "---head: " << head;
		// cout << "  " << "coord->first: " << coord->first;
		// cout << "  " << "yCoord: " << yCoord;
#endif
		// Check for edge of screen and move to oposite 
		if(xCoord == width_){
			xCoord = 0;
		}
		// Store coordinates to vector
		coord->first = xCoord;
		coord->second = yCoord;
		// Move characters to next position(y,x)
		mvaddch(yCoord, xCoord, *symbol); 
	}
	refreshAndWait();
}

void Snake::updateCoord(bool direction){ // horizontal=0 vertical=1
	int head = 0;
	auto coord = snake_coord_.begin();
	auto symbol =  snake_symbol_.begin();
	// Axis chosen for the next direction. e.g. up->x, left->right
	auto future_axis = coord->second; 
	auto past_axis = coord->first;

	// Get actual x coord in order to define column number used for
	//	vertical movement
	head = snake_coord_.back().first;
	// Update coordinates of symbols by decreasing y coord
	for(;coord!=snake_coord_.end()&&symbol!=snake_symbol_.end();++coord,++symbol){
		// Vertical direction 
		if(direction){
			// y axis
			future_axis = coord->second;
			// x axis 
			past_axis = coord->first;
		}
		else{	// Horizontal direction 
			// x axis
			future_axis = coord->first;
			// y axis 
			past_axis = coord->second;
		}
		// Keep same axis as before(head) changing direction and modify
		//	the rest of body by shifting points to head coordinate
		if(head!=past_axis){
			// Check sense of movement of snake
			if(head<past_axis){
				// Move point to left
				past_axis--; 
			}
			else{
				// Move point to right
				past_axis++;
			}
		}
		else{
			past_axis = head;
			// Move point to top
			future_axis--;
		}		
		if(future_axis == 0){
			future_axis = height_-1;
		}
		// Update coordinates for vertical and horizontal direction
		if(direction){
			// y axis
			coord->second = future_axis;
			// x axis 
			coord->first = past_axis;
		}
		else{
			// x axis
			coord->first = future_axis;
			// y axis 
			coord->second = past_axis;
		}
		// Move characters to next position(y,x)
		mvaddch(coord->second, coord->first, *symbol); 
	}
	refreshAndWait();
}
