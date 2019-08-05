#include "Parser.hpp"
#include <iostream>
#include <fstream>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Read file
void Parser::readFile(vector<string>& content, string fileName){

	string line;

	ifstream file (fileName);
	if(file){
		while(getline(file, line)){
			content.push_back(line);
		}
	}
	else{
		cout << "File couldn't open!";
	}

	file.close();

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Parser::splitInWords(vector<string>& content, unordered_map<string, string>& vocab, char delimiter){

	vector<string>::iterator ItContent = content.begin();
	string word1("");
	string word2("");
	int counter(0);

	// Loop through all elements of the vector 
	for(;ItContent!=content.end();++ItContent){
		counter++;
		// Search for the delimiter in order to split in words
		std::size_t delimPosition = (*ItContent).find(delimiter);

		// cout << delimPosition << endl;
		// cout << *ItContent << endl;
		// Split sequence and store in map only the delimiter exists
		if(delimPosition!=string::npos){
			// First word splitting; Stop with one position before to remove a blank " "
			word1 = (*ItContent).substr(0,delimPosition-1);
			// Start from second pos to remove a blank " "
			word2 = (*ItContent).substr(delimPosition+2, string::npos);
			vocab.emplace(word1, word2); 
		}
		else{
			cout << "Delimiter " << delimiter << " was not found in vector's line " << counter << endl; 
		}
	}
}
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
// Write line to the end of the file
void Parser::writeLine(string& line, string fileName){

	ofstream file (fileName, ios::app);

	if(file){
		file << endl << line;
	}
	else{
		cout << "File couldn't open!";	
	}

	file.close();
}