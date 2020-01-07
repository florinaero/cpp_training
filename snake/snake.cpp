#include <iostream>
#include <chrono>
#include <thread>
#include <curses.h>
#include <sys/ioctl.h>
#include <stdio.h>

using namespace std;

class Snake{

public:
	int m_width;
	int m_height;
	static m_snakesize;
	// Coordinates of snake on screen
	vector<pair<int,int>> m_snakeCoord;
	// Snake symbol
	static vector<char> m_snakeSymbol();

	Snake():
	m_width(0),
	m_height(0)
	{
		m_snakeSymbol.push_back
	}

	void intitScreen(){
		// Initialize screen 
		initscr();
		// Disables buffer and makes chars to immediately appear on screen 
		cbreak();
		// Disable printing input on screen 
		noecho();
	}

	void defineStart(){

		const int startPoint = 30;
		// Define coordinates of snake on horizontal
		for(int i=0;i<5;i++){
			m_snakeCoord.push_back(make_pair(startPoint,startPoint+i));
		}
	}

	void getScreenSize(){
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		m_width = w.ws_row;
		m_height = w.ws_col;
	}


	void goDown(){
		for(;;){

		}
	}

	void goRight(){

	}

}


int main(){
	const int size = 0;
	const char UP = 'w';
	const char DOWN = 's';
	const char LEFT = 'a';
	const char RIGHT = 'd';
	int width = 0;
	int height = 0;

	char tmp = 0;

	for(int i : m_snake){
		mvaddstr(i.first(), i.second(),);	
	}
	
	refresh();
	this_thread::sleep_for(chrono::milliseconds(2000));
	endwin();
	return 0;
	for(;;){
		// Enables automatic flushing 
		cout << unitbuf;
		cout << "***->";
		// Wait time
		this_thread::sleep_for(chrono::milliseconds(100));
		// Move cursor at initial point
		for(int i=0;i<size;i++){
			cout << '\b';
		}
		// Erase all chars by overwritng with blank
		for(int i=0;i<size;i++){
			cout << ' ';
		}
		// Move cursor at intial point + 1 
		for(int i=0;i<size-1;i++){
			cout << '\b';
		}

		switch(tmp = getchar()){
			case UP:
				cout << "up" << endl;
				break;
			case DOWN:
				cout << "down" << endl;
				break;
			case LEFT: 
				cout << "left" << endl;
				break;
			case RIGHT:
				cout << "right" << endl;
				break;
			default:
				break;
 		}	
	}

	cout << endl;
	
	return 0;
}