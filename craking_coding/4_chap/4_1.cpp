/*************************************************************************************************/
/**
@brief 		4.1 Route between nodes 	
@details	Find if there is a route between to given nodes in a given directed graph. 
			Read input from file. Uses BFS.
@author 	Marcu Cristian 
@date 		Oct,2019
*/
/*************************************************************************************************/

#include <iostream>     
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept> 
#include <map>
#include <queue>

using namespace std;
/**
@brief This class represents a node from tree
*/
class Node{
public:
	int m_data;
	bool m_visited;
	// Array of indices(children) to nodes of adj list 
	vector<int> m_children;
	// Ctor
	Node():
	m_data(0),
	m_visited(false){} 
};

// This class reads the input of a tree from a file and stores it in a adjacency list
class ReadTree{
public:
	// Create adjacency list of Nodes type 
	vector<Node> m_adjList;
	string m_fileName;
	int m_total;
	// Pairs data node with its index in adj list
	map<int, int> m_mapNodes;

	// Ctor
	ReadTree(string fileName):
	m_fileName(fileName),
	m_total(0)
	{
		readFile();
	}

	// Split a string into integer vector
	vector<int> split(string in, char delim){
		// Create stream from string 
		stringstream stream(in);
		vector<int> list;
		string elem = "";

		// Return empty vector if string is empty
		if(in.empty()){
			return list;
		}
		while(getline(stream, elem, delim)){
			try{
				list.push_back(stoi(elem));
			}
			catch(const invalid_argument& ia){
				cerr << "Invalid argument: " << ia.what() << '\n';
				break;
				return list;
			}
			catch(const out_of_range& oor){
				cerr << "Out of Range error: " << oor.what() << '\n';
				break;
				return list;
			}
		}
		return list;
	}

	// Read file with tree content
	int readFile(){
		int counter = 0;
		string line = "";
		vector<int> temp;
		int index = 0;
		int rootIndex = 0;
		int elem = 0;

		ifstream file(m_fileName,ios_base::in);

		if(!file.good()){
			cout << "Couldn't open file!" << endl;
			return 0;
		}
		// Read number of total nodes 
		file >> m_total;
		// Allocate space for total number of node
		m_adjList.resize(m_total);

		// Read links between nodes
		while(getline(file, line)){
			temp = split(line, ' ');
			if(!temp.empty()){
				// Loop through all elements of line			
				for(int i=0;i<temp.size();i++){
					elem = temp.at(i);
					// cout << " elem = " << elem << endl;
					// Search if node was already met before and initialized
					map<int, int>::iterator itMap = m_mapNodes.find(elem);
					
					// If node doesn't exist then it should be initialized 
					if(itMap==m_mapNodes.end()){
						index = counter++;
						// Initialize node 
						m_adjList.at(index).m_data = elem;
						
						// Operator[] creates element in map
						// Mapping 'data node' as key to index of node 
						m_mapNodes[elem] = index;	
					}
					else{
						// Index of node in adj list 
						index = itMap->second;
					}
					// Check if is first node from line
					if(i==0){
						rootIndex = index;
					}					

					// Skip adding children to first node from line 
					if(i>0){
						m_adjList.at(rootIndex).m_children.push_back(index);
					}
				}
			}
		}
		file.close();

		return 0;
	}
};

/**
@brief This class keeps graph search algorithms
*/
class GraphSearch{
public: 
	GraphSearch(){};
	// Search node starting from root using Breadth-first Search and return shortest path
	// In case stop node is not found return 0
	static int bfs(shared_ptr<vector<Node>> ptrAdj, map<int,int> graphMap, int root, int searched){
		queue<Node> qStorage;
		Node last;
		Node rootNode;
		Node childNode;
		int i = 0;
		// Distance for each node
		std::vector<int> distance(ptrAdj->size(),0);

		// cout << "root = " << ptrAdj->at(graphMap.at(root)).m_data << endl;
		// Mark root node as visited
		ptrAdj->at(graphMap.at(root)).m_visited = true;
		// Push data at end of node in queue
		qStorage.emplace(ptrAdj->at(graphMap.at(root)));

		while(!qStorage.empty()){
			// Used for breaking infinite loops
			i++;
			if(i>100){
				cout << "Stopped at line " << __LINE__ << endl;
				break;
			}
			// Get Node 
			last = qStorage.front();
			// Remove node 
			qStorage.pop();
			for(auto child : last.m_children){
				// cout << "child = " << ptrAdj->at(child).m_data << endl;
				// Get index of last node popped out
				map<int,int>::iterator itLast = graphMap.find(last.m_data); 
				// Increase distance for actual node
				distance.at(child) = distance.at(itLast->second) + 1;  
				// Check if node was found
				if(ptrAdj->at(child).m_data == searched){
					return distance.at(child);
				}
				// Check if node was already visited
				if(ptrAdj->at(child).m_visited==false){
					// Mark node as visited
					ptrAdj->at(child).m_visited = true;
					// Add node to queue
					qStorage.emplace(ptrAdj->at(child));
					// cout << "node = " << ptrAdj->at(child).m_data << endl;
				}
			}
		}
		return 0;		
	}
};


int main(){
	string fileName = "input/4_1.txt";
	int start = 0;
	int stop = 0;
	int bfs = 0;
	
	cout << "Start node: ";
	cin >> start;
	cout << "Stop node: ";
	cin >> stop; 
	// Read file and stores tree data in a adjacency list
	ReadTree tree(fileName);
	bfs = GraphSearch::bfs(make_shared<vector<Node>>(tree.m_adjList), tree.m_mapNodes, start, stop);
	
	if(bfs){
		cout << "Node was found! ";
		cout << "Shortest path: " << bfs << endl;	
	}
	else{
		cout << "Node was not found!" << endl;
	}
	

	cout << "All nodes: " << endl;
	for(auto node : tree.m_adjList){
		cout << node.m_data << " ";
		for(auto child : node.m_children){
			cout << tree.m_adjList.at(child).m_data << " ";
		}
		cout << endl;
	}

	return 0;
}
