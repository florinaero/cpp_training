/********************************************************************
@brief 
@details 
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// Check if they have the same sum 
bool checkPalindrome(string& input){

	int sum = 0;
	int sumRev = 0;
	int seq = 0;

	// Remove space from string
	input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());

	// Split string in char vector using range ctor
	vector<char> sArray(input.begin(), input.end());

	// Show values of chars from ASCII extended
	for(auto it : sArray){
		seq++;
		// Use unary plus operator to cast to int and get ASCII value
		cout << it << " = "<< +it << endl;
		sum += +it * seq;
		// Compute hash of reverse string
		sumRev += (+sArray.at(sArray.size()-(seq))) * (seq);
		// cout << "sum = " << sum ;
		// cout << "   sumRev = " << sumRev << endl;
	}

	cout << "sum = " << sum << endl;
	cout << "sumRev = " << sumRev << endl;

	if(sum==sumRev){
		return true;
	}
	else{
		return false;
	}
}

// Check if input is a permutation of a palindrome
bool chechPermPalin(string& input){
	// Consider ASCII extended
	vector<int> counts(256,0);
	int countOdd = 0;

	// Remove space from string
	input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
	// Split string in char vector using range ctor
	vector<char> sArray(input.begin(), input.end());

	for(auto it:sArray){
		// Count number of chars by incrementing for each position in ASCII table 
		counts.at((int)it)++;
	}

	// A string is a permutation of a palindrome if it has at most one odd counting 
	// of same letter
	for(auto it:counts){
		if(it%2!=0){
			countOdd++;
		}
		if(countOdd>1){
			return false;
		}
	}

	return true;


}

int main(int argc, char** argv){

	string input = " ";
	bool result = false;

	// cout << argv[1] << endl;
	// input = argv[1];
	cout << "Introduce your word: ";
	getline(cin,input);

	// result = checkPalindrome(input);
	result = chechPermPalin(input);
	if(result){
		cout << "good luck" << endl;
	}
	else{
		cout << "bad luck"<< endl;
	}
	return 0;
}