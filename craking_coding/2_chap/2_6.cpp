/**************************************************************************************************
@brief 		2.6 Palindrome
@details	Determine if list is palindrome.
			Palindrome is determined by comparing pair of nodes from extremities to middle point. 
			In order to update the tail, list should be browsed starting from updated head.
@author 	Marcu Cristian 
@date 		Oct,2019
*/

#include <iostream>
#include "SinglyLinkedList.hpp"
#define DELIMITER "  "

shared_ptr<Node> browsing(shared_ptr<Node> crown, shared_ptr<Node> tail){

	shared_ptr<Node> hare;
	shared_ptr<Node> status;

	// Check palindrome condition, by comparing left most head with right most tail 
	if(crown->data!=tail->data){
		status = nullptr;
		return status;
	}

	// Pointer that will browse whole list updated with last head
	hare = crown;
	// Stop before tail
	while(hare->next!=tail){
		hare = hare->next;
	}

	// Move tail to middle's list(to left)	
	tail = hare;
	// Move crown to middle's list(to right)
	crown = crown->next;

	// Stop browsing if you reach middle of list in both cases: even or odd 
	if(crown->next==hare || crown==hare){
		return crown;
	}
	// Recurse browsing
	return browsing(crown, tail);	
}

int main(){

	SinglyLinkedList list;
	int middle = 0;

	cout << "Introduce middle of the list as a number: ";
	cin >> middle;
	// Create last half of list with head equal middle 
	for(int i=0;i<=middle;i++){
		list.insert(i);
	}
	// Create first half of list and avoid already used middle
	for(int i=middle;i>=0;i--){
		list.insert(i);
	}

	// list.showList();

	shared_ptr<Node> tail;
	shared_ptr<Node> palin;

	tail = list.head;

	// Browse whole list and find tail
	while(tail->next!=nullptr){
		tail = tail->next;
	}

	// Browsing list in a recursive approach to find middle
	palin = browsing(list.head, tail);

	// Check if list is palindrome or not 
	if(palin!=nullptr){
		cout << "List is palindrome with next middle node: " << palin->data << endl;
	}
	else{
		cout << "List is not palindrome." << endl;
	}

	return 0;
}