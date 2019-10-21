/********************************************************************
@brief 		2.1 Remove Dups
@details	Remove duplicates from an unsorted linked list.
			How would you solve this problem if a temporary buffer is
			not allowed? 
*/
#include <vector>
#include <iostream>

using namespace std;

class Node{
public:	
	int data;
	Node *next;
	Node *prev;
	Node():data(0),next(nullptr),prev(nullptr){}
	~Node(){}
};	

// Create a double linked list using nodes with 2 links
class LinkedList{
public:
	Node *phead;

	LinkedList():phead(nullptr){}
	~LinkedList(){}
	// Insert element in front of list
	void insert(Node* elem){
		elem->prev = nullptr;
		if(phead!=nullptr){
			elem->next = phead;
		}	
		phead = elem; 
		// cout << phead << " "<< elem << " "<< phead->next<<endl;
	}
};

int main(){

	int counter = 0;
	LinkedList *plist = new LinkedList();
	Node *pdum1 = new Node();
	Node *pdum2 = new Node();

	vector<int> testList = {1,1,2,3,4};
	vector<Node> nodeList(5);

	// Insert elements in list
	for(int i=0;i<nodeList.size();i++){
		//Node *pelem = new Node();
		nodeList.at(i).data = testList.at(counter);
		counter++;
		cout << "& of vec elem: "<< &nodeList.at(i) << endl;
		plist->insert(&nodeList.at(i));
		// delete pelem;
	}

	while(plist->phead!=nullptr){
		cout << plist->phead->data << endl;
		plist->phead = plist->phead->next;
	}

	delete plist;
	delete pdum1;
	delete pdum2;
	return 0;
}

