#include <iostream>
#include <vector>
#include <list>
#include "../Collections/Tree.cpp"

using namespace std;

class Solution {
  public:
    // Fastest, 8ms
    // Cases are complicated, use induction.
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
      vector<vector<int>> result;
      if(root == nullptr) return result;

      list<TreeNode*> nodeList;
      int lastIndex = 0;
      bool reverse = false;
      TreeNode* currNode;
      nodeList.push_back(root);
      vector<int> newList;

      while(!nodeList.empty()) {
        if(reverse) {
          currNode = nodeList.back();
          nodeList.pop_back();
        } else {
          currNode = nodeList.front();
          nodeList.pop_front();
        }

        newList.push_back(currNode->val);

        if(reverse) {
          if(currNode->right != nullptr) nodeList.push_front(currNode->right);
          if(currNode->left != nullptr) nodeList.push_front(currNode->left);
        } else {
          if(currNode->left != nullptr) nodeList.push_back(currNode->left);
          if(currNode->right != nullptr) nodeList.push_back(currNode->right);
        }

        if(lastIndex == 0) {
          lastIndex = nodeList.size();
          result.push_back(newList);
          newList = vector<int>();

          reverse = !reverse;
        }
        lastIndex--;
      }

      return result;
    }
};

int main() {
  Solution s;
  vector<int> input = {1,2,3,4,5,6,7,8,9,10};
  Tree t;
  TreeNode* root = t.construct(input);
  t.printLevelOrder(root);

  for(vector<int>& v: s.zigzagLevelOrder(root)) {
    cout << "[";
    for(int i: v) cout << i << " ";
    cout << "]" << endl;
  }
}
