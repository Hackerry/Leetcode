#include <iostream>
#include "../Collections/LinkedList.cpp"

using namespace std;

class Solution {
  public:
    // Not sure why same idea but different implementation gives slower speed...
    // mem 100% though
    ListNode* reverseBetween(ListNode* head, int m, int n) {
      if(head == nullptr) return nullptr;

      int counter = 1;
      ListNode* end;
      ListNode* start = nullptr;
      ListNode* prevNode;
      ListNode* tempNode;
      ListNode* currNode = head;

      while(currNode != nullptr) {
        if(counter < m-1) {
          currNode = currNode->next;
        } else if(counter == m-1) {
          start = currNode;
          currNode = currNode->next;
        } else if(counter == m) {
          end = currNode;
          prevNode = currNode;
          currNode = currNode->next;
        } else if(counter > m && counter <= n) {
          tempNode = currNode->next;
          currNode->next = prevNode;
          prevNode = currNode;
          currNode = tempNode;
        } else if(counter > n) {
          break;
        }

        counter++;
      }

      if(start != nullptr) start->next = prevNode;
      else head = prevNode;
      end->next = currNode;

      return head;
    }
};

int main() {
  Solution s;
  vector<int> list = {1,2,3,4,5,6,7};
  LinkedListUtil l;
  ListNode* start = l.construct(list);
  ListNode* newHead = s.reverseBetween(start, 3, 4);
  l.printList(newHead);
}
