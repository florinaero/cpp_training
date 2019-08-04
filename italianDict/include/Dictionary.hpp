#include <string>
#include <unordered_map>
#include <vector>

class Dictionary{

private:
	std::string m_firstLanguage;
	std::string m_secondLanguage;
	std::string m_author;
	std::unordered_map<std::string, std::string> m_vocab;
	std::vector<std::string> m_fileContent;
	const std::string m_fileName;
	const char m_delimiter;

	// Read a word from keyboard
	bool readWord(std::string& word);
	// Insert word in dicitionary 
	bool insertWord(std::string& newWord, std::string wordLanguage);

public:
	// ctor
	Dictionary(std::string firstLanguage, std::string secondLanguage, std::string author, std::string fileName);
	
	// Insert new pair of words
	bool insertEntry();
	// Search word function
	bool searchWord(std::string searched);
};							