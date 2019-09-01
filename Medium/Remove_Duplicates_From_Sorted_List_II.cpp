#include <iostream>
#include "../Collections/LinkedList.cpp"

using namespace std;

class Solution {
  public:
    ListNode* deleteDuplicates(ListNode* head) {
      if(head == nullptr) return nullptr;
      ListNode* newHead = new ListNode(0);
      ListNode* lastPos = newHead;
      newHead->next = head;

      ListNode* currNode = head;
      int prevVal = currNode->val;
      currNode = currNode->next;
      char duplicates = false;

      while(currNode != nullptr) {
        if(prevVal != currNode->val) {
          if(!duplicates) lastPos = lastPos->next;
          else lastPos->next = currNode;
          prevVal = currNode->val;
          duplicates = false;
        } else {
          duplicates = true;
        }
        currNode = currNode->next;
      }

      // End check
      if(duplicates) lastPos->next = nullptr;

      return newHead->next;
    }
};

int main() {
  Solution s;
  LinkedListUtil l;
  vector<int> input = {1,1,1,1,1,2};
  ListNode* head = l.construct(input);
  l.printList(s.deleteDuplicates(head));
}
