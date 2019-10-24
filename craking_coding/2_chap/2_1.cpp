/********************************************************************
@brief 		2.1 Remove Dups
@details	Remove duplicates from an unsorted linked list.
			How would you solve this problem if a temporary buffer is
			not allowed? 
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
	Node *next;
	Node *prev;
	Node():data(0),next(nullptr),prev(nullptr){}
	~Node(){}
};	

// Create a double linked list using nodes with 2 links
class LinkedList{
public:
	Node *phead;

	// unique_ptr<Node> phead;

	LinkedList():phead(nullptr){}
	~LinkedList(){}
	
	// Insert element in front of list
	void insert(Node *elem){
		elem->prev = nullptr;
		if(phead!=nullptr){
			elem->next = phead;
			phead->prev = elem;
		}	
		phead = elem; 
		// cout << phead << " "<< elem << " "<< phead->next<<endl;
	}

	// Remove specific node from list
	Node* removeNode(Node *elem){
		if(phead==nullptr){
			return nullptr;
		}

		// Move head before changing references
		if(elem==phead){
			phead = phead->next;
		}
		else{
			elem->prev->next = elem->next;
		}

		// In case is removed the last node, check current phead
		if(phead==nullptr){
			return nullptr;
		} 

		if(elem->next!=nullptr){
			elem->next->prev = elem->prev;
		}

		return phead;
	}

	// Remove node from list searching after data
	Node* remove(int data){
		if(phead==nullptr){
			return nullptr;
		}

		// Search node that has the corresponding data
		Node *dum = search(data);
		cout << "searched addr: " << dum << endl;	
		// Return null in case node is not found
		if(dum==nullptr){
			return nullptr;
		}

		// Case when data is found on head, move head to next node, \
		// otherwise you can change pointer of prev
		if(dum==phead){
			phead = phead->next;
		}
		else{
			// Change prev reference to next of removed node
			dum->prev->next = dum->next;
		}

		// In case is removed the last node, check current phead
		if(phead==nullptr){
			return nullptr;
		} 

		// In case is removed tail of list
		if(dum->next!=nullptr){
			// Change Prev of found->next to found node
			dum->next->prev = dum->prev;
		}

		return phead;
	}

	// Search node in list 
	Node* search(int data){
		Node* dynam;

		dynam = phead;

		if(phead == nullptr){
			return nullptr;
		}

		while(dynam!=nullptr){
			if(dynam->data==data){
				return dynam;
			}
			dynam = dynam->next;
		}
		// Return null in case node is not found
		return nullptr;
	}


	// Check list for duplicates by comparing each combination
	int removeDupl(){

		if(phead==nullptr){
			cout << "List is empty." << endl;
			return 0; 
		}

		// Return false for only one element
		if(phead->next==nullptr){
			cout << "List has less than 2 elements." << endl;
			return 0;
		}

		int dupl = 0;
		Node *test = nullptr;
		// Node that is compared with all nodes until end
		Node *dum1 = phead;
		// Node that slides in list in order to be compared
		Node *dum2 = phead->next;

		// Loop until the n-1 node
		while(dum1->next!=nullptr){
			// cout << "dum1=" << dum1->data << " dum2=" << dum2->data << endl;

			if(dum1->data==dum2->data){
				// Remove node 
				test = removeNode(dum2);
				// showList();
				// Count duplicates
				dupl++;
			}
			// Move sliding node to tail
			dum2 = dum2->next;
			// Check if is reached tail of list and update both nodes
			if(dum2==nullptr){
				// In case of reaching end of list and removal of last node 
				if(dum1->next==nullptr){
					return dupl;
				}
				dum1 = dum1->next;
				dum2 = dum1->next;
			}
		}

		return dupl;	
	}

	void showList(){
		Node *dum = phead;
		cout << "------------" << endl;
		cout << "List:" << endl;
		while(dum!=nullptr){
			cout << dum->data << "  " << dum << endl;
			dum = dum->next;
		}
		cout << "------------" << endl;
	}
	
};

int main(){

	int counter = 0;
	int dupl = 0;
	// LinkedList *plist = new LinkedList();
	unique_ptr<LinkedList> plist(new LinkedList());
	// unique_ptr<LinkedList> plist = make_unique<LinkedList>();

	vector<int> testList = {1,1,2,3,4,4,5,5,5,5,0,0,0,0,0};
	// vector<int> testList = {};
	vector<Node> nodeList(testList.size());

	// Insert elements in list
	for(int i=0;i<nodeList.size();i++){
		//Node *pelem = new Node();
		nodeList.at(i).data = testList.at(counter);
		counter++;
		// cout << "& of vec elem: "<< &nodeList.at(i) << endl;
		plist->insert(&nodeList.at(i));
		// delete pelem;
	}

	// Node *test;
	// test = plist->remove(1);
	// test = plist->remove(2);
	// test = plist->remove(9);
	// test = plist->remove(4);
	// test = plist->remove(3);

	// Show initial list
	cout << "Initial list:" << endl;
	plist->showList();

	dupl = plist->removeDupl();
	cout << "duplicates = " << dupl << endl;

	if(plist->phead!=nullptr){
		cout << "head = " << plist->phead->data << endl;
		plist->showList();		
	}

	return 0;
}

