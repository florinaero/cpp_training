#include <iostream>
#include <chrono>
#include <thread>
#include <curses.h>
#include "snake.hpp"

using namespace std;

int main(){

	// Create snake object with wait time in mills and initial direction
	Snake snake(100, RIGHT);
	return 0;
}