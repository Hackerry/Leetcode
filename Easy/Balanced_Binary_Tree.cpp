#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  public:
    bool provedWrong = false;
    bool isBalanced(TreeNode* root) {
      if(root == nullptr) return true;

      height(root);

      return !provedWrong;
    }

    int height(TreeNode* node) {
      if(node == nullptr || provedWrong) return 0;

      int leftHeight = height(node->left);
      int rightHeight = height(node->right);

      if(abs(leftHeight-rightHeight) > 1) provedWrong = true;

      return max(leftHeight, rightHeight) + 1;
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

void printLevelOrder(TreeNode* root) {
  if(root == nullptr) return;

  queue<TreeNode*> q;
  q.push(root);
  cout << root->val << " ";

  TreeNode* currNode;
  while(!q.empty()) {
    currNode = q.front();
    q.pop();

    if(currNode->left == nullptr) cout << "null ";
    else cout << currNode->left->val << " ";

    if(currNode->right == nullptr) cout << "null ";
    else cout << currNode->right->val << " ";

    if(currNode->left != nullptr) q.push(currNode->left);
    if(currNode->right != nullptr) q.push(currNode->right);
  }

  cout << endl;
}

int main() {
  vector<int> input = {1,2,2,3,0,0,3,4,0,0,4/*3,9,20,0,0,15,7*/};
  TreeNode* root = construct(input);
  printLevelOrder(root);

  Solution s;
  cout << (s.isBalanced(root) == 1? "true": "false") << endl;
  deleteAll(root);

  return 0;
}
