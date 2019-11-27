/*************************************************************************************************/
/**
@brief 		4.3 List of Depths
@details	Given a binary tree create a list for each level. \n
			Use pre-order algorithm. \n
			This implementation use pre-order traversal as in 1st solution, \n
			but it uses smart pointers and stl forward_list for get used with them.
@author 	Marcu Cristian
@date 		2019-11-19 00:30:33
->Last Modified by:   Marcu Cristian
->Last Modified time: 2019-11-27 23:20:46
*/
/*************************************************************************************************/

#include <iostream>
#include <cmath>
#include <forward_list>
// User's libraries
#include "fileManager.hpp"
// Binary search tree 
#include "bst.hpp"

using namespace std;
using arrList = vector< shared_ptr<forward_list < TreeNode<long> > > >;

shared_ptr< TreeNode<long> > createTree(vector<long>& arrInput, long start, long end){
	if(end<start){
		return nullptr;
	}

	// Compute interval's middle
	int mid = (start+end)/2;
	// Create a pointer for node
	auto node = make_shared< TreeNode<long> >(arrInput.at(mid));
	node->m_left = createTree(arrInput, start, mid-1);
	node->m_right = createTree(arrInput, mid+1, end);

	return node;
}

shared_ptr< TreeNode<long> > createTree(vector<long>& arrInput){
	return createTree(arrInput, 0, arrInput.size()-1);
}

void generate(shared_ptr<arrList> shpLists, shared_ptr<TreeNode<long>> root,
			 int level)
{	
	static int counter(0);

	// Check for nulity 
	if(!root){
		return;
	}

	auto shpTemp = make_shared<forward_list<TreeNode<long>>>();
	
	if(shpLists->size() == level){
		cout << "counter = " <<  ++counter << endl;
		shpLists->push_back(shpTemp);
	}
	else{
		shpTemp = shpLists->at(level);
		cout << "Get level\n";
	}

	// Add node at the end of list
	shpTemp->emplace_front(*root);
	cout << (*root).m_key << endl << endl;	
	generate(shpLists, root->m_left, level+1);
	generate(shpLists, root->m_right, level+1);
}

shared_ptr<arrList> storeLevelList(shared_ptr<TreeNode<long>> root){
	// Create pointer to instance of vector of linked lists of nodes
	auto shpLists = make_shared<arrList>();
	generate(shpLists, root, 0);
	return shpLists;
}

int main(){


	vector< vector<long> > input;
	int levels{0};
	int index{0};
	int totalNodes{0};
	int nodes{0};

	// Read file line by line 
	FileManager::readFileNumbers("input/4_3.txt", input);

	// Total number of nodes 
	totalNodes = input[0].size();
	cout << "totalNodes = " << totalNodes << endl;

	// Create trre from array
	Bst<long> tree;
	tree.setLevels(totalNodes);
	shared_ptr< TreeNode<long> > root;
	root = createTree(input.at(0));
	// Show tree
	tree.showBst(root);

	// Array of singly linked list for each level of nodes
	shared_ptr<arrList> shpLists;

	shpLists = storeLevelList(root);

	cout << "Content of lists for each level." << endl;	
	// Loop pointer to lists
	for(auto& i : *shpLists){
		// Loop nodes of lists
		for(auto& m : *i){
			cout << m.m_key << "  ";
		}
		cout << endl;
	}

	// Find number of levels
	levels = ceil(log(totalNodes+1)/log(2));
	cout << "levels = " << levels << endl;

	return 0;
}