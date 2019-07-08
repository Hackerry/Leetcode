// C++ has something called a queue

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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
      vector<vector<int>> result;
      if(root == nullptr) return result;

      int levelBorderIdx = 0;
      TreeNode* currNode;
      vector<TreeNode*> tempList;
      stack<vector<int>> tempStack;

      tempList.push_back(root);
      vector<int> list;
      list.push_back(root->val);
      tempStack.push(list);

      while(!tempList.empty()) {
        currNode = tempList.front();
        tempList.erase(tempList.begin());
        if(currNode->left != nullptr) tempList.push_back(currNode->left);
        if(currNode->right != nullptr) tempList.push_back(currNode->right);

        if(levelBorderIdx == 0) {
          levelBorderIdx = tempList.size()-1;
          vector<int> newList;
          for(TreeNode* node: tempList) {
            newList.push_back(node->val);
          }

          if(!tempList.empty()) tempStack.push(newList);
        }
        else levelBorderIdx--;
      }

      while(!tempStack.empty()) {
        result.push_back(tempStack.top());
        tempStack.pop();
      }

      return result;
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
  int arr[] = {3,9,20,0,0,15,7};
  TreeNode* root = construct(arr, 1);

  cout << "Traversal valuess are: " << endl;

  for(vector<int> v: s.levelOrderBottom(root)) {
    for(int i: v) cout << i << " ";
    cout << endl;
  }
  cout << endl;
}
