#include <iostream>
#include <vector>
#include "../Collections/LinkedList.cpp"

using namespace std;

class Solution {
  public:
    // Original solution
    // Other solution: link the list in a cycle first and then break at desired pos
    ListNode* rotateRight(ListNode* head, int k) {
      if(head == nullptr) return head;

      int size = 1;
      ListNode* end;
      ListNode* cut;
      ListNode* cutPrev;

      // Find size of the list and the end node
      end = head;
      while(end->next != nullptr) {
        size++;
        end = end->next;
      }

      // Find the cut position
      k %= size;

      // Edge case, rotate value is 0
      if(k == 0) return head;

      k = size-k;

      cutPrev = nullptr;
      cut = head;
      while(k > 0) {
        cutPrev = cut;
        cut = cut->next;
        k--;
      }
      cout << cut->val << " " << cutPrev->val << " " << end->val << endl;

      // Rotate list
      cutPrev->next = nullptr;
      end->next = head;
      return cut;
    }
};

int main() {
  Solution s;
  vector<int> input = {1,2,3,4,5,6};
  int k = 11;

  LinkedList l;
  ListNode* head = l.construct(input);
  l.printList(head);
  head = s.rotateRight(head, k);
  l.printList(head);
}
