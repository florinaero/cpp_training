/*
// Sample code to perform I/O:

cin >> name;                            // Reading input from STDIN
cout << "Hi, " << name << ".\n";        // Writing output to STDOUT

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
*/

// Write your code here
#include<vector>
#include<string>
#include<iostream>
using namespace std;

class Hashing{

    // size_t hashTableSize = m_hashTable.size();
    int m_hashTableSize;
    vector<string> m_hashTable;
    vector<int> m_rollNo;
    vector<string> m_names;
    vector<int> m_rollGuess;
    
    void readingContent(){
        int j(0);
        int iRoll(0);
        string sName("");
        int iNoGuess(0);
        

        cin >> m_hashTableSize;

        for(int i=0;i<m_hashTableSize;i++){
            cin >> iRoll;
            m_rollNo.push_back(iRoll);
            cin >> sName;
            m_names.push_back(sName);
        }

        cin >> iNoGuess;
        
        while(cin >> j){
            m_rollGuess.push_back(j);
        }
    }

public:

   Hashing() : 
    m_hashTableSize(0)
    {
        readingContent();

        m_hashTable.resize(m_hashTableSize+1);
        
        map();

        for(int i=0;i<m_rollGuess.size();i++){
            cout << guess(m_rollGuess.at(i)) << endl;
        }
        

    }

    void map(){
        for(int i=0;i<m_rollNo.size();i++){
            m_hashTable[m_rollNo.at(i)] = m_names.at(i);
        }
    }

    string guess(int index){
        return m_hashTable.at(index);

    }

};

int main(){
    
    Hashing k = Hashing();

    return 0;
}
