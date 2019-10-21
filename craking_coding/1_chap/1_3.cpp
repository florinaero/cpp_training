#include<iostream>
#include<vector>
#include<string>

using namespace std;

void replaceChar(string & input, string & output, string & insertion){

	for(int i=0;i<input.length();i++){
		
		if(input.at(i) ==' '){
			output = output + insertion;
		}
		else{
			// Insert next elements to output
			output = output + input.at(i);
		}
	}
}

int main(){

	string s1 = "";
	string s2 = "";
	string insertion = "%20";

	cout << "String: ";
	getline(cin,s1);


	replaceChar(s1, s2, insertion);
	
	cout << "\n" << s2  << endl;

	return 0;
}

