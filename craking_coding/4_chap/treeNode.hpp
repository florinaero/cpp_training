#include <memory>
#include <iostream>

/**
@brief This class creates a node for a binary tree
*/
template <class K>
class TreeNode{
public:
	K m_key;
	std::shared_ptr<TreeNode> m_left;
	std::shared_ptr<TreeNode> m_right;
	std::shared_ptr<TreeNode> m_parent;

	// Ctor
	TreeNode(K key):
	m_key(key),
	m_left(nullptr),
	m_right(nullptr),
	m_parent(nullptr)
	{
		// static int counter = 0;
		// counter++;
		// std::cout << "new "<< counter << std::endl;
	}
};