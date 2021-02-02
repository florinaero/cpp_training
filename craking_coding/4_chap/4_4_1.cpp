
#include<memory>
#include<vector>
#include<cmath>
#include<algorithm>
#include<iostream>

using namespace std;

struct TreeNode {
	shared_ptr<TreeNode> left;
	shared_ptr<TreeNode> right;
	int data;

	TreeNode(int data) :
		left(nullptr),
		right(nullptr),
		data(data) {}

	int insert(unique_ptr<TreeNode> root, int data) {
		if (root == nullptr) {
			return 0;
		}

		root->data = data;
		return 1;
	}
};

typedef shared_ptr<TreeNode> node;

node insertOrderLevel(node root, int index, int size, int arr[]) {
	if (index < size) {
		auto newNode = make_shared<TreeNode>(arr[index]);
		root = newNode;

		cout << "insert: " << arr[index] << endl;
		newNode->left = insertOrderLevel(newNode->left, 2 * index + 1, size, arr);
		newNode->right = insertOrderLevel(newNode->right, 2 * index + 2, size, arr);
	}
	return root;
}

void inOrder(node root) {
	if (root != nullptr) {
		inOrder(root->left);
		cout << root->data << endl;
		inOrder(root->right);
	}
}

void preOrder(node root) {
	if (root != nullptr) {
		cout << root->data << endl;
		preOrder(root->left);
		preOrder(root->right);
	}
}

void postOrder(node root) {
	if (root != nullptr) {
		postOrder(root->left);
		postOrder(root->right);
		cout << root->data << endl;
	}
}

void test() {
	cout << "test" << endl;
}

int getHeight(node root) {
	if (root == nullptr) {
		return -1;
	}
	return max(getHeight(root->left), getHeight(root->right)) + 1;
}
bool isBalanced(node root) {
	if(root==nullptr){
		return true;
	}

	int delta = abs((getHeight(root->left) - getHeight(root->right)));
	if (delta > 1) {
		return false;
	}
	else {
		return isBalanced(root->left) && isBalanced(root->right);
	}
}

int main() {

	// auto root = make_shared<TreeNode>(0);
	const int noNodes = 100;
	int levels = ceil(log2(noNodes));
	int arr[] = { 1,2,3,4,5,6,7,8,9 };

	int size = sizeof(arr) / sizeof(arr[0]);

	node root = insertOrderLevel(root, 0, size, arr);

	inOrder(root);
	cout << "Height: " << getHeight(root) << endl;

	bool balanced = isBalanced(root);
	cout << "Is balanced: " << boolalpha << balanced << endl;
	return 0;
}