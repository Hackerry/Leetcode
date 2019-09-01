#include <iostream>
#include "../Collections/LinkedList.cpp"

using namespace std;

class Solution {
  public:
    // My orginal solution tests nullptr head.
    // This one comes from solution 1.
    // Have the same runtime but much cleaner.
    ListNode* partition(ListNode* head, int x) {
      ListNode* start = new ListNode(0);
      ListNode* newHead = start;
      ListNode* end = new ListNode(0);
      ListNode* bigHead = end;

      while(head != nullptr) {
        if(head->val < x) {
          start->next = head;
          start = start->next;
        } else {
          end->next = head;
          end = end->next;
        }

        head = head->next;
      }

      end->next = nullptr;

      // Link them together
      start->next = bigHead->next;
      return newHead->next;
    }
};

int main() {
  LinkedListUtil l;
  Solution s;
  vector<int> input = {1,2};
  ListNode* start = l.construct(input);

  ListNode* newHead = s.partition(start, 0);
  ListNode* currNode = newHead;
  l.printList(newHead);
}
