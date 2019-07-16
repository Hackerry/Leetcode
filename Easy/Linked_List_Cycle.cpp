#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  public:
    bool hasCycle(ListNode *head) {
      return runnerMethod(head);
    }

    bool destructiveMethod(ListNode *head) {
      if(head == nullptr) return false;

      ListNode* currNode = head;
      ListNode* nextNode = head->next;
      while(currNode != nullptr) {
        // Slef-loop, cycle found!
        if(currNode->next == currNode) return true;

        currNode->next = currNode;
        currNode = nextNode;
        if(nextNode != nullptr) {
          nextNode = nextNode->next;
        }
      }

      return false;
    }

    bool runnerMethod(ListNode* head) {
      if(head == nullptr || head->next == nullptr) return false;

      ListNode* fastRunner = head.next;
      ListNode* slowRunner = head;
      while(fastRunner != slowRunner) {
        if(fastRunner == nullptr || fastRunner->next == nullptr) {
          return false;
        }
        slowRunner = slowRunner->next;
        fastRunner = fastRunner->next->next;
      }

      return false;
    }
};
