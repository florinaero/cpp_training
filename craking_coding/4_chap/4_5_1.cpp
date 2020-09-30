#pragma once
#include <memory>
#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
	int val;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node> right;
	Node(int val) :
		val(val),
		left(nullptr),
		right(nullptr)
	{}
};


typedef std::shared_ptr<Node> node_ptr;

class Bst {
public:
	node_ptr insertOrderLevel(node_ptr root, int index, std::vector<int> val) {
		if (index < val.size() && val[index] != -1) {
			// Create a new node 
			auto node = std::make_shared<Node>(val[index]);
			root = node;
			// std::cout << root->val << std::endl;
			node->left = insertOrderLevel(node->left, 2 * index + 1, val);
			node->right = insertOrderLevel(node->right, 2 * index + 2, val);
		}
		return root;
	}

	bool isValidBST(node_ptr root) {
		bool result = true;
		if (root != nullptr) {
			if (root->left != nullptr) {
				if (root->left->val >= root->val) {
					std::cout << "root->val: " << root->val
						<< " left: " << root->left->val << std::endl;
					return false;
				}
			}

			if (root->right != nullptr) {
				if (root->right->val <= root->val) {
					std::cout << "root->val: " << root->val
						<< " right: " << root->right->val << std::endl;
					return false;
				}
			}

			result = isValidBST(root->left);
			result = isValidBST(root->right);
			return result && result;
		}
		return true;
	}

	void inOrder(node_ptr root) {
		if (root != nullptr) {
			inOrder(root->left);
			std::cout << root->val << std::endl;
			inOrder(root->right);
		}
	}

	void preOrder(node_ptr root) {
		if (root != nullptr) {
			std::cout << root->val << std::endl;
			preOrder(root->left);
			preOrder(root->right);
		}
		else {
			// std::cout << "is null" << std::endl;
		}
	}

	bool flag = false;
	int lastData = -1;

	// Nodes of BST should be sorted if they are read in order, in this should always 
	// be checked if previous visited node is smaller than actual one
	bool detectBST(node_ptr root) {
		if (root == nullptr) {
			return true;
		}

		if (detectBST(root->left) == false) {
			return false;
		}

		if (root->right != nullptr || root->left != nullptr) {
			std::cout << "last data: " << lastData << " root->data: " << root->val << std::endl;
		}

		if (lastData >= root->val && flag) {
			std::cout << "not bst" << std::endl;
			std::cout << "last data: " << lastData << " root->data: " << root->val << std::endl;
			return false;
		}

		flag = true;
		// Store data of node that will be used for comparison at next visited node
		lastData = root->val;

		if (detectBST(root->right) == false) {
			return false;
		}
		return true;
	}

	bool detectBstMinMax(node_ptr root, int min, int max) {
		if (root == nullptr) {
			return true;
		}

		if (root->val<min || root->val>max) {
			return false;
		}
		bool result = detectBstMinMax(root->left, min, root->val);
		result = result && detectBstMinMax(root->right, root->val, max);
		return result;
	}
};

void probl4_5() {
	Bst temp;

	//vector<int> arr = {1,2,3,4,5,6,7,8,9};
   //vector<int> arr = { 6,4,8,3,5,7,9 }; // BST
	vector<int> arr = { 6,4,9,3,5,7,10 }; // not BST
	//vector<int> arr = { 6,4,8,3,5,-2,9 }; // not BST -2 should be 7
	// vector<int> arr = {10,5,15,-1,-1,6,20};//,8,9};
	node_ptr root;
	root = temp.insertOrderLevel(root, 0, arr);

	cout << "in order: " << endl;
	temp.inOrder(root);


	cout << "pre order: " << endl;
	temp.preOrder(root);
	cout << "Result:" << endl;
	bool result = { false };
	// result = temp.isValidBST(root);

	result = temp.detectBST(root);
	cout << boolalpha << result << endl;

	cout << "Version 2" << endl;
	cout << temp.detectBstMinMax(root, INT_MIN, INT_MAX) << endl;
}

int main() {

	// Probl 4_5 detect bst
	probl4_5();

	return 0;
}