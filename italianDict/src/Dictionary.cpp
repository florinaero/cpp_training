#include "Dictionary.hpp"
#include "Parser.hpp"
#include <iostream>

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
// Insert a new entry into dictionary
bool Dictionary::insertEntry(){
	bool isEmptyWord1 = true;
	bool isEmptyWord2 = true;
	string word1 = "";
	string word2 = "";

	
	isEmptyWord1 = Dictionary::insertWord(word1, m_firstLanguage);
	isEmptyWord2 = Dictionary::insertWord(word2, m_secondLanguage);
	// If both words are not empty 
	if(!(isEmptyWord1 || isEmptyWord2)){
		m_vocab.emplace(word1, word2);
		return true;
	}
	else{
		cout << "Do not introduce empty words!" << endl;
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Dictionary::searchWord(string searched){
	unordered_map<string, string>::iterator itElem = m_vocab.find(searched);

	if(itElem!=m_vocab.end()){
		cout << "Italian word: ";
		cout << (*itElem).second << endl;
	}
	else{
		cout << "Elem was not found." << endl;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Read word from keyboard
bool Dictionary::insertWord(string& newWord, string wordLanguage){

	cout << "Insert " <<wordLanguage << " word: ";
	// Read word from keyboard
	cin >> newWord;
	// Check if size of word is larger than 0 and return status
	if(!newWord.size()){
		return false;
	}
	else{
		return true;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Dictionary::readWord(string& word){
	return false;
}