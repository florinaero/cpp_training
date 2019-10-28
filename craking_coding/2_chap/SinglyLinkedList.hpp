
#ifndef SINGLYLINKEDLIST_
#define SINGLYLINKEDLIST_

#include <iostream>

using namespace std;

class Node{
public:
	int data;
	shared_ptr<Node> next;

	Node(int data_);
	Node()=delete;
};

class SinglyLinkedList{
public:
	shared_ptr<Node> head;

	SinglyLinkedList(){}

	void insert(int data);

	// Return head of list
	shared_ptr<Node> remove(int data);

	shared_ptr<Node> search(int data);

	void showList();
};

#endif