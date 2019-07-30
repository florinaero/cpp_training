#include "Dictionary.hpp"
#include "Parser.hpp"
#include <iostream>

using namespace std;

int main(){

	vector<string> content;
	string fileName = "vocabolario.txt";
	unordered_map<string, string> vocab;

	Parser::readFile(content, fileName);
	Parser::splitInWords(content, vocab, '=');

	for(unordered_map<string,string>::iterator it=vocab.begin(); it!=vocab.end(); ++it){
		// cout << (*it).first << "$   $" << (*it).second <<"$"<< endl;
	}

	unordered_map<string, string>::iterator itElem = vocab.find("ceas");

	if(itElem!=vocab.end()){
		cout << "Italian word: ";
		cout << (*itElem).second << endl;
	}
	else{
		cout << "Elem was not found." << endl;
	}

	return 0;
}