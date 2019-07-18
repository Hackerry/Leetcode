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

  public:
    ListNode* construct(vector<int>& input) {
      if(root != nullptr) deleteAll();

      if(input.size() == 0) return root;

      root = new ListNode(input[0]);
      ListNode* currNode = root;
      for(int i = 1; i < input.size(); i++) {
        currNode->next = new ListNode(input[i]);
        currNode = currNode->next;
      }

      return root;
    }

    void printList() {
      ListNode* currNode = root;
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
      if(root == nullptr) return;

      ListNode* nextNode;
      ListNode* currNode = root;
      while(currNode != nullptr) {
        nextNode = currNode->next;
        delete(currNode);
        currNode = nextNode;
      }

      root = nullptr;
    }

    ~LinkedList() {
      deleteAll();
    }
};
