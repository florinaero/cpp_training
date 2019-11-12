/*************************************************************************************************/
/**
@brief 		
@details	
@author 	Marcu Cristian
@date 		2019-11-10 00:53:15
->Last Modified by:   Marcu Cristian
->Last Modified time: 2019-11-11 23:58:33
*/
/*************************************************************************************************/

#include <string>
#include <vector>

class FileManager{
public:
	// Read file that contains only numbers and store them in a matrix
	static bool readFileNumbers(std::string fileName, std::vector< std::vector<long> >& output, 
								char delim=' ');
	// Split a string into integer vector
	static std::vector<long> split(std::string in, char delim);		

};