#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include "../Collections/Tree.cpp"

using namespace std;

class Solution {
  public:
    // Holy one pass!
    // 92.82% 100%
    // Crucial observation:
    // 1. Think of the order of inorder traversal as picking out grapes.
    //    First the smallest branch, then take the parent branch (which now is 
    //    the smallest branch), and so on. Our build tree process is simply the
    //    reverse.
    // 2. In summary:
    //    For every current node, the next node in inorder is either its right
    //    child or its parent.
    //    If next node's preorder is smaller, it's a parent node.
    //    Store a stack of parent nodes and it's the parent of the node with
    //    the smallest preorder # that's bigger than next node's preorder #.
    //
    //    If next node is a right child, put current root in stack and point
    //    to the next node as the root of the right subtree. Grow the subtree
    //    from there.
    //
    // The recursive solution is also pretty elegant: (But I hate recursive...)
    // Every time get the head of preorder as the root. Split inorder into two
    // subtree based on the position of root. Repeat until there's only one
    // node left and build the tree back along the way.
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
      unordered_map<int,int> preMap;
      stack<TreeNode*> roots;
      int N = preorder.size();

      if(N == 0) return nullptr;

      // Store their orders
      for(int i = 0; i < N; i++) preMap.insert({preorder[i], i});

      // Start search
      TreeNode* currNode = new TreeNode(inorder[0]);
      TreeNode* nextNode;
      int currOrder = preMap.find(inorder[0])->second;
      int compOrder;
      for(int i = 1; i < N; i++) {
        nextNode = new TreeNode(inorder[i]);
        compOrder = preMap.find(inorder[i])->second;

        if(compOrder > currOrder) {
          // This is a node from right subtree
          roots.push(currNode);
          currNode = nextNode;
        } else {
          // This is a parent node
          while(!roots.empty() && preMap.find(roots.top()->val)->second > compOrder) {
            roots.top()->right = currNode;
            currNode = roots.top();
            roots.pop();
          }

          // Find whose parent this is
          nextNode->left = currNode;
          currNode = nextNode;
        }

        currOrder = preMap.find(inorder[i])->second;
      }

      // Restore the root
      while(!roots.empty()) {
        roots.top()->right = currNode;
        currNode = roots.top();
        roots.pop();
      }

      return currNode;
    }
};

void deleteAll(TreeNode* root) {
  if(root == nullptr) return;
  deleteAll(root->left);
  deleteAll(root->right);
  delete(root);
}

int main() {
  Solution s;
  vector<int> pre = {3,9,20,15,7};
  vector<int> in = {9,3,15,20,7};

  Tree t;
  TreeNode* root = s.buildTree(pre, in);
  t.printLevelOrder(root);

  deleteAll(root);
}
