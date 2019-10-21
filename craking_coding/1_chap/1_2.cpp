#include<iostream>
#include<string>
#include<vector>

using namespace std;

bool isPermutation(string & s1, string & s2){

	// Consdier ASCII extended
	vector<int> counts1 (256,0);
	vector<int> counts2 (256,0);

	// Check length before step by step verification
	if(s1.length()!=s2.length()){
		return false;
	}
	else{
		for(int i=0; i<s1.length();++i){
			counts1.at(s1.at(i))++;
			counts2.at(s2.at(i))++;			
		}
		for(int j=0; j<256; j++){
			if(counts1.at(j)!=counts2.at(j)){
				return false;
			}
		}
		return true;
	}	
}

int main(){

	string s1 = "";
	string s2 = "";

	cout << "first string: ";
	getline(cin,s1);
	cout << "second string:";
	getline(cin,s2);

	cout << "\n" <<boolalpha << isPermutation(s1, s2) << endl;

	return 0;
}
