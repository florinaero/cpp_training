/*Note : For this question use PAIRS for taking input, and then do it, don't use map.

There are 'N' 2-D co-ordinate points given. Now , you have to print the co-ordinate point, 
followed by their frequencies, See sample I/O,

Print the coordinate points in the Lexicographical order.

Input :

First line contains an integer 'N' , i.e the no. of 2-D coordinate points given.
Next N line contains, two space separated integers x and y, defining x-coordinate and y- coordinate respectively .
Output:

Three space separated integers, first one defines the x-coordinate, second integer define
y-coordinate and third integer defines the frequency of (x,y). Constraints:

1<= N <=100000
-10^9<= x,y <=10^9
*/
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <range.hpp>
#include <cmath>
#include <algorithm>
#include <chrono>

// N=100 gives a better time
#define N 100

using namespace std;

class HashCoord{

private: 
	const int init;
	const pair<int,int> INIT;
	int tempCounter;
	static inline int logTotal = log10(N);
public:
	int noCoord{0};
	vector<pair<pair<int,int>,int>> coordFreq;
	vector< pair<int,int> > hashTable;


	// Ctor
	HashCoord():
	init(pow(10.0,9) + 1),
	INIT(make_pair(init,init)), 
	tempCounter(0)
	{};

	// Read file
	void readFile(string path){
		fstream file(path);
		string line;
		int coord{0};
		int counter{0};
		int position{0};
		vector<int> elements(2,0);
		pair<int,int> newPair;
		int temp{0};
		if(file){
			// Read number of pairs
			file >> noCoord;
			noCoord = 199999;
			hashTable.resize(noCoord, INIT);
			coordFreq.resize(noCoord);

			while(file >> coord){
				elements.at(counter) = coord;
				counter++;
				if(counter==elements.size()){
					newPair = make_pair(elements.at(0), elements.at(1));
					position = hashing1(newPair.first, newPair.second);
					insert(newPair, position);
					counter = 0;
				}
				temp++;
				if(temp>199990){
					// cout<<temp<<endl;		
				}	
			}	
		}
		file.close();
	}

	// Mid square hashing 	
	int hashing1(int elem1, int elem2)const{
		int hash1{0};
		long temp{0};
		int digits{0};
		int diff{0};
		int halfDiff{0};
		const int modDigits = pow(10,logTotal);

		// hash1 = (1991*elem1 + elem2) % 2069 % noCoord; 
		// Add 10000 to have at least "logTotal" 
		temp = pow(double(abs(elem1)+abs(elem2) + N),2);
		// Find number of digits
		digits = floor(log10(temp))+1;
		if(digits==logTotal){
			// In case of same number of digits assign value without extraction
			hash1 = temp;
		}
		else{
			// Difference of digits 
			diff = digits - logTotal;
			// Find how many digits should be removed from each side of the number
			halfDiff = diff/2;		
			// Remove digits from LSB 
			hash1 = temp / (pow(10,halfDiff));
			// Remove digits from MSB by keeping only mid digits
			hash1 = hash1 % modDigits;
		}


		return hash1 % noCoord;
	}

	int hashing2(int elem1, int elem2)const{
		return (31*abs(elem1) + abs(elem2)) % noCoord; 
	}

	void insert(pair<int,int>& insertedPair, int position){
		static int level = 1000;
		int counter{0};

		// Check for an empty position
		while(hashTable.at(position)!=INIT){
			// Linear probing
			// position = (position+1) % noCoord;
			// Double probing only when pairs are different, otherwise keep the same position
			if(hashTable.at(position)!=insertedPair){
				position = (position + counter+hashing2(insertedPair.first, insertedPair.second)) % noCoord;
				tempCounter++;
				counter++;
			}
			else{
				// Interrupt while loop if pairs are equal
				cout << "Equal pair: " << "<"<<insertedPair.first<<","<<insertedPair.second<<">" << endl; 
		
				break;
			}
			if(tempCounter > 10000){
				// cout << "tempCounter = " << tempCounter << endl;
			}
		}
			
		if(tempCounter>level){
			
			level = level + 1000;
		}
		// Store new pair in hashTable
		hashTable.at(position) = insertedPair;
		// Increase counter of pairs
		coordFreq.at(position).second++;
		// Store pair
		coordFreq.at(position).first = insertedPair;
	}

	void showResults(){

		sort(coordFreq.begin(), coordFreq.end());	
		for(uint i: util::lang::indices(coordFreq)){
			// Do not print empty slots
			// if(hashTable.at(i)!=INIT){
			// 	cout << hashTable.at(i).first << " " << hashTable.at(i).second << " " << coordFreq.at(i) << endl; 
			// }
			if(coordFreq.at(i).first!=make_pair(0,0)){
				cout << coordFreq.at(i).first.first << " " << coordFreq.at(i).first.second << " ";
				cout << coordFreq.at(i).second << endl; 
			}
		}
	}
};

int main(){

	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	HashCoord *object = new HashCoord();
	object->readFile("input/input1.txt");
	cout << "Show results" << endl;
	// object->showResults();
	delete object;

	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	
	cout << "Elapsed time = " << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "ms" << endl;
	
	return 0;
}