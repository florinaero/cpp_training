/**************************************************************************************************
@brief 		2.4 Partition	
@details	Write code to partition a linked list around a value x, such that all nodes less than 
			x come before all nodes greater than or equal to x. (Important: The partition element x
			can appear anywhere in "the rigth partition"; it does not need to appear between the left and the right partitions.)
@author 	Marcu Cristian 
@date 		Oct,2019
*/

#include <iostream>
#include "SinglyLinkedList.hpp"

shared_ptr<Node> partition(shared_ptr<Node> head, int target){
	
	shared_ptr<Node> p1, p2;

	p1 = head;

	if(p1==nullptr){
		cout << "List is empty." << endl;
		return head;
	}

	if(p1->next==nullptr){
		cout << "Only one element in list." << endl;
		return head;
	}

	// Verify when you reach end of list 
	while(p1->next!=nullptr){
		if((p1->next->data) <= target){
			// Store address of compared node
			p2 = p1->next;
			// Link previous node to next one before moving
			p1->next = p1->next->next;
			// Move compared to head of list 
			p2->next = head;
			head = p2;

			// cout << "head = " << head->data << " ->" << head->next->data
			// << " ->" << head->next->next->data  << endl;
		}
		else{
			// Move to next node
			p1 = p1->next;
		}
	}


	return head;
}

int main(int argc, char** argv){
	// Create Singly linked list
	unique_ptr<SinglyLinkedList> list = make_unique<SinglyLinkedList>();

	const int target = 4;

	// for(int i=0;i<10;i++){
	// 	list->insert(i);
	// }

	list->insert(4);
	list->insert(5);
	list->insert(4);


	list->showList();

	shared_ptr<Node> tmp;

	// Verify if node is in list 
	if(list->search(target)==nullptr){
		cout << "Node is not in list!" << endl;
		return 0;
	}
	// Update head of list
	list->head = partition(list->head, target);

	list->showList();	

	return 0;
}