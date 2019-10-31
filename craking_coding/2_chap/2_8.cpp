/**************************************************************************************************
@brief 		2.8 Loop Detection	
@details	Given a linked list which might contain a loop, implement an algorithm that returns 
			the node at the begining of the loop.
			Input for program before running is LOOP NODE.
@author 	Marcu Cristian 
@date 		Oct,2019
*/

#include <iostream>
#include "SinglyLinkedList.hpp"

int main(int argc, char** argv){

	int loopSize = 0;
	int steps = 0;
	unique_ptr<SinglyLinkedList> list = make_unique<SinglyLinkedList>();

	for(int i=20;i>=0;i--){
		list->insert(i);
	}

	list->showList();

	shared_ptr<Node> tmp;
	// Create a loop 
	tmp = list->search(8);
	cout << "Node before loop node: " << tmp->data << endl;
	cout << "head = " << list->head->data << endl;
	tmp->next = list->search(stoi(argv[1]));
	cout << "loop node = " << tmp->next->data << endl;
	
	shared_ptr<Node> slow;
	shared_ptr<Node> fast;

	slow = list->head->next;
	fast = slow->next;

	while(slow!=fast){
		cout << "runners = " << slow->data << "  " << fast->data << endl;
		slow = slow->next;
		if(fast->next==nullptr || fast->next->next==nullptr){
			cout << "No loop!" << endl;
			return 0;
		}
		fast = fast->next->next;
	}

	cout << "Meeting node has key = " << slow->data << "  " << fast->data << endl;
	cout << "There is a loop in list." << endl;
	
	// Move one of pointers to head
	slow = list->head;

	// Loop with one node step until pointers meet
	while(slow!=fast){
		slow = slow->next;
		fast = fast->next;
	}

	cout << "LOOP NODE = " << slow->data << endl;
	
	return 0;
	
}