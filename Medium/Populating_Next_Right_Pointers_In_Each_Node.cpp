#include <vector>
#include <list>
#include <iostream>

class Node {
  public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
      val = _val;
      left = _left;
      right = _right;
      next = _next;
    }
};

class Solution {
  public:
    // Discuss top solution
    // Same runtime???
    Node* connect(Node* root) {
      if(root == nullptr) return nullptr;

      Node* pare = root;
      Node* curr = nullptr;
      pare->next = nullptr;

      while(pare->left != nullptr) {
        curr = pare;
        while(curr != nullptr) {
          curr->left->next = curr->right;
          if(curr->next != nullptr) curr->right->next = curr->next->left;
          curr = curr->next;
        }
        pare = pare->left;
      }
      return root;
    }

    // 73%, there is a better solution!
    Node* connectOriginal(Node* root) {
      if(root == nullptr) return nullptr;

      list<Node*> tempList;
      tempList.push_back(root);

      int size;
      Node* currNode;
      while(!tempList.empty()) {
        size = tempList.size();
        for(int i = 0; i < size; i++) {
          currNode = tempList.front();
          tempList.pop_front();
          if(i < size-1) currNode->next = tempList.front();
          else currNode->next = nullptr;
          if(currNode->left != nullptr) {
            tempList.push_back(currNode->left);
            tempList.push_back(currNode->right);
          }
        }
      }

      return root;
    }
};
