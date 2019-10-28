/**************************************************************************************************
@brief 		2.3 Delete Middle node
@details	Implement an algorithm to delete a node in the middle (i.e.,
			any node but the first and last node not necessarily the exact in the middle) of a singly 
			linked list, given only access to that node.  
			of singly linked list.
@author 	Marcu Cristian 
@date 		Oct,2019
*/

#include <iostream>
#include "SinglyLinkedList.hpp"

using namespace std;

int main(){

	unique_ptr<SinglyLinkedList> list = make_unique<SinglyLinkedList>();

	for(int i=0;i<5;i++){
		list->insert(i);
	}
	cout << "Initial list:" << endl;
	list->showList();

	for(int i=0;i<4;i++){
		list->remove(i);
	}
	list->remove(4);
	list->showList();

	return 0;
}