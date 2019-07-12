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
    ListNode* swapPairs(ListNode* head) {
      if(head == nullptr || head->next == nullptr) return head;

      ListNode* first = head;
      ListNode* second = head->next;
      ListNode* root = second;
      ListNode* prevChunk = nullptr;

      while(first != nullptr && second != nullptr) {
        first->next = second->next;
        second->next = first;

        if(prevChunk != nullptr) prevChunk->next = second;
        prevChunk = first;

        first = first->next;
        if(first != nullptr) second = first->next;
      }

      return root;
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

  vector<int> input = {};
  ListNode* root = construct(input);
  printList(root);

  ListNode* newHead = s.swapPairs(root);
  printList(newHead);
  deleteAll(newHead);
}
