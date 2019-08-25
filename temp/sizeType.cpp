#include <iostream>

using namespace std;

int main(){


	cout << "Type" << "           | " << "Size(bytes)" << endl;
	cout << "------------------------------------------"<< endl;
	cout << "int" << "            | " << sizeof(int) << endl;
	cout << "uint" << "           | " << sizeof(uint) << endl;
	cout << "long" << "           | " << sizeof(long) << endl;
	cout << "long long int" << "  | " << sizeof(long long int) << endl;
	cout << "double" << "         | " << sizeof(double) << endl;
	return 0;
}