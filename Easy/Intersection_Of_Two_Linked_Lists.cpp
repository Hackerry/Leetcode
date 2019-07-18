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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
      return smartSolutionCopy(headA, headB);
    }

    // O(m+n) <- 2(m+n)
    // Think like two runners who ran through the same distance after running
    // m+n distance.
    ListNode *smartSolutionCopy(ListNode *headA, ListNode *headB) {
      if(headA == nullptr || headB == nullptr) return nullptr;

      ListNode* currA = headA;
      ListNode* currB = headB;
      while(currA != currB && currA != nullptr && currB != nullptr) {
        currA = currA->next;
        currB = currB->next;
        if(currA == currB) return currA;

        if(currA == nullptr) currA = headB;
        if(currB == nullptr) currB = headA;
      }

      return currA;
    }

    // 2(m+n) -> O(m+n)
    // See solution 3
    ListNode *mySolutionThree(ListNode *headA, ListNode *headB) {
      if(headA == nullptr || headB == nullptr) return nullptr;
      else if(headA == headB) return headA;

      ListNode* currA = headA;
      ListNode* currB = headB;
      int ASize = 1;
      int BSize = 1;

      while(currA->next != nullptr) {
        currA = currA->next;
        ASize++;
      }

      while(currB->next != nullptr) {
        currB = currB->next;
        BSize++;
      }

      if(currA != currB) return nullptr;

      currA = headA;
      currB = headB;
      if(ASize < BSize) {
        for(int i = 0; i < BSize-ASize; i++) currB = currB->next;
      } else {
        for(int i = 0; i < ASize-BSize; i++) currA = currA->next;
      }

      while(currA != nullptr && currB != nullptr) {
        if(currA == currB) return currA;
        currA = currA->next;
        currB = currB->next;
      }

      return nullptr;
  }
};

vector<ListNode*> construct(vector<int>& listA, vector<int>& listB, int posA, int posB) {
  if(listA.size() < posA || listB.size() < posB) {
    cerr << "Check your positions." << endl;
    return vector<ListNode*>();
  } else if(posA < 0 || posB < 0) {
    cerr << "Position is none negative." << endl;
    return vector<ListNode*>();
  }

  ListNode* headA = nullptr;
  ListNode* headB = nullptr;
  ListNode* currNodeA;
  ListNode* currNodeB;
  for(int i = 0; i < posA; i++) {
    if(headA == nullptr) {
      headA = new ListNode(listA[i]);
      currNodeA = headA;
    }
    else {
      currNodeA->next = new ListNode(listA[i]);
      currNodeA = currNodeA->next;
    }
  }

  for(int i = 0; i < posB; i++) {
    if(headB == nullptr) {
      headB = new ListNode(listB[i]);
      currNodeB = headB;
    }
    else {
      currNodeB->next = new ListNode(listB[i]);
      currNodeB = currNodeB->next;
    }
  }

  if(posA+1 < listA.size()) {
    currNodeA->next = new ListNode(listA[posA]);
    currNodeB->next = currNodeA->next;
    currNodeA = currNodeA->next;

    for(int i = posA+1; i < listA.size(); i++) {
      currNodeA->next = new ListNode(listA[i]);
      currNodeA = currNodeA->next;
    }
  }

  return vector<ListNode*>{headA, headB};
}

void printList(ListNode* head) {
  ListNode* currNode = head;
  while(currNode != nullptr) {
    cout << currNode->val << " ";
    currNode = currNode->next;
  }
  cout << endl;
}

void deleteAll(ListNode* headA, ListNode* headB, int posA) {
  ListNode* nextNode;
  ListNode* currNode = headA;
  for(int i = 0; i < posA; i++) {
    if(currNode != nullptr) {
      nextNode = currNode->next;
      delete(currNode);
      currNode = nextNode;
    }
  }

  currNode = headB;
  while(currNode != nullptr) {
    nextNode = currNode->next;
    delete(currNode);
    currNode = nextNode;
  }
}

int main() {
  Solution s;
  vector<int> listA = {2,6,4};
  vector<int> listB = {1,5};
  int posA = 3;
  int posB = 2;

  vector<ListNode*> heads = construct(listA, listB, posA, posB);
  printList(heads[0]);
  printList(heads[1]);
  ListNode* intersection = s.getIntersectionNode(heads[0], heads[1]);
  if(intersection == nullptr) cout << "null" << endl;
  else cout << intersection->val << endl;
  deleteAll(heads[0], heads[1], posA);
}
