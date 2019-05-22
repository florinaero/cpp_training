 /*
// Sample code to perform I/O:

cin >> name;                            // Reading input from STDIN
cout << "Hi, " << name << ".\n";        // Writing output to STDOUT

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
*/

// Write your code here
#define DEBUG 0
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;
typedef vector< pair<int,int> > vPair;

// Remove element from vector that keeps largest subarray, auxiliary function
void removeMaxElement(vPair* vSortedIndex, vPair& index);
// Sort vector and keep index
void sortVectorKeepIndex(vector<int>& input, vPair& index, int max);
// Sort vector with index 
void sortVectorIndex(vector<int>* input, vPair* index, int max);
// Sort vector
void sortVector(vector<int>* input, int);
// Read input from file and return element
void readFile(string path, vector<int>&, int&, int&);
// Read input from keyboard and return element
void readKeyboard(vector<int>&, int&, int&);
void allocation(long, vector<int>&, vector<int> *);
long msb(long);
bool consecutive(long elem1, long elem2);
// Add element for counting 
void addElementCounter(vector<int>& counter);
// Compute minimum sum that can be achieved by K flips
void removeFlippArrays(vPair*, int, int);
// Compute the minimum sum by summing up remaining subbarrays
long minSum(vPair*, int);

int main(int argc, char** argv){

	long minimumSum = 0;
    long max=0;
    vector<int> input;
    int noOfElements = 0 ;
    int noOfFlips = 0;


    //const string PATH = argv[1];
    
#if DEBUG
    cout << PATH << endl;
#endif

    // Maximum MSB of an element
    max=msb(1e6);
    vector<int> vCounter[max+1];
	vPair vSortedIndex [max+1];

    // Read file and store content in vector 
    // readFile(PATH, input, noOfElements, noOfFlips);
	readKeyboard(input, noOfElements, noOfFlips);


    // Read all elements
    // input: position of MSB
    allocation(max, input, vCounter);

    // Sort vector with index
    sortVectorIndex(vCounter, vSortedIndex, max);


#if DEBUG
    cout << "\nSize of subarrays and their position in vector in a sorted way. \n";
    for(int i=0;i<=max;i++){
	 	cout <<"vCounter sorted[" << i <<"]: ";
		for(vPair::iterator it=(vSortedIndex[i]).begin();it!=(vSortedIndex[i]).end();++it){
			cout << (*it).first << "(" << (*it).second << ")" << ",";
			
		}
		cout << endl;
	}
	cout << "Number of Flips: " << noOfFlips << endl;
#endif

	removeFlippArrays(vSortedIndex, noOfFlips, max);


#if DEBUG
    cout << "\nRemained elements. \n";
    for(int i=0;i<=max;i++){
	 	cout <<"vCounter sorted[" << i <<"]: ";
		for(vPair::iterator it=(vSortedIndex[i]).begin();it!=(vSortedIndex[i]).end();++it){
			cout << (*it).first << "(" << (*it).second << ")" << ",";
			
		}
		cout << endl;
	}
#endif

	minimumSum = minSum(vSortedIndex, max);

	cout << minimumSum << endl;
	// cout << "END\n"; 

	return 0;
}

long minSum(vPair* vLast, int max){
	long sumBits = 0;
	long sum = 0;

	// Elements of pair: first: number of SET bits , second:index of subarray in general vector
	for(int i=0; i<=max; i++){
		for(vPair::iterator it=(vLast[i]).begin();it!=vLast[i].end();++it){
			if((*it).first>0){
				sumBits = sumBits + (*it).first;
			}
		}
		sum = sum + ((1<<i) * sumBits);
		// Reset sum of bits for each position in a number with "max" number of bits
		sumBits = 0;
	}

	return sum;
}

// Compute minimum sum that can be achieved by K flips
void removeFlippArrays(vPair* vSortedIndex, int noOfFlips, int max){
	vector<int> vMax;
	vPair index;
	int pushedElement = 0;
	int sumSize = 0;

	// Clear vector before a new search
	vMax.clear();

	// Get through each vector that stores number of elements of subarray for each bit position 
	for(int i=0;i<=max;i++){
		// cout << boolalpha << i << "___" << vSortedIndex[i].empty() << endl;
		if(vSortedIndex[i].empty()){
			pushedElement = 0;
		}
		else{
			// Last element from each vector with number of elems of subarray
			pushedElement = vSortedIndex[i].back().first;
			// Avoid processing "-1" which is used as delimiter
			if(pushedElement == -1){
				pushedElement = 0;
			}
		}
		sumSize = sumSize + pushedElement;
		vMax.push_back(pushedElement);
	}
	// Sort vector and return a vector of pairs<counter, vector index>
	index.clear();
	sortVectorKeepIndex(vMax, index, max);


#if DEBUG
	static int n = 0;		
	cout <<"\n vMax removedFlippArrays[" << n++ <<"]: ";
	for(vPair::iterator it=(index).begin();it!=(index).end();++it){
	cout << (*it).first << "(" << (*it).second << ")" << ",";

	}
	cout << endl;
	cout << "Sum of elements  =  " << sumSize << endl;
#endif


	removeMaxElement(vSortedIndex, index);
	noOfFlips--;
	// Check is nothing anymore to sort 			
	if(sumSize !=0 && noOfFlips !=0){
		// TODO: removeFlippArrays can get index as input to be sorted to not get through all elements again
		// Recursivity 
		removeFlippArrays(vSortedIndex, noOfFlips, max);
	}
}


