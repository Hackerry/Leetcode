#include <iostream>
#include <limits>
#include <algorithm>
#include <queue>
#include "../Collections/LinkedList.cpp"
#include "../Collections/Parser.cpp"

using namespace std;

class Solution {
  public:
    struct Comp {
      bool operator()(const ListNode* l1, const ListNode* l2) {
        return l1->val < l2->val;
      }
    };

    // Sample 16 ms
    // https://leetcode.com/problems/merge-k-sorted-lists/discuss/10531/Sharing-my-straightforward-C%2B%2B-solution-without-data-structure-other-than-vector
    // Can use recursion: divide and conquer(K lists->k/2 lists->k/4 lists...)
    // k/2*(2N)+k/4*(4N)+k/8*(8N)... = O(KNlogK)

    // From sample 24ms solution
    // O(NlogK) - 20ms --> K<N
    ListNode* mergeKLists(vector<ListNode*>& lists) {
      // Lambda expression C++11
      auto comp = [](const ListNode* l1, const ListNode* l2) {
        return l1->val > l2->val;
      };

      ListNode* root = new ListNode(0);
      ListNode* currNode = root;
      priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> queue(comp);
      for(int i = 0; i < lists.size(); i++) {
        if(lists[i] != nullptr) queue.push(lists[i]);
      }

      while(!queue.empty()) {
        currNode->next = queue.top();
        currNode = currNode->next;
        queue.pop();
        if(currNode->next != nullptr) queue.push(currNode->next);
      }

      currNode->next = nullptr;
      currNode = root->next;
      delete(root);
      return currNode;
    }

    // Great example of posting unnecessary constraints when solving problems!!
    // N + NlogN = O(NlogN)   - 28ms
    ListNode* mergeKListsNlogN(vector<ListNode*>& lists) {
      ListNode* root = nullptr;
      ListNode* currNode;
      vector<ListNode*> nodes;

      // Add all nodes to list
      for(int i = 0; i < lists.size(); i++) {
        currNode = lists[i];
        while(currNode != nullptr) {
          nodes.push_back(currNode);
          currNode = currNode->next;
        }
      }

      // Sort the list
      sort(nodes.begin(), nodes.end(), Comp());

      // Relink
      if(!nodes.empty()) {
        root = nodes[0];
        currNode = root;

        for(int i = 1; i < nodes.size(); i++) {
          currNode->next = nodes[i];
          currNode = currNode->next;
        }

        // Careful here
        currNode->next = nullptr;
      }

      return root;
    }

    // Small improvement???
    // O(KN)
    // NO! 436ms
    ListNode* mergeKListsKN2(vector<ListNode*>& lists) {
      int smallest, next;
      int smallestIdx;
      ListNode* root = nullptr;
      ListNode* currNode;
      char remain = false;

      do {
        remain = false;
        smallest = numeric_limits<int>::max();
        next = smallest;

        // Update the smallest and next
        for(int i = 0; i < lists.size(); i++) {
          if(lists[i] != nullptr) {
            if(lists[i]->val < smallest) {
              next = smallest;
              smallest = lists[i]->val;
              smallestIdx = i;
              remain = true;
            } else if(lists[i]->val < next) {
              next = lists[i]->val;
            }
          }
        }

        // Append new list to end
        if(remain) {
          if(root == nullptr) {
            root = lists[smallestIdx];
            currNode = root;
          } else {
            currNode->next = lists[smallestIdx];
            currNode = currNode->next;
          }
          lists[smallestIdx] = lists[smallestIdx]->next;

          // Keep going until have to change list
          while(lists[smallestIdx] != nullptr && lists[smallestIdx]->val < next) {
            currNode = lists[smallestIdx];
            lists[smallestIdx] = lists[smallestIdx]->next;
          }
        }
      } while(remain);

      return root;
    }

    // Slow O(kN) algorithm
    // Fun fact: got runtime 404ms lol!
    ListNode* mergeKListsKN(vector<ListNode*>& lists) {
      int smallest;
      char remain;
      ListNode* root = nullptr;
      ListNode* currNode;
      int index;

      do {
        remain = false;
        smallest = numeric_limits<int>::max();
        for(int i = 0; i < lists.size(); i++) {
          if(lists[i] != nullptr) {
            if(lists[i]->val < smallest) {
              smallest = lists[i]->val;
              index = i;
            }
            remain = true;
          }
        }

        if(remain) {
          if(root == nullptr) {
            root = lists[index];
            currNode = root;
          } else {
            currNode->next = lists[index];
            currNode = currNode->next;
          }
          lists[index] = lists[index]->next;
        }
      } while(remain);

      return root;
    }
};

int main() {
  Solution s;
  LinkedListUtil l;
  Parser p;

  vector<vector<int>> input = p.parse2DList("[[1,2],[4,6],[3,7]]");//"[[-10,-6,-4,-4,0,2,2,2,2],[-5,1,3,4,4,4],[-9],[-9],[-10,-8,-5,-4,-3,-3,-2,4],[-10,-8,-7,-4,-4,0,1,2],[-8,-1,4],[-6,-5,-2,-2,-1,1,3,4]]");
  vector<ListNode*> lists;

  for(vector<int>& v: input) {
    ListNode* newNode = l.construct(v);
    lists.push_back(newNode);
    l.printList(newNode);
  }

  ListNode* newNode = s.mergeKLists(lists);

  l.printList(newNode);
}
