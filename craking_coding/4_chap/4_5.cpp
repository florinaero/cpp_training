/*************************************************************************************************/
/**
@brief 		Check if a binary tree is a binary search tree.
@details	
@author 	florin_mac
@date 		2020-02-03 21:05:12
->Last Modified by:   florin_mac
->Last Modified time: 2020-02-04 08:48:01
*/
/*************************************************************************************************/

#include <iostream>
#include "fileManager.hpp"
#include <vector>
#include "treeNode.hpp"

using namespace std;


int main(){

	FileManager file;
	string path = "input/4_5.cpp";
	vector<vector<long>> output;

	file.readFileNumbers(path, output,' ');

	vector<long>::const_iterator it = output.at(0).begin();

	for(it;it!=output.at(0).end();++it){
		
	}
	return 0;
}