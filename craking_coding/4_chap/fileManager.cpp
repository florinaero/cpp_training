/*************************************************************************************************/
/**
@brief 		
@details	
@author 	Marcu Cristian
@date 		2019-11-10 01:15:20
->Last Modified by:   Marcu Cristian
->Last Modified time: 2019-11-11 23:58:38
*/
/*************************************************************************************************/

#include "fileManager.hpp"
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept> 
#include <iostream>

using namespace std;

bool FileManager::readFileNumbers(string fileName, vector< vector<long> >& output, char delim){
	ifstream file(fileName,ios_base::in);
	string line;

	if(!file.good()){
		cerr << "Couldn't open file!" << endl;
		return 0;
	}

	while(getline(file,line)){
		// Store each line of elements in matrix
		output.push_back(split(line, delim));
	}
	return 1;
}

vector<long> FileManager::split(string in, char delim){
	// Create stream from string 
	stringstream stream(in);
	vector<long> list;
	string elem = "";

	// Return empty vector if string is empty
	if(in.empty()){
		return list;
	}
	while(getline(stream, elem, delim)){
		try{
			// Convert string to long and store it to vector
			list.push_back(stol(elem));
		}
		catch(const invalid_argument& ia){
			cerr << "Invalid argument: " << ia.what() << '\n';
			break;
			return list;
		}
		catch(const out_of_range& oor){
			cerr << "Out of Range error: " << oor.what() << '\n';
			break;
			return list;
		}
	}
	return list;
}