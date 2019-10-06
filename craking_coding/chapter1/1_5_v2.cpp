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

	string concat = "";

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

	concat = input1 + input2;
	
	// 
	for(auto i : concat){
		letters.at('z'-i) ^= 1;
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
	cout << "counter = " << counter << endl;
	cout << "sum = " << sum << endl;


	// One replacement is neccesary; identical strings already checked
	if(sum == 1 || sum == 0){
		result = true;
	}

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
