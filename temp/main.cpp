#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <deque>

using namespace std;


int main(){

	long temp;
	stringstream temp1;
	string temp2;
	int size; 
	deque<int> dlist= {1,2,3,4,5,6,6};
	

	cout << "post increment:" << endl;
	for(auto it=dlist.begin();it!=dlist.end();it++){
		cout << *it << endl;
	}

	cout << "pre increment:" << endl;
	for(auto it=dlist.begin();it!=dlist.end();++it){
		cout << *it << endl;
	}


	cout << "duplicates:" << endl;
	for(int i=0;i<dlist.size()-1;++i){
		int a = dlist.at(i);
		int b = dlist.at(i+1);
		// cout << a << " = " << b << endl;
		if(a==b){
			cout <<  a << " = " << b << endl;

		}
	}	
	return 0;
}