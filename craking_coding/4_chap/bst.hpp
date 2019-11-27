/*************************************************************************************************/
/**
@brief 		
@details	
@author 	Marcu Cristian
@date 		2019-11-13 00:02:10
->Last Modified by:   Marcu Cristian
->Last Modified time: 2019-11-27 00:05:58
*/
/*************************************************************************************************/

#ifndef BST_
#define BST_

#include <memory>
#include <cmath>
#include <vector>
#include "treeNode.hpp"

/**
@brief This class creates a binary search tree(Bst) and contains regular methods
*/
template <class K>
class Bst{
public: 
	std::unique_ptr<TreeNode<K>> m_head;
	int m_levels;
	// Ctor
	Bst(){};

	/**
	@brief				Print bst to console starting from root 
	@param[in] 	node 	Bst root
	@return				void
	*/
	void showBst(std::shared_ptr< TreeNode<K> > root){

		std::vector<std::shared_ptr<TreeNode<K>>> levelNodes;

		// Indentation of root node
		for(int i=0;i<m_levels;i++){
			std::cout << "    ";	
		}
		std::cout << "  ";
		std::cout << root->m_key << "\n" << std::endl;
		
		levelNodes.push_back(root);
		for(int i=0;i<m_levels;i++){
			for(int j=0;j<(1<<i);j++){
				// Break before last level to avoid storing nullptr
				if(i==m_levels-1){break;}
				levelNodes.push_back(levelNodes[j]->m_left);
				levelNodes.push_back(levelNodes[j]->m_right);
			}
			// Remove parent nodes by erasing number of nodes of level
			levelNodes.erase(levelNodes.begin(),levelNodes.begin()+(1<<i));
			// Indentation of tree level
			for(int s=0;s<m_levels-i;s++){
				std::cout << "    ";
			}
			

			for(auto node : levelNodes){
				if(node!=nullptr){
					std::cout << node->m_key;
					// for(int s=0;s<m_levels-i+1;s++){
						std::cout << "  ";
					// }
				}
			}
			std::cout << "\n"<< std::endl;
		}
	}

	void insertNode(TreeNode<K> node){
		m_head = node;
	}
	/**
	@brief				Find number of levels for a binary tree
	@param[in] 	nodes	Number of nodes of a binary tree
	@return				Number of levels for a binary tree considering root. 
	*/
	void setLevels(int totalNodes){
		m_levels = ceil(log(totalNodes+1)/log(2));	
	};
};

#endif 