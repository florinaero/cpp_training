#include <iostream>
using namespace std;

void test(int);

int main(){

	test(0);
	return 1;
}

void test(int counter){

	if(counter == 10)
		return;
	cout << counter << endl;
	counter += 1;
	test(counter);
}