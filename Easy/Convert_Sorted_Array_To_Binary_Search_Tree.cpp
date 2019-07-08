#include <iostream>
#include <vector>
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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
      if(nums.size() == 0) return nullptr;

      return constructHelper(nums, 0, nums.size()-1);
    }

    TreeNode* constructHelper(vector<int>& nums, int start, int end) {
      if(start > end) return nullptr;

      int mid = (start+end)/2;
      TreeNode* newNode = new TreeNode(nums[mid]);

      newNode->left = constructHelper(nums, start, mid-1);
      newNode->right = constructHelper(nums, mid+1, end);

      return newNode;
    }
};

void deleteAll(TreeNode* root) {
  if(root == nullptr) return;

  deleteAll(root->left);
  deleteAll(root->right);
  delete(root);
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
  vector<int> input = {-10,-3,0,5,9};

  Solution s;
  TreeNode* root = s.sortedArrayToBST(input);
  printLevelOrder(root);
  deleteAll(root);
}
