/*************************************************************************************************/
/**
@brief 		4.2 Minimal tree 	
@details	Given a sorted(increasing order) array with unique integer elements, write an algorithm
			to create a binary seaerch tree with minimal height. 
@author 	Marcu Cristian 
@date 		Oct,2019
*/
/*************************************************************************************************/

#include <iostream>
#include <cmath>
#include "fileManager.hpp"

using namespace std;

class Tree{
public:
	/**
	@brief				Find number of levels for a binary tree
	@param[in] 	nodes	Number of nodes of a binary tree
	@return				Number of levels for a binary tree considering root. 
	*/
	int findLevels(int nodes){
		return ceil(log(nodes+1)/log(2));	
	}

};


int main(int argc, char** argv){	

	int nodes;
	double levels; 
	int status = 0;
	int rootPos = 0;
	int rightNoLvl = 0;
	int leftNoLvl = 0;
	int actNode = 0;
	int nodesLvl = 0;
	int child = 0;
	vector< vector<int> > adjList;
	vector<long> listNodes;

	Tree tr;
	vector< vector<long> > fileMatrix;
	 
	// Get input
	status = FileManager::readFileNumbers("input/4_2.txt", fileMatrix);
	if(!status){
		return 0;	
	}

	// First line of file is number of nodes
	nodes = fileMatrix.at(0).at(0);
	// Resize adjacency list with no of nodes
	adjList.resize(nodes);

	listNodes = fileMatrix.at(1);

	// Find root position in vector by considering parity of # nodes.
	if(nodes%2==0){
		// Left half smaller by one node than left
		rootPos = nodes/2 -1;
		// Number of nodes for right half is equal with position of root 
		rightNoLvl = tr.findLevels(rootPos);
		leftNoLvl= rightNoLvl + 1;		 
	}
	else{
		rootPos = floor(nodes/2);
		rightNoLvl = tr.findLevels(rootPos);
		leftNoLvl= rightNoLvl;		 	
	}

	for(auto &line : fileMatrix){
		for(auto &elem : line){
			cout << elem << " ";
		}
		cout << endl;
	}

	cout << "root node = " << rootPos << endl;
	cout << "No. of right and left levels: " << rightNoLvl << " " << leftNoLvl << endl;
	cout << endl;

	int firstNodeLvl;
	firstNodeLvl = rootPos - 1;
	int children = 0;
	int counter = 0;
	
	// Create right half of tree
	for(int lvl=0;lvl<rightNoLvl-1;lvl++){	
		nodesLvl = pow(2,lvl);	// Number of nodes for each level
		if(lvl>0){
			firstNodeLvl = firstNodeLvl - nodesLvl;	// Get position of first node of level
		}
		children = 2 * nodesLvl;	// Numebr of possible children for nodes of a level
		counter = 0;
		cout << "\nnodesLvl = " << nodesLvl << endl;
		cout << "firstNodeLvl = " << firstNodeLvl << endl;
		for(int j=0;j<nodesLvl;j++){	// Loop through all nodes of level
			actNode = firstNodeLvl + j;	// Pos. of node on its level, relative to 1st node
			cout << "node = " << listNodes.at(actNode) << endl;
			for(int k=counter;k<counter+2;k++){	// Child relativ to firstNodeLvl
				child = firstNodeLvl - (nodesLvl+k);
				if(child < 0){	// Check for last node
					cout << "last node = " << listNodes.at(child+1); 
					return 0;
				}
				// Store children		
				adjList.at(actNode).push_back(listNodes.at(child));	
				// cout << "pos  = " << child; 
				cout << " child = " << listNodes.at(child) << endl;
			}				
			counter = counter + 2;	// increase by 2 to move at next pair of children
		}
	}		

	return 0;
}