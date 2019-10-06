#include<iostream>
#include<string>

using namespace std;

int main(){

	string s = "";
	// Ascii elements
	int counter[126] = {0};
	char elem;
	bool flag = false;

	cin >> s;

	for(int i=0;i<s.length();++i){
		elem = s.at(i);
		counter[elem] += 1;

		// cout << "element: " << int(elem) << endl;
		if(counter[elem]>1){
			// cout << counter[elem] << endl;
			flag = true;	
			break;
		}
	}

	if(flag){
		cout << "String has not unique elements!\n";
	}
	else{
		cout << "String has unique elements!_!*\n";
	}

	return 0;
}