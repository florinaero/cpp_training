/*************************************************************************************************/
/**
@brief 		4.7 Build Order
@details	
@author 	florin
@date 		2021-01-29 
/*************************************************************************************************/
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <utility>
#include <deque>

class Node {
public:
    // ctor
    Node(std::string name):
    name_(name),
    dependency_(0)
    {}
    std::string name_;
    std::vector<std::shared_ptr<Node>> adj_list;
    int dependency_; // Number of nodes that points to this element or number of dependencies
    // Define operator for set comparison
    bool operator< (const Node& node) const{
        return node.name_ < name_;
    }
};

class Graph {
public: 
    std::vector<std::shared_ptr<Node>> nodes_;
};

int main(){
    std::cout << "Problem 4.7 Build order.\n";
    std::vector<std::pair<std::string, std::string>> input {
        {"f","b"}, {"f","c"}, {"f","a"}, {"c","a"},
        {"b","a"}, {"b","e"}, {"a","e"}, {"d","g"}, {"e","f"}
    };
    Graph graph;
    
    for(auto& elem : input){
        std::shared_ptr<Node> ptr_node_first = std::make_shared<Node>(elem.first);
        std::shared_ptr<Node> ptr_node_second;
        std::string name_first = elem.first; 
        
		// Check if insertion took place which means node is not existing in graph
        auto it_first = std::find_if(graph.nodes_.begin(), graph.nodes_.end(),
                        [name_first](std::shared_ptr<Node> ptr) {
                            return ptr->name_==name_first;});
							
        if(it_first == graph.nodes_.end()) {
            graph.nodes_.push_back(ptr_node_first);
        }
        else{// If insertion didn't take place it means node is already existing and it is necessary just to update the adj_list
            ptr_node_first = *it_first; // Copy node's pointer        
        }

        ptr_node_second = std::make_shared<Node>(elem.second); // Create pointer for second elem for checking existance in graph
        std::string name_sec = elem.second;
        auto it_second = std::find_if(graph.nodes_.begin(), graph.nodes_.end(),
                        [name_sec](std::shared_ptr<Node> ptr) {
                            return ptr->name_==name_sec;});
							
        if(it_second != graph.nodes_.end()){ // Second node already in graph
            (*it_second)->dependency_++;
            ptr_node_first->adj_list.push_back(*it_second); // Add existing node from graph, not the local one
        }
        else{
            graph.nodes_.push_back(ptr_node_second); // Insert new element
            ptr_node_second->dependency_++;  // Increase dependency for each addition to an adj_list
            ptr_node_first->adj_list.push_back(ptr_node_second);
        }
    }

    using ptrNode = std::shared_ptr<Node>;

    std::vector<ptrNode> build_order;
    std::vector<ptrNode> que = graph.nodes_;
    int idx = 0;
    while(que.empty()==false){
        auto elem = que.at(idx);
        if(elem->dependency_ == 0){
            que.erase(que.begin()+idx);
            build_order.push_back(elem);
            for(auto node : elem->adj_list){
                node->dependency_--;
            }
            idx=0;
        }
        else{
            idx++;
            if(idx==que.size()){
                std::cout << "All nodes have dependencies. Stop" << std::endl;
                break;
            }  
        }
    }

    std::cout << "build order: ";
    for(auto i : build_order){
        std::cout << i->name_ << " " ;
    }

    return 1;
}