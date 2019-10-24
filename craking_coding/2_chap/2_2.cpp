/********************************************************************
@brief 		2.2 Return Kth to last
@details	Implement an algorithm to find the k-th to last element 
			of singly linked list.
			It is done using 2 raw pointers.
@author 	Marcu Cristian 
@date 		Oct,2019
*/

#include <vector>
#include <iostream>

using namespace std;

class Node{
public:
	int data;
	shared_ptr<Node> next;

	Node():data(0),next(nullptr){};	
};

class SinglyLinkedList{
public:
	shared_ptr<Node> head;
	SinglyLinkedList(){};

	void insert(int elem){
		// Node node;
		shared_ptr<Node> node = make_shared<Node>();	

		node->data = elem;
		node->next = head;
		head = node;
	}

	void showList(){
		cout << "List content" << endl;
		cout << "------------" << endl;
		if(head==nullptr){
			cout << "empty list" << endl;  
		}

		shared_ptr<Node> temp;
		temp = head;

		while(temp!=nullptr){
			cout << temp->data;
			temp = temp->next;
			if(temp!=nullptr){
				cout << "->";
			}
		}
		cout << "\n------------" << endl;
	}

	// Return kth element to last element of list
	int kthElem(int position){

		vector<shared_ptr<Node>> nodes;
		shared_ptr<Node> dum;
		int last = 0;

		dum = head;

		while(dum!=nullptr){
			nodes.push_back(dum);
			dum = dum->next;
		}

		// Position of last element
		last = nodes.size() - 1;
		if(last<0){
			cout << "empty list" << endl;
			return -1;
		}
		if(last-position<0){
			cout << "Element is outside of list." << endl;
			return -1;
		}
		else{
			// Get kth element
			dum = nodes.at(last-position);
		}

		return dum->data;
	}
};

int main(int argc, char** argv){

	int result = 0;

	unique_ptr<SinglyLinkedList> sList = make_unique<SinglyLinkedList>();

	for(int i=0;i<10;i++){
		sList->insert(i*2);
	}	

	sList->showList();
	
	result = sList->kthElem(stoi(argv[1]));
	if(result!=-1){
		cout << "Kth to last = " << result << endl;
	}

	return 0;
}
