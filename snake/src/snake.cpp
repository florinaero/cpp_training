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
todo: Remove fixed dimmension of m_snakeSymbol
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

const int Snake::m_snakeSize = 4;
// Snake symbol
const vector<char> Snake::m_snakeSymbol={'#', '*', '*', 'o'};

// Coordinates constructor
Snake::Coord::Coord(int x_coord, int y_coord):
	x_coord(x_coord),
	y_coord(y_coord)
	{}

Snake::Snake(int waitTimeMills):
m_width(0),
m_height(0),
m_waitTimeMills(waitTimeMills)
{
	// Init screen for ncurses
	Snake::intitScreen();
	// Define coordinates of snake on vertical
	for(int i=0;i<Snake::m_snakeSize;i++){
		// Start from middle of window
		m_snakeCoord.push_back(make_pair(m_width/2, m_height/2+i));
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
	m_height = w.ws_row;
	m_width = w.ws_col;
	// cout << "width: "<<m_width << "  height: \n" << m_height;
}

void Snake::refreshAndWait(){
	// Refresh screen 
	refresh();
	// Wait time
	this_thread::sleep_for(chrono::milliseconds(m_waitTimeMills));
	// Clear screen
	clear();
}

void Snake::goDown(){

	auto coord = m_snakeCoord.begin();
	auto symbol =  m_snakeSymbol.begin();
	int yCoord = 0;
	int xCoord = 0;
	int head = 0;

	// Get position of head of previous snake's position on x axis
	head = m_snakeCoord.back().first;
	// Update coordinates of symbols by increasing y coord
	for(;coord!=m_snakeCoord.end()&&symbol!=m_snakeSymbol.end();++coord,++symbol){
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
			// Move point to bottom
			yCoord += 1;
		}
#if DEBUG	
		cout << "  " << "symbol: " << *symbol;
		cout << "---head: " << head;
		cout << "  " << "coord->first: " << coord->first;
		cout << "  " << "yCoord: " << yCoord;
#endif
		// Check for bottom of screen and move to top 
		if(yCoord == m_height-1){
			yCoord = 0;
		}
		// Store coordinates to vector
		coord->first = xCoord;
		coord->second = yCoord;
		// Move characters to next position(y,x)
		mvaddch(yCoord, xCoord, *symbol); 
	}

	refreshAndWait();
}

void Snake::goUp(){
	auto coord = m_snakeCoord.begin();
	auto symbol =  m_snakeSymbol.begin();
	int yCoord = 0;
	int xCoord = 0;
	int head = 0;

	// Get actual x coord in order to define column number used for
	//	vertical movement
	head = m_snakeCoord.back().first;
	// Update coordinates of symbols by decreasing y coord
	for(;coord!=m_snakeCoord.end()&&symbol!=m_snakeSymbol.end();++coord,++symbol){
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
			yCoord = m_height-1;
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
	auto coord = m_snakeCoord.begin();
	auto symbol =  m_snakeSymbol.begin();
	int yCoord = 0;
	int xCoord = 0;
	int head = 0;

	// Get actual y coord in order to define column number used for
	//	horizontal movement
	head = m_snakeCoord.back().second;
		
	// Update coordinates of symbols by decreasing x coord
	for(;coord!=m_snakeCoord.end()&&symbol!=m_snakeSymbol.end();++coord,++symbol){
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
			xCoord = m_width-1;
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
	auto coord = m_snakeCoord.begin();
	auto symbol =  m_snakeSymbol.begin();
	int yCoord = 0;
	int xCoord = 0;
	int head = 0;

	// Get actual y coord in order to define column number used for
	//	horizontal movement
	head = m_snakeCoord.back().second;
		
	// Update coordinates of symbols by decreasing x coord
	for(;coord!=m_snakeCoord.end()&&symbol!=m_snakeSymbol.end();++coord,++symbol){
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
		if(xCoord == m_width){
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
