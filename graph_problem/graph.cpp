/*
You have been given an undirected graph consisting of N nodes and M edges. This graph can consist of self-loops as well as multiple edges. In addition , you have also been given Q queries. For each query , you shall be given 2 integers A and B. You just need to find if there exists an edge between node A and node B. If yes, print "YES" (without quotes) else , print "NO"(without quotes).

Input Format:

The first line consist of 2 integers N and M denoting the number of nodes and edges respectively. Each of the next M lines consist of 2 integers A and B denoting an undirected edge between node A and B. The next line contains a single integer Q denoting the number of queries. The next Line contains 2 integers A and B denoting the details of the query.

Output Format

Print Q lines, the answer to each query on a new line.*/

#include <iostream>

using namespace std;

int main(){
	
	int nodes=0;
	int edges=0;
	int queries=0;
	int qElem1=0;
	int qElem2=0;
	int A=0;
	int B=0;

	// Create a pointer to pointer
	int** ptrAdj=NULL;
	
	// Define graph by reading nodes and edges
	cout<<"nodes"<<endl;
	cin>>nodes;
	cout<<"edges"<<endl;
	cin>>edges;
	
	//Initialize adj matrix
	// create an array of pointers for int 
	ptrAdj=new int* [nodes];
	// 
	for(int p=0;p<nodes;++p){
		// For each addr allocate mem for an array of int 
		ptrAdj[p]= new int[nodes];
	}

	for(int j=0;j<nodes;++j){
		for(int k=0;k<nodes;k++){
			ptrAdj[j][k]=0;
		}
	}
	// Fill adjancey matrix
	for(int i=0;i<edges;++i){
		cout<<"pair: "<<i<<endl;
		cin>>A>>B;
		ptrAdj[A][B]=1;
		ptrAdj[B][A]=1;	
	}	
	
	// Read number of queries 
	cout<<"queries:"<<endl;
	cin>>queries;
	
	for(int i=0;i<queries;++i){
		cin>>qElem1>>qElem2;
		if(ptrAdj[qElem1][qElem2]==1){
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}

	// Free memory 
	for(int i=0;i<nodes;++i){
		delete [] ptrAdj[i];
	}
	delete [] ptrAdj;
	

return 0;
}
