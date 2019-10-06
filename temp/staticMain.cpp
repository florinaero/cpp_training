#include "staticSingleton.hpp"

using namespace std;

void run(){
	string second = "second";
	staticSingleton::getInstance().insert(second);
}

int main(){

	string first = "first";
	staticSingleton::getInstance().insert(first);
	run();
	return 0;	
}