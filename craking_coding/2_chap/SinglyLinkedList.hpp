
#ifdef SINGLYLINKEDLIST_
#define SINGLYLINKEDLIST_

#include <iostream>

class Node{
public:
	int data;
	shared_ptr<Node> next;

	Node(int data_):
	data(data_){}

	Node()=delete;
};

class SinglyLinkedList{
public:
	shared_ptr<Node> head;

	SinglyLinkedList();

	void insert(int data){
		// Create a new node with corresponding data
		shared_ptr<Node> elem = make_shared<Node>(data);
		// Check if list is not empty
		if(head!=nullptr){
			elem->next = move(head);	
		}
		head = elem;
	}

	// Return head of list
	shared_ptr<Node> remove(int data){
		shared_ptr<Node> elem = search(data);
		// cout << elem->data << endl;
		shared_ptr<Node> temp;
		// Element not found or list is empty 
		if(elem==nullptr){
			return nullptr;
		}

		// Case when head is removed
		if(head==elem){
			head = head->next;
			return head;
		}

		temp = head;
		// Stop one node before element that will be removed
		while(temp->next!=elem){
			temp = temp->next;
		}

		// Initial object pointed by temp->next is destroyed after assignment because all 
		// shared_ptr release the ownership of that object
		temp->next = elem->next;

		return head;
	}

	shared_ptr<Node> search(int data){
		shared_ptr<Node> dum;

		if(head==nullptr){
			return nullptr;
		}
		dum = head;

		while(dum->data!=data){
			dum=dum->next;
			if(dum==nullptr){
				return dum;
			}
		}
		return dum;
	}

	void showList(){

		shared_ptr<Node> temp;

		if(head==nullptr){
			cout << "List is empty." << endl;
		}

		temp = head;		
		while(temp!=nullptr){
			cout << temp->data;
			temp=temp->next;
			if(temp!=nullptr){
				cout << "->";
			}
			else{
				cout << endl;
			}
		}
	}
};

#endif