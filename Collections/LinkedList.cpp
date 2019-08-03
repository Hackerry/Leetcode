#include <vector>
#include <iostream>

using namespace std;

/*
 * Copied from Leetcode
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

// Class for testing Linked List problems
class LinkedList{
  private:
    ListNode* root;
    vector<ListNode*> nodes;          // List structure may be changed, store
                                      // in vectors instead

  public:
    ListNode* construct(vector<int>& input) {
      if(root != nullptr) deleteAll();

      if(input.size() == 0) return root;

      root = new ListNode(input[0]);
      nodes.push_back(root);
      ListNode* currNode = root;
      for(int i = 1; i < input.size(); i++) {
        currNode->next = new ListNode(input[i]);
        currNode = currNode->next;
        nodes.push_back(currNode);
      }

      return root;
    }

    void printList(ListNode* head) {
      ListNode* currNode = head;
      cout << "[";
      while(currNode != nullptr) {
        if(currNode->next == nullptr) cout << currNode->val;
        else cout << currNode->val << ", ";
        currNode = currNode->next;
      }
      cout << "]" << endl;
    }

    void otherOperation() {}

    void deleteAll() {
      for(ListNode* l: nodes) delete(l);
    }

    ~LinkedList() {
      deleteAll();
    }
};
