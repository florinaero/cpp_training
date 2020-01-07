#include <iostream>
#include <chrono>
#include <thread>
#include <curses.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "snake.hpp"

using namespace std;

const int Snake::m_snakeSize = 4;
// Snake symbol
const vector<char> Snake::m_snakeSymbol={'*', '*', '*', '>'};
const int Snake::m_originPoint = 30;

Snake::Snake():
m_width(0),
m_height(0)
{
	// Define coordinates of snake on horizontal
	for(int i=0;i<Snake::m_snakeSize;i++){
		m_snakeCoord.push_back(make_pair(m_originPoint, m_originPoint+i));
	} 
}

void Snake::intitScreen(){
	// Initialize screen 
	initscr();
	// Disables buffer and makes chars to immediately appear on screen 
	cbreak();
	// Disable printing input on screen 
	noecho();
}

void Snake::clearScreen(){
	endwin();
}

void Snake::getScreenSize(){
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	m_width = w.ws_row;
	m_height = w.ws_col;
}


void Snake::goDown(){

}

void Snake::goUp(){

}

void Snake::goLeft(){

}

void Snake::goRight(){

}
