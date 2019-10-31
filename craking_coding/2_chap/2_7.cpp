/**************************************************************************************************
@brief 		2.7 Intersection	
@details	Determine if 2 lists intersect and return intersecting node.
@author 	Marcu Cristian 
@date 		Oct,2019
*/

#include <iostream>
#include "SinglyLinkedList.hpp"
#define DELIMITER "  "

int main(int argc, char** argv){

	// Create 2 lists for trials
	unique_ptr<SinglyLinkedList> list1 = make_unique<SinglyLinkedList>();
	unique_ptr<SinglyLinkedList> list2 = make_unique<SinglyLinkedList>();

	// Insert elements in lists 
	for(int i=1;i<10;i++){
		list1->insert(i);
		list2->insert(i*3);
	}


	cout << "list1" << endl;
	list1->showList();
	cout << "list2" << endl;
	list2->showList();


	// Create intersection of nodes
	if(stoi(argv[1])){
		shared_ptr<Node> intersectNode = list2->head->next->next;
		intersectNode->next = list1->head->next->next->next; 
		cout << "Intersection node: " << intersectNode->next->data << endl;
	}

	cout << "list1" << endl;
	list1->showList();
	cout << "list2" << endl;
	list2->showList();

	shared_ptr<Node> runner1;
	shared_ptr<Node> runner2;
	// 2 pointer that go until end of lists
	runner1 = list1->head;
	runner2 = list2->head;
	int steps1 = 0;
	int steps2 = 0;
	int gap = 0;
	// Get last node and cound no of node
	while(runner1->next!=nullptr){
		runner1=runner1->next;
		steps1++;
	}
	while(runner2->next!=nullptr){
		runner2=runner2->next;
		steps2++;
	}

	cout << "steps1=" << steps1 << DELIMITER << "steps2=" << steps2 << endl;

	if(runner1==runner2){
		cout << "Lists do intersect." << endl;
		// Find gap between lists and which one is bigger	
		gap = steps1 - steps2; 

		runner1 = list1->head;
		runner2 = list2->head;
		
		if(gap>0){
			for(int i=0;i<gap;i++){
				runner1 = runner1->next;
			}
		}
		else{
			for(int i=0;i<abs(gap);i++){
				runner2 = runner2->next;
			}
		}

		// Loop until you find intersection node
		while(runner1!=runner2){
			runner1 = runner1->next;
			runner2 = runner2->next;
		}

		cout << "Intersection node: " << runner1->data << endl;

		return 0;
	}

	// List do not intersect
	cout << "Lists do not intersect!" << endl;		

	return 0;
}