#include <iostream>
#include <vector>
#include <queue>
#include "../Collections/Tree.cpp"

using namespace std;

class Solution {
  public:
    // Passed first time!
    // Practice makes perfect (see ../Collections/Tree.cpp -- printLevelOrder())
    vector<vector<int>> levelOrder(TreeNode* root) {
      vector<vector<int>> result;
      if(root == nullptr) return result;

      queue<TreeNode*> nodeList;
      int lastIndex = 0;
      TreeNode* currNode;
      nodeList.push(root);
      vector<int> newList;

      while(!nodeList.empty()) {
        currNode = nodeList.front();
        nodeList.pop();

        newList.push_back(currNode->val);
        if(currNode->left != nullptr) nodeList.push(currNode->left);
        if(currNode->right != nullptr) nodeList.push(currNode->right);
        if(lastIndex == 0) {
          lastIndex = nodeList.size();
          result.push_back(newList);
          newList = vector<int>();
        }
        lastIndex--;
      }

      return result;
    }
};

int main() {
  Solution s;
  vector<int> input = {3,9,2,-1,-1,6,-1};
  Tree t;
  TreeNode* root = t.construct(input);
  t.printLevelOrder(root);

  for(vector<int>& v: s.levelOrder(root)) {
    cout << "[";
    for(int i: v) cout << i << " ";
    cout << "]" << endl;
  }
}
