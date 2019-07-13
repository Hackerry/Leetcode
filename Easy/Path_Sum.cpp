#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  public:
    bool hasPathSum(TreeNode* root, int sum) {
      if(root == nullptr) return false;

      queue<TreeNode*> tempList;
      queue<int> sums;
      tempList.push(root);
      sums.push(0);

      TreeNode* currNode;
      int currSum;
      while(!tempList.empty()) {
        currNode = tempList.front();
        currSum = sums.front();
        tempList.pop();
        sums.pop();

        if(currNode->left == nullptr && currNode->right == nullptr) {
          if(currNode->val + currSum == sum) return true;
        } else {
          if(currNode->left != nullptr) {
            tempList.push(currNode->left);
            sums.push(currSum+currNode->val);
          }
          if(currNode->right != nullptr) {
            tempList.push(currNode->right);
            sums.push(currSum+currNode->val);
          }
        }
      }

      return false;
    }
};

void deleteAll(TreeNode* root) {
  if(root == nullptr) return;

  deleteAll(root->left);
  deleteAll(root->right);
  delete(root);
}

TreeNode* construct(vector<int>& input) {
  if(input.size() == 0 || input[0] == 0) return nullptr;

  int index = 0;
  TreeNode* root = new TreeNode(input[index++]);

  queue<TreeNode*> tempList;
  tempList.push(root);

  TreeNode* currNode;
  TreeNode* newNode;
  while(!tempList.empty() && index < input.size()) {
    currNode = tempList.front();
    tempList.pop();

    if(input[index] != 0) {
      newNode = new TreeNode(input[index]);
      currNode->left = newNode;
      tempList.push(newNode);
    }
    index++;
    if(input[index] != 0) {
      newNode = new TreeNode(input[index]);
      currNode->right = newNode;
      tempList.push(newNode);
    }
    index++;
  }

  return root;
}

int main() {
  vector<int> input = {5,4,8,11,0,13,4,7,1,0,0,0,1};
  TreeNode* root = construct(input);

  Solution s;
  cout << (s.hasPathSum(root, 22) == 1? "true": "false") << endl;
  deleteAll(root);

  return 0;
}
