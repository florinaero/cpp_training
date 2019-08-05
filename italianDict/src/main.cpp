#include "Dictionary.hpp"
#include "Parser.hpp"
#include <iostream>

using namespace std;

int main(){

	bool exit = 1; 
	int option = 0;
	bool statusEntry = false;
	bool statusSearch = false;
	string searched("");
	vector<string> foundedWords;
	string subString("");
	
	Dictionary *romItal = new Dictionary("romanian","italian","marcucri","vocabolario.txt"); 

	while(exit){
		cout << endl << "choose action vocab:" << endl;
		cout << "1 = insert new word" << endl;
		cout << "2 = search word" << endl;
		cout << "3 = Show words that start with. " << endl;
		cout << "0 = exit" << endl;
		cout << "Option: ";
		cin >> option;
		cout << endl;
		switch(option){
			case(0):
				exit = 0;
				break;
			case(1):
				statusEntry = romItal->insertEntry();
				break;
			case(2):
				cout << "Introduce searched word:";
				cin >> searched;
				statusSearch = romItal->searchWord(searched);
				break;
			case(3):
				cout << "Start with: ";
				cin >> subString;
				foundedWords.clear();
				romItal->showWordsStartWith(subString, foundedWords);
				if(!foundedWords.empty()){
					cout << endl << "Result:" << endl;
					for(auto it : foundedWords){
						cout << it << endl;
					}
				}
				else{
					cout << "Nothing found." << endl;
				}
				break;

			default:
				cout << "Wrong option." << endl;
				cout << endl;
				break;	

		}
	}

	delete romItal;	

	// for(unordered_map<string,string>::iterator it=vocab.begin(); it!=vocab.end(); ++it){
	// 	cout << (*it).first << "$   $" << (*it).second <<"$"<< endl;
	// }

	// unordered_map<string, string>::iterator itElem = vocab.find(word);
	return 0;
}