#include <iostream>
#include <vector>
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
    int maxDepthIterative(TreeNode* root) {
      if(root == nullptr) return 0;

      int levelBorderIdx = 0;
      int level = 0;
      TreeNode* currNode;
      vector<TreeNode*> tempList;

      tempList.push_back(root);

      while(!tempList.empty()) {
        currNode = tempList.front();
        tempList.erase(tempList.begin());
        if(currNode->left != nullptr) tempList.push_back(currNode->left);
        if(currNode->right != nullptr) tempList.push_back(currNode->right);

        if(levelBorderIdx == 0) {
          level++;
          levelBorderIdx = tempList.size()-1;
        }
        else levelBorderIdx--;
      }

      return level;

    }

    int maxDepth(TreeNode* root) {
      if(root == nullptr) return 0;

      return maxDepthHelper(root, 0);
    }

    int maxDepthHelper(TreeNode* node, int height) {
      if(node == nullptr) return height;

      return max(maxDepthHelper(node->left, height+1), maxDepthHelper(node->right, height+1));
    }
};

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
  Solution s;
  int arr[] = {3};
  TreeNode* root = construct(arr, 1);

  cout << "Max depth: " << s.maxDepth(root) << endl;
}
