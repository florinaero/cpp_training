/**********************************************************
1.5
There are three types of edits that can be done on a 
strings: insert, remove, replace character. 
Given 2 strings check if they are one(or zero) edit away.
Example:	pale,  ple  -> true
			pales, pale -> true
			pale,  bake -> false
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool check(string& input1, string& input2){
	size_t size1 = input1.size();
	size_t size2 = input2.size();
	string largest = "";
	int sum = 0; 
	int counter = 0;
	bool result = false;

	// Only english letters
	vector<int> letters(26,0);

	// Check if strings are different with more than one letter
	if(abs(int(size1-size2)) > 1){
		return false;
	}

	// Check if strings are already equal
	if(input1 == input2){
		return true;
	}

	if(size1-size2 < 0){
		largest = input2;
	}
	else{
		largest = input1;
	}

	// Add 1 for letters from first string
	for(auto i : input1){
		letters.at('z'-i) += 1;
	}

	// Subtract 1 for letters from second string
	for(auto i : input2){
		letters.at('z'-i) -= 1;
	}

	for(auto i : letters){
		cout << i << " " ;
		// Sum up counting of letters
		sum += i;
		if(i!=0){
			counter += 1;
		}
	} 	

	cout << endl;

	// Check if one move is necessary
	if(sum==0 && counter==2){
		result = true;
	}
	// Check if one replace is necessary
	else if(counter==1 && (sum==-1 || sum ==1)){
		result = true;
	}
	// Check if are palindrome
	else if(sum==0 && counter==0){
		result = true;
		cout << "Strings are palindrome." << endl; 
	}

	cout << "counter = " << counter << endl;
	cout << "sum = " << sum << endl;
	return result;
}


int main(){

	string input1;
	string input2;
	bool result = false; 

	input1 = "pale";
	input2 = "ple";

	cout << "world1: ";
	cin >> input1;
	cout << endl << "world2: ";
	cin >> input2;

	result = check(input1, input2);

	cout << boolalpha << endl << result;
	return 0;
}
