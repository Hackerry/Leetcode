#include <iostream>
#include <list>
#include <limits>
#include <stack>
#include "../Collections/Tree.cpp"

using namespace std;

class Solution {
  public:
    // Solution 3
    bool isValidBST(TreeNode* root) {
      stack<TreeNode*> path;
      TreeNode* last = nullptr;

      while(!path.empty() || root != nullptr) {
        while(root != nullptr) {
          path.push(root);
          root = root->left;
        }

        root = path.top();
        path.pop();
        if(last != nullptr && last->val >= root->val) return false;
        last = root;
        root = root->right;
      }

      return true;
    }

    // Bug 1: test strictly less than case [1,1]
    // Bug 2: wrong left and right values, no need to take min or max
    // Bug 3: can't take special value like max and min limits
    bool isValidBSTRecursive(TreeNode* root) {
      if(root == nullptr) return true;

      return isValid(root->left, nullptr, root)
        && isValid(root->right, root, nullptr);
    }

    bool isValid(TreeNode* node, TreeNode* left, TreeNode* right) {
      if(node == nullptr) return true;

      if((left != nullptr && node->val <= left->val) || 
          (right != nullptr && node->val >= right->val) ) return false;

      return isValid(node->left, left, node)
        && isValid(node->right, node, right);
    }
};

int main() {
  Solution s;
  Tree t;
  vector<int> input = {3,1,5,0,2,4,6};
  TreeNode* head = t.construct(input);
  t.printLevelOrder(head);
  cout << s.isValidBST(head) << endl;
}
