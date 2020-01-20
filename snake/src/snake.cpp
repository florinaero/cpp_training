#define DEBUG 0

#include <iostream>
#include <chrono>
#include <thread>
#include <curses.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "snake.hpp"
#include <random>
/*
todo: Reduce size of run() function.
Solved: Remove fixed dimmension of snake_symbol_
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
	intitScreen();
	// Define coordinates of snake on vertical
	for(size_t i=0;i<born_size_;i++){
		// Start from middle of window
		snake_coord_.push_back(Coord(width_/2, height_/2+i));
	} 

	// Start running snake
	run();
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
	snake_coord_.emplace_back(snake_coord_.back());
	// Change y coordinate of the new head
	snake_coord_.back().y_coord = new_ycoord;
	// Change x coordinate of the new head
	snake_coord_.back().x_coord = new_xcoord;
	// Remove snake's tail
	snake_coord_.pop_front();

	wchar_t symbol = 'x';
	// Update coordinates of symbols by changing head's coord and copying coordinates
	//	of symbols from tail to head, follow head.
	for(auto it=snake_coord_.rbegin();it!=snake_coord_.rend();++it){
		// Choose symbols of snake according to deque coordinates sequence
		if(it==snake_coord_.rbegin()){
			symbol = SnakeSymbols::head;
		}
		else{
			symbol = SnakeSymbols::body;
		}
		moveChar(it->y_coord, it->x_coord, symbol); 

	}
	refreshAndWait();
}

//TODO: Reduce function size to 40 lines
void Snake::run(){
	wchar_t old_direction = 0;
	bool change_flag = false;
	Coord food_coord = getFoodCoord();
	
	// Exit with STOP_KEY
	while(head_position_!=STOP_KEY){
		// Check if no key or wrong key was pressed, then keep previous command
		if(head_position_==ERR || (head_position_!=UP && head_position_!=DOWN && 
										head_position_!=RIGHT && head_position_!=LEFT)){
			head_position_ = old_direction;
		}

		// Generate new coordinates for food if head reached it
		if(checkFoodReached(food_coord)){
			food_coord = getFoodCoord();
			increaseSize();
		}
		// DEBUG
		// food_coord.y_coord = height_ -1;
		// Place food symbol on screen 
		moveChar(food_coord.y_coord, food_coord.x_coord, food_symbol_);
		
		// Check for collision 
		if(checkCollision()){
			break;
		}
		// Flag that checks if chosen direction is backwards
		change_flag = false;
		switch(head_position_){
			case UP: 
				if(old_direction!=DOWN){
					goUp();
					change_flag = true;
				}
				break;
			case DOWN:
				if(old_direction!=UP){
					goDown();
					change_flag = true;
				}
				break;
			case LEFT: 
				if(old_direction!=RIGHT){
					goLeft();
					change_flag = true;
				}
				break;
			case RIGHT: 
				if(old_direction!=LEFT){
					goRight();
					change_flag = true;
				}
				break;
			default: // Do nothing
				break;
		}
		if(change_flag){
			// Store direction that was selected 
			old_direction = head_position_;
		}	
		// Get direction from input
		head_position_ = getch();
	}
	// Return to original screen
	clearScreen();
}

void Snake::goDown(){
	int new_ycoord = 0;
	// Update head position
	head_position_ = DOWN;

	new_ycoord = snake_coord_.back().y_coord;
	new_ycoord++;
	// Check not to get out of screen
	if(new_ycoord>=height_){
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
	if(new_ycoord<1){
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
	if(new_xcoord<1){
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
	if(new_xcoord>=width_){
		new_xcoord = 0;
	}
	
	updateCoord(new_xcoord, snake_coord_.back().y_coord);
}

Snake::Coord Snake::getFoodCoord(){
	Coord food_coord(0,0);

	random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis_x(1, width_ - 1);
    uniform_int_distribution<> dis_y(1, height_ - 1);
    
    food_coord.x_coord = dis_x(gen);
    food_coord.y_coord = dis_y(gen);
    
    return food_coord;
}

bool Snake::checkFoodReached(const Coord& food_coord){
	// Compare coord of head with food coord
	return (snake_coord_.back() == food_coord);
}

void Snake::increaseSize(){
	// Create a copy of head to increase size of snake
	snake_coord_.emplace_back(snake_coord_.back());
	// Define position of newest head by checking actual direction 
	switch(head_position_){
		case UP:
			snake_coord_.back().y_coord--;
			break;
		case DOWN:
			snake_coord_.back().y_coord++;
			break;
		case LEFT: 
			snake_coord_.back().x_coord--;
			break;
		case RIGHT:
			snake_coord_.back().x_coord++;
			break;
		default:	// Do nothing
			break; 
	}
}

// Check if head hits body by checking duplicate in list
bool Snake::checkCollision(){
	int wait_time = 400; 
	auto head = snake_coord_.back();
	// Check each element against last elem(head) 
	for(size_t i=0;i<snake_coord_.size()-1;i++){
		if(head==snake_coord_.at(i)){
			for(int i=0;i<3;i++){
				// Clear screen
				clear();
				refresh();
				this_thread::sleep_for(chrono::milliseconds(wait_time));
				for(auto & it : snake_coord_){
					moveChar(it.y_coord, it.x_coord, SnakeSymbols::body);
				}
				// Refresh screen 
				refresh();
				this_thread::sleep_for(chrono::milliseconds(wait_time));
			}
			return true;
		}
	}
	return false;
}
