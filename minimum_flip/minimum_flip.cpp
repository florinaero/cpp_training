 /*
// Sample code to perform I/O:

cin >> name;                            // Reading input from STDIN
cout << "Hi, " << name << ".\n";        // Writing output to STDOUT

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
*/

// Write your code here
#define DEBUG 1
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// Sort vector with index 
void sortVectorIndex(vector<int>* input, vector< pair<int,int> >* index, int max);
// Sort vector
void sortVector(vector<int>* input, int);
// Read input and return element
void readFile(string path, vector<int>&);
void allocation(long, vector<int>&, vector<int> *);
long msb(long);
bool consecutive(long elem1, long elem2);
// Add element for counting 
void addElementCounter(vector<int>& counter);

int main(int argc, char** argv){

    long max=0;
    vector<int> input;
    
    const string PATH = argv[1];
    cout << PATH << endl;

    // Maximum MSB of an element
    max=msb(1e6);
    vector<int> vCounter[max+1];
    vector<int> *ptrVCounter = vCounter; 
    
	vector< pair<int,int> > vSortedIndex [max+1];
	vector< pair<int,int> > *ptrVSortedIndex = vSortedIndex;
	typedef vector< pair<int,int> > vPair;

    cout << "position of MSB: " << max << endl;
    // cout << "Number of elements: ";
    // cin >> n;
    // cout << "Number of flips: ";
    // cin >> k;

    // Read file and store content in vector 
    readFile(PATH, input);

    // Read all elements
    // input: position of MSB
    allocation(max, input, ptrVCounter);
    // Sort vector
    // sortVector(ptrVCounter, max);
    // Sort vector with index
    sortVectorIndex(ptrVCounter, ptrVSortedIndex, max);

#if DEBUG
    int j;
    for(int i=0;i<=max;i++){
		j = 0;
	 	cout <<"vCounter sorted[" << i <<"]: ";
		for(vPair::iterator it=(ptrVSortedIndex[i]).begin();it!=(ptrVSortedIndex[i]).end();++it){
			cout << (*it).first << "(" << (*it).second << ")" << ",";
			
		}
		cout << endl;
	}
#endif

}

// input: maximum decimal value of an element 
void allocation(long max, vector<int>& input, vector<int>* vCounter){
    vector<int> split [max+1];
    vector<int> allElem;
    // vector<int> vCounter [max+1];

    long elem = 0;
    long actualPos = 0;
    long lastPos = 0;
    int temp = 0;

    // Read elements untill the last one
    for(vector<int>::iterator It = input.begin();It!=input.end();++It){
    	elem = *It;
		// Store all elements
		allElem.push_back(elem);
		actualPos = allElem.size()-1;

		// Cycle each bit of an element 
	    for(int i=0;i<=max;i++){
	    	// Check if bit is set
	    	if(elem & (1<<i)){
		    	// Add elements if necessary
		    	addElementCounter(vCounter[i]);
	    		// Store position from general vector 
	    		split[i].push_back(actualPos);
	    		// Check size before accesing second last elem
	    		if(split[i].size()>1){
		    		// Last stored position from the general vector into the set bit vector
		    		lastPos = (split[i].end()[-2]);
	   
		    		// Check if last 2 stored numbers from a vector with set bits are consecutive
		    		// In this way you know the subarrays with same set bits 
		    		if(consecutive(actualPos, lastPos))
		    		{
		    			// Count how many numbers are consecutive to find the largest array
		    			vCounter[i].end()[-1]++;
		    		}
	    			else	
		    		{		    			
		    			// Store a delimeter if elements are not consecutive
		    			// Remove last elem and push delimeter and store back last elem		    	
		    			temp = split[i].end()[-1];
		    			split[i].pop_back();
		    			split[i].push_back(-1);
		    			split[i].push_back(temp);
		    			// Mark end of subarray with -1 in 
		    			vCounter[i].push_back(-1);
		    		}
				}	    	
	    	}
	    }
	}


#if DEBUG
	
	cout << "all elements: ";
	for(vector<int>::iterator it=allElem.begin();it!=allElem.end();++it){
			cout << (*it) << ", ";
	}
	cout << endl;
	for(int i=0;i<=max;i++){
		
		 cout <<"set bit[" << i <<"]:  ";
		for(vector<int>::iterator it=split[i].begin();it!=split[i].end();++it){
			cout << (*it) << ", ";
		}
		cout << endl;
	}

	for(int i=0;i<=max;i++){
	 	cout <<"vCounter[" << i <<"]: ";
		for(vector<int>::iterator it=vCounter[i].begin();it!=vCounter[i].end();++it){
			
			cout << (*it) << ", ";

		}
		cout << endl;
	}

#endif

}

// Sort vector
void sortVector(vector<int>* temp, int max){
	// vector<int> temp(&input);

	for(int i=0;i<=max;i++){
		sort(temp[i].begin(), temp[i].end());
	}
}

// Sort vector and keep index
void sortVectorIndex(vector<int>* input, vector< pair<int,int> >* index, int max){

	int j = 0;

	cout << "Size of vectorIndex is " << index->size() << endl;
	for(int i=0;i<=max;i++){
		for(vector<int>::iterator it = input[i].begin();it!=input[i].end();++it){
			index[i].push_back(make_pair(*it, j));
			j++;
		}
		// Reset index for each vector from array
		j=0;
		sort(index[i].begin(),index[i].end());
	}
}

// Read input and return element
void readFile(string path, vector<int>& elements){
	int elem = 0;

	ifstream file;

	file.open(path);
	if(!file){
		cout << "Unable to open file." << endl;
		exit(1);
	}
	else{
		cout << "Opened file." << endl;
	}

	while(file >> elem){
		elements.push_back(elem);
	}

	file.close();
}
// Add element for counting 
void addElementCounter(vector<int>& counter){
	if(counter.size()<1 || counter.end()[-1]==-1){
		// Introduce an 1 will mark in vector the presence of non-consecutive number
		counter.push_back(1);
	}
}

// Find if 2 elements are consecutive 
bool consecutive(long elem1, long elem2){
	if(abs(elem2 - elem1) == 1)
		return true;
	else 
		return false;
}

long msb(long number){
	long msb=0;

	if(number==0)
		return 0;

	while(number!=0){
		number = number >> 1;
			msb++;
	}

	return msb-1;
}