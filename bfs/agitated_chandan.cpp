#include <iostream>
#include <vector>

using namespace std;

int main(){
	
	int tests;
	int nodes;
	int node1, node2, weight;
	
	cin >> tests;
	cin >> nodes;

	vector< pair<int,int> > graph[nodes];

	for(int i=0;i<nodes*3;i++){
		cin >> node1;
		cin >> node2;
		cin >> weight;
		graph[node1].push_back(make_pair(node2, weight));
	}
}