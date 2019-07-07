/*
 * Idea: Traverse left subtree and store values in a vector. Compare the values
 *       when traversing right subtree.
 * Better idea:
 * Use mirror as in solution.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <stdio.h>
#include <math.h>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  public:
    bool isSymmetricCompare(TreeNode* root) {
      if(root == nullptr) return true;

      vector<TreeNode*> nodes;
      stack<TreeNode*> tempNodes;
      tempNodes.push(root->left);

      TreeNode* currNode;
      while(!tempNodes.empty()) {
        currNode = tempNodes.top();
        tempNodes.pop();
        if(currNode != nullptr) {
          tempNodes.push(currNode->left);
          tempNodes.push(currNode->right);
        }

        nodes.push_back(currNode);
      }

      int index = 0;
      tempNodes.push(root->right);
      while(!tempNodes.empty()) {
        currNode = tempNodes.top();
        tempNodes.pop();
        if(currNode == nullptr && nodes[index] == nullptr) {
          index++;
          continue;
        }
        if(currNode == nullptr || nodes[index] == nullptr) return false;
        tempNodes.push(currNode->right);
        tempNodes.push(currNode->left);
        if(currNode->val != nodes[index]->val) return false;
        index++;
      }

      return true;
    }

    bool isSymmetricIterative(TreeNode* root) {
      if(root == nullptr) return true;

      vector<TreeNode*> list;
      list.push_back(root);
      list.insert(list.begin(), root);

      TreeNode* left;
      TreeNode* right;
      while(!list.empty()) {
        left = list.front();
        list.erase(list.begin());
        right = list.back();
        list.pop_back();

        if(left == nullptr && right == nullptr) continue;
        if(left == nullptr || right == nullptr) return false;
        if(left->val != right->val) return false;

        list.insert(list.begin(), left->left);
        list.insert(list.begin(), left->right);
        list.push_back(right->right);
        list.push_back(right->left);
      }

      return true;
    }

    bool isSymmetric(TreeNode* root) {
      if(root == nullptr) return true;
      return isMirror(root->left, root->right);
    }

    bool isMirror(TreeNode* left, TreeNode* right) {
      if(left == nullptr && right == nullptr) return true;
      if(left == nullptr || right == nullptr) return false;
      else {
        return left->val == right->val && isMirror(left->left, right->right)
          && isMirror(left->right, right->left);
      }
    }
};

void deleteAll(TreeNode* root) {
  if(root == nullptr) return;

  deleteAll(root->left);
  deleteAll(root->left);
  delete(root);
}

TreeNode* construct(int arr[], int length) {
  if(length == 0) return nullptr;

  vector<TreeNode*> levelNode;
  int index = 0;
  TreeNode* root = new TreeNode(arr[index++]);
  int level = 1;
  levelNode.push_back(root);

  TreeNode* newNode;
  while(pow(2, level) <= length) {
    for(int i = 0; i < level; i++) {
      newNode = new TreeNode(arr[index+2*i]);
      levelNode[i]->left = newNode;
      levelNode.push_back(newNode);
      newNode = new TreeNode(arr[index+2*i+1]);
      levelNode.push_back(newNode);
      levelNode[i]->right = newNode;
    }

    levelNode.erase(levelNode.begin(), levelNode.begin()+index);
    level++;
    index += levelNode.size();
  }

  return root;
}

int main() {
  int arr[] = {1,2,2,3,4,4,3};
  TreeNode* root = construct(arr, 7);
  Solution s;

  cout << "Is symmetrical? " << (s.isSymmetric(root)? "true": "false") << endl;

  deleteAll(root);
}

