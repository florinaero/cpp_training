#include <vector>
#include <string>
#include <unordered_map>

class Parser{

private:
	Parser();

public:
	// Read a file line by line.
	// Store each line into a vector of strings
	static void readFile(std::vector<std::string>&, std::string);

	// Split content into words considering delimiter
	static void splitInWords(std::vector<std::string>& content, std::unordered_map<std::string,std::string>& vocab,
							 char delimiter);
};