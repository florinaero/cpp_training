

// Write your code here
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

void discoverPath(int father[], int level[] , int stop, int start);
void bfs(int start, int stop, int cities, vector<int> *map);

int main(){

    vector<int> *ptrAdjList;
    
    int cities;
    int routes;
    int switchTime;
    int travelTime;
    int city0, city1;
    int start;
    int stop;
    
    cin >> cities;
    cin >> routes;
    cin >> switchTime;
    cin >> travelTime;
    
    ptrAdjList = new vector<int>[cities];
    
    // Read all available routes
    for(int i=0;i<routes;i++){
        cin >> city0;
        cin >> city1;
        ptrAdjList[city0-1].push_back(city1-1);
        // Complete links in vector
        ptrAdjList[city1-1].push_back(city0-1);
    }

    // Sort nodes
    for(int m=0;m<cities;m++){
        sort(ptrAdjList[m].begin(), ptrAdjList[m].end());
        auto last = unique(ptrAdjList[m].begin(), ptrAdjList[m].end());
        ptrAdjList[m].erase(last, ptrAdjList[m].end());
    }

    
    // Read Start city and stop city
    cin >> start >> stop;
    
    bfs(start-1, stop-1, cities, ptrAdjList);
    
    delete [] ptrAdjList;
    
    return 0;
    }

void bfs(int start, int stop, int cities,  vector<int> *map){
    
    queue<int> list;
    bool visited[cities];
    int father[cities];
    int elem;
    int level[cities];

    // Initialize array with false
    for(int i=0;i<cities;i++){
        visited[i] = false;
    }
    
    list.push(start);
    // parents[start] = start;
    visited[start] = true;
    level[start]=0;
    
    while(!list.empty()){
        
        elem = list.front();
        list.pop();
if(list.empty()){
    // cout<<"last elem"<<elem<<endl;
}
        for(int i=0;i<map[elem].size();i++){
// cout << "visi1: " << map[elem][i] << "+" << visited[map[elem][i]] << "_";
            if(visited[map[elem][i]]==false){
                list.push(map[elem][i]);
                visited[map[elem][i]] = true;
                // Level of node if one unit larger than his parent
                level[map[elem][i]] = level[elem] + 1;
                // Store parent of each node 
                father[map[elem][i]] = elem;
            }
        }
    }
    discoverPath(father, level, stop, start);
}
    
void discoverPath(int father[], int level[], int stop, int start){
    int index;
    // Keeps cities of path; level indicates how many cities are between 
    //  source and destination
    int path[level[stop]];
    index=stop;
// cout<<"stop: "<<level[stop]+1<<endl;
    // Print number of cities 
    cout << level[stop] + 1 << endl;

    for(int i=0;i<level[stop];i++){
        path[i] = father[index];
        // cout << "father["<<i<<"]: " << father[index] << endl;
        index = father[index]; 
    }
    
    for(int i=level[stop]-1;i>=0;i--){
        cout << path[i] + 1<< " ";
    }
    cout << stop + 1;
}