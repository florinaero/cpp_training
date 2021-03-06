/* Everyone knows that some special Pikachus hate evolving into Raichus. (The legend says because
Raichu is ugly, and Pikachu looks good!)

The question is how do we find these special Pikachus who hate evolution? 
The crazy Poke'mon trainer Ash Catch'Em has derived a random algorithm, which is completely wrong, 
but since he's your friend, you've to humor him and his crazy algorithms.

He thinks if you are given N Pikachus in an array, A1,A2 ... AN, where each Pikachu is denoted by 
an integer. The total number of unique pairs (Ai,Aj) where i < j is the number of Pikachus who
hate evolution.
  
Input format: The first line will consist of a single integer N. The second line consists of N
integers A1,A2 ... AN.

Output format: Output the total number of unique pairs (Ai,Aj) that can be formed, which will also
be the number of special Pikachus.

Constraints: 1 ≤ N ≤ 2 * 10E+5 1 ≤ Ai ≤ 10E+9

5 1 2 2 1 3 SAMPLE OUTPUT  6 Explanation All the possible pairs are 
(1,1), (1,2), (1,3), (2,1), (2,2), (2,3). */

#include <fstream> 
#include <vector> 
#include <string> 
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

class Electric{

protected: 
	int m_noOfElements; 
	vector<int> m_elements; 
	string m_pathFile;
	long m_noOfPairs;

public: 
	vector< vector<pair<int,int>> > m_hashTable;

	// ctor 
	Electric() {	
		readingInput();
		// compute no of possible pairs
		m_noOfPairs = 3967;//(m_noOfElements * (m_noOfElements-1)) / 2;

		// Create hash table with the maximum of possible pairs
		pair<int,int> tempPair(0,0);
		m_hashTable.resize(m_noOfPairs);
	}

	// hash function 
	long hashing(int elem1, int elem2, int index1, int index2){
		return ((2*elem1+elem2) % m_noOfPairs);
	}

	// Read input 
	void readingInput(){
		int element{0};

		cin >> m_noOfElements;
		while(cin >> element){
			m_elements.push_back(element);
		}

	}

	// Insert function in hash table 
	void insert(int elem1, int elem2, int index1, int index2){
		long index {0};
		int pwr {0};

		pair<int,int> newPair(elem1, elem2);

		index = hashing(elem1, elem2, index1, index2);

		try{
			// Check if the new pair is already in hash table
			// while(m_hashTable.at(index)!=newPair && m_hashTable.at(index)!=make_pair(0,0)){
			// 	// Linear probing 	
			// 	index = (index + 1) % m_noOfPairs;
			// 	pwr++;
			// 	// cout << "index: " << index <<" pwr: " << pwr << endl;
			// 	if(pwr>3000){
			// 		cout << "";
			// 	} 
			// }
			// Insert pair in hashTable
			m_hashTable.at(index).push_back(newPair);
		}
		catch(out_of_range oor){
			cout << "Out of range at line " << __LINE__;
		}
	}

	// Create pairs where i>j for Ai and Aj of input array
 	void processElem(){
 		vector<int>::iterator Jt;
 		vector<int>::iterator It = m_elements.begin();
 		int index1{0};
 		int index2{0};
 		int counter{0};

		for(;It!=m_elements.end()-1;++It){
 			index1 = It - m_elements.begin();
 			// Start from the second element
 			for(Jt=It+1;Jt!=m_elements.end();++Jt){
				index2 = Jt - m_elements.begin();
				// Insert element in hash table 
				insert((*It), (*Jt), index1, index2);
 			}
 		}
 	}
};

int main(){

	vector< pair<int,int> > seqPair;
	int counter1{0};
	int counter2{0};

	Electric *probl = new Electric() ;
	probl->processElem();
	
	for(auto & row : probl->m_hashTable){
		sort(row.begin(),row.end());
		row.erase(unique(row.begin(),row.end()),row.end());
		for(auto & it : row){
			if(it!=make_pair(0,0)){
				counter1++;
			}
		}
	}

	// Print number of unique pairs
	cout << counter1 << endl;

	return 0; 
}