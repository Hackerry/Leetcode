#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  public:
    // O(n)
    // Use dummy node to simplify edge case
    ListNode* removeNthFromEnd(ListNode* head, int n) {
      if(head == nullptr) return head;

      int index = 1;
      ListNode* currNode = head;
      ListNode* removeNode = nullptr;
      // Space the two pointers by n
      while(index++ <= n) currNode = currNode->next;

      // Edge case, remove head
      if(currNode == nullptr) return head->next;

      // Put in the remove pointer
      removeNode = head;

      // When the first pointer reaches the last element, remove pointer is at 
      // the parent of the to be removed node
      while(currNode->next != nullptr) {
        currNode = currNode->next;
        removeNode = removeNode->next;
      }

      // Remove the node
      removeNode->next = removeNode->next->next;

      return head;
    }
};

ListNode* construct(vector<int>& input) {
  if(input.size() == 0) return nullptr;

  ListNode* root = nullptr;
  ListNode* prevNode;
  ListNode* newNode;
  for(int i: input) {
    if(root == nullptr) {
      root = new ListNode(i);
      prevNode = root;
    } else {
      newNode = new ListNode(i);
      prevNode->next = newNode;
      prevNode = prevNode->next;
    }
  }

  return root;
}

void deleteAll(ListNode* root) {
  if(root == nullptr) return;

  deleteAll(root->next);
  delete(root);
}

void printList(ListNode* root) {
  while(root != nullptr) {
    cout << root->val << " ";
    root = root->next;
  }

  cout << endl;
}

int main() {
  Solution s;

  vector<int> input = {1,2};
  ListNode* root = construct(input);
  printList(root);

  ListNode* newHead = s.removeNthFromEnd(root, 2);
  printList(newHead);
  deleteAll(root);
}
