#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
  public:
    // 0ms!!!!
    // Complicated code though
    vector<int> inorderTraversalOri(TreeNode* root) {
      stack<TreeNode*> pare;
      stack<TreeNode*> left;
      stack<TreeNode*> right;
      vector<int> result;
      if(root == nullptr) return result;

      pare.push(root);
      if(root->left != nullptr) left.push(root->left);
      right.push(root->right);
      TreeNode* currNode;

      while(!right.empty()) {
        // First goes left, which preserves the left most child in the subtree
        if(!left.empty()) {
          currNode = left.top();
          left.pop();

          // Traverse down the tree if possible
          if(currNode->left != nullptr) {
            left.push(currNode->left);
            pare.push(currNode);
            right.push(currNode->right);
          } else {
            // If this is a leaf node, put it directly in result
            // No need to test it again
            if(currNode->right == nullptr)
              result.push_back(currNode->val);
            else {
              right.push(currNode->right);
              pare.push(currNode);
            }
          }
        } else {
          // Left subtree finished, put parent in list
          currNode = pare.top();
          pare.pop();
          result.push_back(currNode->val);

          // Get right subtree. If it isn't null, go down this subtree.
          currNode = right.top();
          right.pop();
          if(currNode != nullptr) {
            pare.push(currNode);
            if(currNode->left != nullptr) left.push(currNode->left);
            right.push(currNode->right);
          }
        }
      }

      return result;
    }

    // Silly me... why not use only one stack?
    // Solution 2
    vector<int> inorderTraversal(TreeNode* root) {
      vector<int> result;
      stack<TreeNode*> nodes;
      TreeNode* currNode = root;

      // First condition is used to first time execute the loop
      while(currNode != nullptr || !nodes.empty()) {
        // Add all left subtree nodes
        while(currNode != nullptr) {
          nodes.push(currNode);
          currNode = currNode->left;
        }

        // Left subtree is done, push in subtree parent node 
        // and goes to the right
        currNode = nodes.top();
        nodes.pop();
        result.push_back(currNode->val);
        currNode = currNode->right;
      }

      return result;
    }
};
