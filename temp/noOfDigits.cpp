#include <string>
#include <sstream>
#include <iostream>

using namespace std;

void funct(string& arg1, const string& arg2, string arg3, int arg4){}
int main(){

	long temp  = 233;
	stringstream temp1;
	string temp2;
	int size; 

	// cout << "Introduce a number in order to find number of digits." << endl;
	// cin >> temp;
	temp1 << temp;
	temp1 >> temp2;

	size = temp2.size();

	if(temp2.at(0) == '-'){
		size--;
	}

	cout << "Number of digits of " << temp << " is " << size << endl;
	return 0;
}