void removeMaxElement(vPair* vSortedIndex, vPair& index){
	int position = 0;

	if(!index.empty()){
		position = index.back().second;
		index.pop_back();
	}

	// Check for elements->Means bits for corresponding position are NOT anymore SET
	if(!vSortedIndex[position].empty()){
		// Remove from sorted vector the pair that has the biggest counter->largest subarray 
		vSortedIndex[position].pop_back();
		// Push next pair that has number of elements of subarray
		index.push_back(vSortedIndex[position].back());
	}
	else{
		if(!index.empty()){
			removeMaxElement(vSortedIndex, index);
		}
	}
// #if DEBUG
// 	cout <<"vMax sorted[" << 0 <<"]: ";
// 	for(vPair::iterator it=(index).begin();it!=(index).end();++it){
// 	cout << (*it).first << "(" << (*it).second << ")" << ",";

// 	}
// 	cout << endl;
// #endif
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
    int n = 0;

    // Read elements until the last one
    for(vector<int>::iterator It = input.begin();It!=input.end();++It){
    	elem = *It;
		// Store all elements
		allElem.push_back(elem);
		actualPos = allElem.size()-1;

		// Cycle each bit of an element 
	    for(int i=0;i<=max;i++){
	    	// Check if bit is set, result is a number > 0
	    	if(elem & (1<<i)){
	    		n++;
		    	// Add elements if necessary
		    	addElementCounter(vCounter[i]);
#if DEBUG
	cout << "BIT: " << i <<" ELEM: " << elem << " Vcounter value: "<<
	 vCounter[i].back() << " split size: " << split[i].size() <<
	 " actual position: " << actualPos << endl;
#endif
	    		// Store position from general vector 
	    		split[i].push_back(actualPos);
	    		// Check size before accesing second last elem
	    		if(split[i].size()>1){
		    		// Last but one element stored in SET bit vector
		    		lastPos = (split[i].end()[-2]);
	   
		    		// Check if last 2 stored numbers from a vector with set bits are consecutive
		    		// In this way you know the subarrays with same set bits 
		    		if(consecutive(actualPos, lastPos))
		    		{
		    			// Count how many numbers are consecutive to find the largest array
		    			vCounter[i].back()++;
		    		}
	    			else	
		    		{		    			
		    			// Store a delimeter if elements are not consecutive
		    			// Remove last elem and push delimeter(-1) and store back last elem		    	
		    			temp = split[i].end()[-1];
		    			split[i].pop_back();
		    			split[i].push_back(-1);
		    			split[i].push_back(temp);
		    			// Mark end of subarray with -1 in 
		    			vCounter[i].push_back(-1);
		    			// If the last 2 elements are not consecutive it will not be added "1" 
		    			// 	to mention last element. 
		    			if(actualPos == input.size()-1){
		    				vCounter[i].push_back(1);
		    			}
		    		}
				}	    	
	    	}
	    }
	}


#if DEBUG
	cout << "Number of SET bits: " << n << endl;
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
void sortVectorKeepIndex(vector<int>& input, vPair& index, int max){

	int j = 0;

	for(vector<int>::iterator it = input.begin();it!=input.end();++it){
		// First: counter, Second:index
		// First element if powered to bit position to avoid equal counters 
		//	which corresponds to different position
		index.push_back(make_pair((j<<*it), j));
		j++;
	}
	// Reset index for each vector from array
	// Sort vector of pairs after first element
	sort(index.begin(),index.end());
	
	for(vPair::iterator it = index.begin();it!=index.end();++it){
		(*it).first = ((*it).first) >> ((*it).second);
	}
}

// Sort vector and keep index
void sortVectorIndex(vector<int>* input, vPair* index, int max){

	int j = 0;

	for(int i=0;i<=max;i++){
		for(vector<int>::iterator it = input[i].begin();it!=input[i].end();++it){
			// First: counter, Second:index
			index[i].push_back(make_pair(*it, j));
			j++;
		}
		// Reset index for each vector from array
		j=0;
		sort(index[i].begin(),index[i].end());
	}
}

// Read input and return element
void readFile(string path, vector<int>& elements, int& total, int& flips){
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

	total = elements.front();
	elements.erase(elements.begin());
	flips = elements.front();
	elements.erase(elements.begin());

	file.close();
}

// Read input from keyboard and return element
void readKeyboard(vector<int>& elements, int& total, int& flips){
	int elem = 0;

	while(cin >> elem){
		elements.push_back(elem);
	}

	total = elements.front();
	elements.erase(elements.begin());
	flips = elements.front();
	elements.erase(elements.begin());
}

// Add element for counting 
void addElementCounter(vector<int>& counter){
	if(counter.empty() || counter.back()==-1){
		// Introduce an 1 will mark in vector the presence of non-consecutive number
#if DEBUG	
	if(!counter.empty()){
		cout << "last element: " << counter.back() << endl; 
	}
#endif	
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