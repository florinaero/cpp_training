/*************************************************************************************************/
/**
@brief 		4.4 Check Balanced
@details	Check if a binary tree is balanced.\n
			Implementation with DFS.
@author 	Marcu Cristian
@date 		2019-12-02 23:06:29
->Last Modified by:   Marcu Cristian
->Last Modified time: 2019-12-05 22:57:49
*/
/*************************************************************************************************/

#include <iostream>
#include <forward_list>
#include "fileManager.hpp"
#include <vector>
#include <string>

using namespace std;

struct Node{
public:
	int data;
	bool visit;

	Node(int data_input)
		:data(data_input),
		visit(false){}
};

void preOrder(int start, int end, const vector<long> &input, shared_ptr<forward_list<Node>> tree){
	
	cout << "end: "<< end << " start:" << start << endl;
	if(end<start){
		return;
	}	
	
	int mid = (start+end)/2;
	cout << "mid: " << mid << endl;
	// Build node 
	Node node(input.at(mid));
	cout << "node: " << node.data << endl;
	tree->emplace_front(node);
	
	preOrder(start,mid-1,input,tree);
	preOrder(mid+1,end,input,tree);
}

// Create a tree using preorder traversal
void createTree(const vector<long> &input, shared_ptr<forward_list<Node>> tree){
	size_t len = input.size();
	preOrder(0, len-1, input, tree);	
}

int main(){	
	vector < vector<long> > input;
	string path = "input/4_4.txt";

	auto tree = make_shared<forward_list<Node>>();

	// Read input
	FileManager::readFileNumbers(path, input);
	// Create tree using singly linked list with pre-order traversal
	createTree(input.at(0), tree);

	cout << "Content of singly list tree: " << endl;
	for(auto it=tree->begin();it!=tree->end();++it){
		cout << (*it).data << endl;
	}

	return 0;
}