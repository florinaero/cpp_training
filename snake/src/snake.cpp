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
head_position_(head_position),
width_(0),
height_(0),
wait_time_mills_(waitTimeMills)
{
	// Init screen for ncurses
	Snake::intitScreen();
	// Define coordinates of snake on vertical
	for(int i=0;i<Snake::snake_size_;i++){
		// Start from middle of window
		m_snakeCoord.push_back(make_pair(width_/2, height_/2+i));
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

void Snake::moveChar(int yCoord, int xCoord, wchar_t symbol){
	mvaddch(yCoord, xCoord, symbol);
}

void Snake::goDown(){
	auto coord = m_snakeCoord.begin();
	auto symbol =  snake_symbol_.begin();
	int yCoord = 0;
	int xCoord = 0;
	int head = 0;

	// Update head position
	head_position_ = DOWN;
	// Get position of head of previous snake's position on x axis
	head = m_snakeCoord.back().first;
	// Update coordinates of symbols by increasing y coord
	for(;coord!=m_snakeCoord.end()&&symbol!=snake_symbol_.end();++coord,++symbol){
		xCoord = coord->first;
		yCoord = coord->second;
		// Keep same x axis as before(head) going down and modify
		//	the rest of body by shifting points to head coordinate
		if(head!=xCoord){
			// Check sense of movement of snake, 1st case move to left
			if(head<xCoord){
				xCoord--;	// Move point to left
			}
			else{				
				xCoord++;	// Move point to right
			}
		}
		else{
			xCoord = head;			
			yCoord ++;	// Move point to bottom
		}
		// Check for bottom of screen and move to top 
		if(yCoord == height_-1){
			yCoord = 0;
		}
		// Store coordinates to vector
		coord->first = xCoord;
		coord->second = yCoord;
		// Move characters to next position(y,x)
		moveChar(yCoord, xCoord, *symbol); 
	}
	refreshAndWait();
}

void Snake::goUp(){
	auto coord = m_snakeCoord.begin();
	auto symbol =  snake_symbol_.begin();
	int yCoord = 0;
	int xCoord = 0;
	int head = 0;

	// Update head position
	head_position_ = UP;
	// Get actual x coord in order to define column number used for
	//	vertical movement
	head = m_snakeCoord.back().first;
	// Update coordinates of symbols by decreasing y coord
	for(;coord!=m_snakeCoord.end()&&symbol!=snake_symbol_.end();++coord,++symbol){
		xCoord = coord->first;
		yCoord = coord->second;
		// Keep X coordinate of head before going up and modify
		//	the rest of body by shifting points to head coordinate
		if(head!=xCoord){
			// Check sense of movement of snake, 1st case move to left
			if(head<xCoord){
				xCoord--;	// Move point to left
			}
			else{
				xCoord++;	// Move point to right
			}
		}
		else{
			xCoord = head;
			yCoord--;	// Move point to top
		}
		// Check for bottom of screen and move to top 
		if(yCoord == 0){
			yCoord = height_ - 1;
		}
		// Store coordinates to vector
		coord->first = xCoord;
		coord->second = yCoord;
		// Move characters to next position(y,x)
		moveChar(yCoord, xCoord, *symbol); 
	}
	refreshAndWait();
}

void Snake::goLeft(){
	auto coord = m_snakeCoord.begin();
	auto symbol =  snake_symbol_.begin();
	int yCoord = 0;
	int xCoord = 0;
	int head = 0;

	// Update head position
	head_position_ = LEFT;
	// Get actual y coord in order to define column number used for
	//	horizontal movement
	head = m_snakeCoord.back().second;	
	// Update coordinates of symbols by decreasing x coord
	for(;coord!=m_snakeCoord.end()&&symbol!=snake_symbol_.end();++coord,++symbol){
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
			xCoord--;	// Move point to chosen sense of movement
		}
		// Check for edge of screen and move to oposite 
		if(xCoord == 0){
			xCoord = width_-1;
		}
		// Store coordinates to vector
		coord->first = xCoord;
		coord->second = yCoord;
		// Move characters to next position(y,x)
		moveChar(yCoord, xCoord, *symbol);  
	}
	refreshAndWait();
}

void Snake::goRight(){
	auto coord = m_snakeCoord.begin();
	auto symbol =  snake_symbol_.begin();
	int yCoord = 0;
	int xCoord = 0;
	int head = 0;

	// Update head position
	head_position_ = RIGHT;
	// Get actual y coord in order to define column number used for
	//	horizontal movement
	head = m_snakeCoord.back().second;
		
	// Update coordinates of symbols by decreasing x coord
	for(;coord!=m_snakeCoord.end()&&symbol!=snake_symbol_.end();++coord,++symbol){
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
			xCoord++;	// Move point to chosen sense of movement
		}
		// Check for edge of screen and move to oposite 
		if(xCoord == width_){
			xCoord = 0;
		}
		// Store coordinates to vector
		coord->first = xCoord;
		coord->second = yCoord;
		// Move characters to next position(y,x)
		moveChar(yCoord, xCoord, *symbol);  
	}
	refreshAndWait();
}
