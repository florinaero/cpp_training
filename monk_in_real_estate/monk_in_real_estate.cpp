
// Write your code here
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
int main(){
    
    // maximum number of nodes
    vector<int> adjList[10000];
    vector<int> edges;
    int x, y; 
    int roads; 
    int cities;
    int total;
    int testCases;
    int position;
    
    // Read no of cases
    cin >> testCases;
    
    for(int p=0;p<testCases;p++){
        cities = 0;
        cin >> roads;
        
        // No of city is <= 1 so I start with i=1
        for(int i=1;i<=roads;i++){
            cin >> x >> y;
            edges.push_back(x);
            edges.push_back(y);
            // Store edges for each city 
            // adjList[x].push_back(y);
            // Store which vertexes from adjList has a road
            // edges.push_back(x);
        }
        
        sort(edges.begin(), edges.end());
        auto ptr = unique(edges.begin(), edges.end());
        edges.erase(ptr,edges.end());
        cities = edges.size();
                
#if 0
        for(int k=1;k<=roads;++k){
            position = edges[k-1];
            // Sort if it has more than 2 edges
            if (adjList[position].size()>1){
                // Sort each list 
                sort(adjList[position].begin(), adjList[position].end());
                // Select duplicate elements
                auto last = unique(adjList[position].begin(), adjList[position].end());
                // erase duplicates
                adjList[position].erase(last, adjList[position].end());
            }
            // Count number of cities
            cities += adjList[position].size(); 
            // Clear the list
            adjList[position].clear();
        
        }
#endif
        edges.clear();
        cout << cities << endl;
    }
    return 0;
}

/*        
    for(int p=0;p<testCases;p++){
        max = 0;
        counter = 0;
        dimenssion = 0;
        // no of roads and also the next number of lines from input
        cin >> dimenssion;
cout << "dim = "<<dimenssion << endl;
        
        // Array of pointers
        ptrCities = new int* [dimenssion];
        // Create an array twice as dimenssion to store roads between cities
        ptrArr = new int[2*dimenssion];
        
        // Find max from all lines for matrix creation
        while(cin >> elem){
            ptrArr[counter] = elem;
if (p == testCases-1){
    cout << "elem = " << ptrArr[counter] << endl;
}
            counter += 1;
            if(elem>max){
                max = elem; 
            }
            if(counter == 2*dimenssion)
                break;
        }
// cout << "counter = " << counter << endl;
        // ptrmax = max_element(ptrArr, 2*dimenssion);
// cout << "max = " <<max << endl;
        
        // Allocate an array for each address
        for(int i=0;i<max;i++){
            ptrCities[i] = new int[max];
        }

cout << "check_1" << endl;

        // Initialize matrix with 0 
        for(int i=0;i<max;i++){
            for(int j=0;j<max;j++){
                ptrCities[i][j] = 0; 
if (p == testCases-1){
    cout << "init = " << i << " " << j << endl;
}
            }
        }
        
cout << "check_2" << endl;
        
        for(int i=0;i<2*dimenssion;i+=2){
if (p == testCases-1){
    cout << "elem for matrix= " << i << endl;
}
            line = ptrArr[i];
            col = ptrArr[i+1];
cout << "line = " << line << endl << "col = " << col << endl;
            ptrCities[line-1][col-1] = 1;
            ptrCities[col-1][line-1] = 1;
        }
        
cout << "check_3" << endl;
        
        // Count cities
        for(int i=1;i<max;i++){
            for(int j=0;j<i;j++){
                if(ptrCities[i][j] == 1){
                    cities += 1;
                }
            }
        }
        
        // Destroy matrix
        for(int i=0;i<max;i++){
            delete [] ptrCities[i];
        }
        delete ptrCities;
        delete [] ptrArr;
        
        cout << "CITIES = " << cities << endl;    
        
    }
    
    return 0;
}*/
