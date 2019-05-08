

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

 // Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
 };
 
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
            
        
        
            // Store address of first node
            ListNode *ptrFirst = head;
        
            if(!(ptrFirst->next->next)){
                // Reallocate head to second node
			head = ptrFirst->next;
        
            // New head is linked to old address
			head->next = ptrFirst;
                cout << ptrFirst->val << "<-";
            // New second node points to third node 
            ptrFirst->next = nullptr;
                
			    return head;
			}
            // Store adress of third node 
			ListNode *ptrSecond = ptrFirst->next->next;
        
            // Reallocate head to second node
			head = ptrFirst->next;
        
            // New head is linked to old address
			head->next = ptrFirst;

            // New second node points to third node 
            ptrFirst->next = ptrSecond;

			swapPairs(ptrSecond);			
			return head;
    }
};

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

ListNode* stringToListNode(string input) {
    // Generate list from the input
    vector<int> list = stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

string listNodeToString(ListNode* node) {
    if (node == nullptr) {
        return "[]";
    }

    string result;

    while (node) {
        result += to_string(node->val) + ", ";
        node = node->next;
    }
    return "[" + result.substr(0, result.length() - 2) + "]";
}

int main() {
    string line;
    while (getline(cin, line)) {

        ListNode* head = stringToListNode(line);
        
        ListNode* ret = Solution().swapPairs(head);

        string out = listNodeToString(ret);
        cout << out << endl;
    }
    return 0;
}