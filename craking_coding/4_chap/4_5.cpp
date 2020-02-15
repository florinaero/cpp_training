/*************************************************************************************************/
/**
@brief 		Check if a binary tree is a binary search tree.
@details	
@author 	florin_mac
@date 		2020-02-03 21:05:12
->Last Modified by:   florin_mac
->Last Modified time: 2020-02-04 08:48:01
Condition of a binary search tree:
-> every node has maximum 2 children
-> left node < node <= right node
*/
/*************************************************************************************************/

#include <iostream>
#include <vector>
#include <memory>
// #include "treeNode.hpp"
#include "fileManager.hpp"
#include "../logging.hpp"
using namespace std;

const bool LOG = 0;

class Node{
public:
	int key_;
	shared_ptr<Node> parent_;
	shared_ptr<Node> left_;
	shared_ptr<Node> right_;
	// Ctor
	Node(int key):
	key_(key),
	parent_(nullptr),
	left_(nullptr),
	right_(nullptr)
	{}
};

class Tree {
public:
	shared_ptr<Node> root_;
	// Ctor 
	Tree():
	root_(nullptr)
	{}

	shared_ptr<Node> insertBst(Node node, shared_ptr<Node> &root);
	void showInOrder(shared_ptr<Node> root);
	void showPreOrder(shared_ptr<Node> root);
	void showPostOrder(shared_ptr<Node> root);
	bool checkBstPreOrder(const shared_ptr<Node> root);
};

// insertBst nodes to tree in respect to bst rule
shared_ptr<Node> Tree::insertBst(Node node, shared_ptr<Node> &root){
	if(root == nullptr){
		root = make_shared<Node>(node);
		return root;
	}
	// if(node.key_==root_->key_){
	// 	cout << "duplicate!" << endl;
	// }
	if(node.key_<root->key_){
		Logging::print("left "+to_string(node.key_)+" "+
			to_string(root->key_), LOG);
		root->left_ = insertBst(node, root->left_);
	}
	if(node.key_>=root->key_){
		Logging::print("right "+to_string(node.key_)+" "+
			to_string(root->key_), LOG);
		root->right_ = insertBst(node, root->right_);
	}
	return root;
}

void Tree::showInOrder(shared_ptr<Node> root){
	static bool flag = true;
	
	if(flag){
		flag = false;	
		cout << "In order" << endl;
	}

	if(root!=nullptr){
		showInOrder(root->left_);
		cout << root->key_ << endl;
		showInOrder(root->right_);
	}
}

void Tree::showPreOrder(shared_ptr<Node> root){
	static bool flag = true;
	
	if(flag){
		flag = false;	
		cout << "Pre order" << endl;
	}

	if(root!=nullptr){
		cout << root->key_ << endl;
		showPreOrder(root->left_);
		showPreOrder(root->right_);
	}
}

void Tree::showPostOrder(shared_ptr<Node> root){
	static bool flag = true;
	
	if(flag){
		flag = false;	
		cout << "Post order" << endl;
	}

	if(root!=nullptr){
		showPostOrder(root->left_);
		showPostOrder(root->right_);
		cout << root->key_ << endl;
	}
}

// Check for BST in preorder traversal
bool Tree::checkBstPreOrder(const shared_ptr<Node> root){
	bool result = true;
	if(root!=nullptr){
		// Check if root is not greater than left child
		if(root->left_!=nullptr){
			Logging::print("root->left_->key_ = " +
					to_string(root->left_->key_), LOG);
			if(!(root->key_ > root->left_->key_)){
				Logging::print("$$$$$$wrong left");
				return false;
			}
		}
		
		// Check if root is not greater or equal than right child
		if(root->right_!=nullptr){
			Logging::print("root->right_->key_ = " +
					to_string(root->right_->key_), LOG);
			if(!(root->key_ <= root->right_->key_)){
				Logging::print("######wrong right");
				return false;
			}
		}

		result = checkBstPreOrder(root->left_);
		result = checkBstPreOrder(root->right_);
		return result&&result;
	}
	return true;
}

int main(){

	FileManager file;
	string path = "input/4_5.txt";
	vector<vector<long>> output;

	file.readFileNumbers(path, output,' ');
	Tree junior_tree;

	vector<long>::const_iterator it = output.at(0).begin();

	for(it;it!=output.at(0).end();++it){
		Node new_node(*it);
		Logging::print("node key = "+to_string(new_node.key_),LOG);
		junior_tree.insertBst(new_node, junior_tree.root_);
	}
	Logging::print("InOrder", LOG);
	junior_tree.showInOrder(junior_tree.root_);
	Logging::print("PreOrder", LOG);
	junior_tree.showPreOrder(junior_tree.root_);
	Logging::print("PostOrder", LOG);
	junior_tree.showPostOrder(junior_tree.root_);
	bool isBst = junior_tree.checkBstPreOrder(junior_tree.root_);
	Logging::print("Is BST? -> "+to_string(isBst));

	return 0;
}
