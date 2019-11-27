/*************************************************************************************************/
/**
@brief 		4.3 List of Depths
@details	Given a binary tree create a list for each level.
			Traverse each level of tree.
@author 	Marcu Cristian
@date 		2019-11-19 00:30:33
->Last Modified by:   Marcu Cristian
->Last Modified time: 2019-11-25 21:12:43
*/
/*************************************************************************************************/

#include <iostream>
#include <cmath>
// User's libraries
#include "fileManager.hpp"

using namespace std;

struct Node{
	int data;
	shared_ptr<Node> next;
	shared_ptr<Node> prev;
	// Ctor
	Node(int new_data):
	data(new_data),
	next(nullptr),
	prev(nullptr)
	{}; 
};

class List{
public:
	shared_ptr<Node> head;
	// Ctor
	List():head(nullptr){};

	void insertNode(long data){
		shared_ptr<Node> paco = make_shared<Node>(data);
		if(head!=nullptr){
			paco->next = move(head);
		}
		head=paco;
	}

	void showList(){
		while(head!=nullptr){
			cout << head->data;
			if(head->next!=nullptr){
				cout << "->";	
			}
			head = head->next;
		}
	}
};

int main(){
	
	vector< vector<long> > input;
	int levels{0};
	int index{0};
	int totalNodes{0};
	int nodes{0};
	vector<List> floors;

	// Read file line by line 
	FileManager::readFileNumbers("input/4_2.txt", input);

	// Total number of nodes 
	totalNodes = input[0].size();
	cout << "totalNodes = " << totalNodes << endl;

	// Find number of levels
	levels = ceil(log(totalNodes+1)/log(2));
	cout << "levels = " << levels << endl;

	for(int n=0;n<levels;n++){
		// Number of theoretically nodes on tree level
		nodes = pow(2,n);
		//Create list
		List listLevel;
		// Loop over nodes of one level
		for(int j=0;j<nodes;j++){
			listLevel.insertNode(input[0][j+index]);
			// Stop after last node
			if(j+index==totalNodes){
				break;
			}
		}
		// Store list of levels
		floors.push_back(listLevel);
		// Update index to the beginning of tree's level
		index = index + nodes;
	}

	// Show levels of tree as lists
	for(auto& list : floors){
		list.showList();
		cout << endl;
	}

	return 0;
}