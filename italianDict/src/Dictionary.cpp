#include "Dictionary.hpp"
#include "Parser.hpp"
#include <iostream>
#include <boost/algorithm/string/predicate.hpp>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ctor
Dictionary::Dictionary(string firstLanguage, string secondLanguage, string author, string fileName):
	m_firstLanguage(firstLanguage),
	m_secondLanguage(secondLanguage),
	m_author(author),
	m_fileName(fileName),
	m_delimiter('=')
	{
		// Read file that keeps the decitionary content
		Parser::readFile(m_fileContent, m_fileName);
		// Parse the content and store it 
		Parser::splitInWords(m_fileContent, m_vocab, m_delimiter);
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Write entry to the file 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Insert a new entry into dictionary
bool Dictionary::insertEntry(){
	bool isNotEmptyWord1 = false;
	bool isNotEmptyWord2 = false;
	string word1 = "";
	string word2 = "";
	string line = "";
	
	isNotEmptyWord1 = Dictionary::insertWord(word1, m_firstLanguage);
	isNotEmptyWord2 = Dictionary::insertWord(word2, m_secondLanguage);
	// If both words are not empty 
	if(isNotEmptyWord1 && isNotEmptyWord2){
		m_vocab.emplace(word1, word2);
		line = word1 + " = " + word2;
		// Write entry to file
		Parser::writeLine(line, m_fileName);
		return true;
	}
	else{
		cout << "Do not introduce empty words!" << endl;
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Search word in dictionary
bool Dictionary::searchWord(string searched){
	unordered_map<string, string>::iterator itElem = m_vocab.find(searched);

	if(itElem!=m_vocab.end()){
		cout << endl << "###################" << endl;
		cout << "Italian word: ";
		cout << (*itElem).second;
		cout << endl <<"###################" << endl;
	}
	else{
		cout << "Element was not found." << endl;	
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Dictionary::showWordsStartWith(string& startWord, vector<string>& resultedWords){

	bool isIn = false;

	for(auto const& it : m_vocab){
		isIn = boost::algorithm::starts_with(it.first, startWord);
		// Store word if is founded in list
		if(isIn){
			resultedWords.push_back(it.first);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Read word from keyboard
bool Dictionary::insertWord(string& newWord, string wordLanguage){

	cout << "Insert " <<wordLanguage << " word: ";
	// Read word from keyboard
	cin >> newWord;
	// Check if size of word is larger than 0 and return TRUE
	if(newWord.size()){
		return true;
	}
	// Return FALSE for empty words
	else{
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Dictionary::readWord(string& word){
	return false;
}