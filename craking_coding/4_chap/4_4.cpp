/*************************************************************************************************/
/**
@brief 		4.4 Check Balanced
@details	Check if a binary tree is balanced.\n
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
#include <algorithm>

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

struct TreeNode{
	shared_ptr<TreeNode> left;
	shared_ptr<TreeNode> right;
	int data;
	bool visited;

	TreeNode(int data):
	left(nullptr),
	right(nullptr),
	data(data),
	visited(false){}
};

// Answer of CTCI
int getHeight(shared_ptr<TreeNode> root){
	if(root==nullptr){
		return -1;
	}

	return max(getHeight(root->left), getHeight(root->right)) + 1;
}

// Answer of CTCI
bool isBalanced(shared_ptr<TreeNode> root){
	if(root==nullptr){
		return true;
	}

	int heightDiff = getHeight(root->left) - getHeight(root->right);
	if(abs(heightDiff)>1){
		return false;
	}
	else{
		return isBalanced(root->left) && isBalanced(root->right);
	}
}

void insert(shared_ptr<TreeNode> parent, int data){
	parent = make_shared<TreeNode>(data);
}

shared_ptr<TreeNode> insert_bst(shared_ptr<TreeNode> parent, int data){
	static int counter = 0;
	if(parent==nullptr){
		cout << counter++ << " root is null" << endl;
		return make_shared<TreeNode>(data);
	}
	else{
		// cout << counter << " root is not null" << endl;
		if(data>=parent->data){
			cout << "LEFT" << endl;	
			parent->left = insert_bst(parent->left, data);
		}
		else{
			cout << "RIGHT" << endl;
			parent->right = insert_bst(parent->right, data);
		}
		return parent;
	}
}

void preOrderRead(shared_ptr<TreeNode> node){

	if(node!=nullptr){
		cout << node->data << endl;
		preOrderRead(node->left);
		preOrderRead(node->right);
	}
}

void postOrderRead(shared_ptr<TreeNode> node){
	if(node!=nullptr){
		postOrderRead(node->left);
		postOrderRead(node->right);
		cout << node->data << endl;
	}
}

int main(){	
	vector < vector<long> > input; 
	string path = "input/4_4.txt";

	auto root = make_shared<TreeNode>(0);
	// root = nullptr;
	for(int i=1;i<10;i++){
		insert_bst(root, i);
	}

	cout << "Root data: " << (root->data) << endl;
	cout << "preOrderRead" << endl;
	preOrderRead(root);

	cout << "postOrderRead" << endl;
	postOrderRead(root);
	
	bool result = false;
	result = isBalanced(root);
	cout << "Is balanced: " << boolalpha << result << endl;
	// auto tree = make_shared<forward_list<Node>>();
	// // Read input
	// FileManager::readFileNumbers(path, input);
	// // Create tree using singly linked list with pre-order traversal
	// createTree(input.at(0), tree);

	// cout << "Content of singly list tree: " << endl;
	// for(auto it=tree->begin();it!=tree->end();++it){
	// 	cout << (*it).data << endl;
	// }


	return 0;
}