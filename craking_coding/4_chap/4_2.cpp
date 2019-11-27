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
#include "bst.hpp"

using namespace std;


shared_ptr< TreeNode<long> > createMinimalBst(vector<long> array, int start, int end){
	static int i = 0;
	if(end<start){
		return nullptr;
	}
	// cout << "start = " << start << "  end = " << end << endl;

	int mid = (start+end)/2;
	// cout << "mid = " << mid << endl;	
	shared_ptr< TreeNode<long> > node = make_shared< TreeNode<long> >(array.at(mid));
	node->m_left = createMinimalBst(array, start, mid-1);
	node->m_right = createMinimalBst(array, mid+1, end);

	// cout << "    node = " << node->m_key << endl;
	return node;
}

shared_ptr< TreeNode<long> > createMinimalBst(vector<long> array){
	return createMinimalBst(array,0,array.size()-1);
}

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

	vector< vector<long> > fileMatrix;
	 
	// Get input
	status = FileManager::readFileNumbers("input/4_2.txt", fileMatrix);
	if(!status){
		return 0;	
	}
	// First line of file has total number of nodes
	nodes = fileMatrix.at(0).size();

	Bst<long> tree;
	tree.setLevels(nodes);
	shared_ptr< TreeNode<long> > root;

	// Create BST 
	root = createMinimalBst(fileMatrix.at(0));

	// Print content of input array
	for(auto &line : fileMatrix){
		for(auto &elem : line){
			cout << elem << " ";
		}
		cout << endl;
	}
	// cout << "levels = " << tree.m_levels << endl;

	tree.showBst(root);
	return 0;
}