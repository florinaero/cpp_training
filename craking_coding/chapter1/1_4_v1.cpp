/********************************************************************
@brief Brute force is not an option. 
@details This problem is not correct cause is not considering all 
			permutations.
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Brute force 
bool checkPalindrome(string& orig){

	string tmp = "";
	string rev = "";
	bool result = false;

	for(int i=0;i<orig.length();i++){
		for(int j=0;j<orig.length();j++){
			// Skip repetitions in string
			if(i!=j){
				tmp=orig;
				tmp.at(i) = orig.at(j);
				tmp.at(j) = orig.at(i);
				rev = tmp;
				reverse(rev.begin(),rev.end());
				if(tmp!=rev){
					cout << tmp << "<-->" << rev << endl;
					if(j==orig.length()-1){
						cout << i << endl;
					}
					// return true;
				}
			}
		}
	}

	return false;
}

int main(){

	string input = " ";
	bool result = false;

	cout << "Introduce your word: ";
	cin >> input;
	result = checkPalindrome(input);
	if(result){
		cout << "good luck" << endl;
	}
	else{
		cout << "bad luck"<< endl;
	}
	return 0;
}