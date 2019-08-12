/*
There is a class consisting of 'N' students . There can be many students with the same name.

Now, you have to print the names of the students followed by there frequency as shown in the sample explanation given below.

Output the names in the lexicographical order.

Input :

First line contains an integer 'N', i.e the no. of students in the class.
Next 'N' lines contains the names of the students.
Output:

Each line consists of the name of student space and separated its frequency.
Constraints:

1<=N<=1000
string length<=100
string consists of lowercase letters
Note : For practicing use Map technique only .
*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <algorithm>

using namespace std;

class Students{

public:
	string m_fileName;	
	vector<string> m_names;
	vector<int> m_freq;
	vector< vector<string> > m_hashTable;
	int m_totalStudents;


	void initialize(){
		m_fileName = "input/input2.txt";
	}

	void readingFile(){

		string name;
		int freq;

		ifstream file (m_fileName);
		if(file){
			file >> m_totalStudents;
			while(file >> name){
				m_names.push_back(name);
			}
		}
		else{
			cout << "File couldn't open!" << endl;
		}
		file.close();
	}

	void readingInput(){
		string name;
		int counter{0};
		cin >> m_totalStudents;
		while((cin >> name) && (counter<m_totalStudents-1))
		{
			m_names.push_back(name);
			counter++;
		}
	}

	int hashFunc(string name){
		int index(0);
		int sum(0);

		for(int i=0;i<name.size();i++){
			sum = (sum + name.at(i));
		}

		index = sum%2069%m_totalStudents;
		// cout << index << endl;
		return index;
	}

	void insert (string name) {
		int index(0);

		index = hashFunc(name);

		while(m_hashTable.at(index).size() != 0){
			index = (index+1)%m_totalStudents;
		}
		m_hashTable.at(index).push_back(name);


	}

	// struct{
	// 	bool operator() (string s1, string s2) const {
	// 		return s1<s2;
	// 	}
	// } compare;

public:
	// ctor
	Students():
	m_totalStudents(0)
	{
		initialize();
		readingFile();
		// readingInput();
		m_hashTable.resize(m_totalStudents);

		// cout << "no of students = " << m_totalStudents << endl;
		for(int i=0;i<m_names.size();i++){
			// cout << m_names.at(i) << endl;
			insert(m_names.at(i));
		}

		// cout << m_hashTable.size() << endl;
	}
};

bool compare (string s1, string s2)	 {
			return s1<s2;
}

int main(){

	Students kal = Students();

	vector<int> freq;
	vector<string> finalNames;
	int counter(1);
	int i(0);
	int result(0);

	sort(kal.m_names.begin(),kal.m_names.end(),compare);

	// Stop the last name
	for(int j=0;j<kal.m_names.size();++j){
		// In case of end of vector step over the comparison 
		if(j!=kal.m_names.size()-1){
			result = kal.m_names.at(j).compare(kal.m_names.at(j+1));
		}
		else{
			result = 1;
		}
		// Check if are the same names
		if(!result){
			counter++;
			// cout << kal.m_names.at(j) << endl;
		}
		else{
			// Store number of names from list
			finalNames.push_back(kal.m_names.at(j));
			freq.push_back(counter);
			counter = 1;
		}
	}

	
	for(int i=0;i<finalNames.size();i++){
					
		cout << finalNames.at(i) << " " << freq.at(i)  << endl;
		// cout << endl << m_hashTable.at(i).size() << endl;
		// for(int j=0;j<m_hashTable.at(i).size();j++){
		// 	cout << m_hashTable.at(i).at(j) << " ";
		// }
		// cout << endl;

	}

	return 0;
}
