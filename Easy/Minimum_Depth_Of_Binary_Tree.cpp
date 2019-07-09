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
		int minDepth(TreeNode* root) {
      if(root == nullptr) return 0;

      queue<TreeNode*> tempList;
      tempList.push(root);

      TreeNode* currNode;
      int level = 1;
      int lastIdx = 0;
      while(!tempList.empty()) {
        currNode = tempList.front();
        tempList.pop();

        if(currNode->left == nullptr && currNode->right == nullptr) return level;
        if(currNode->left != nullptr) tempList.push(currNode->left);
        if(currNode->right != nullptr) tempList.push(currNode->right);

        if(lastIdx == 0) {
          lastIdx = tempList.size()-1;
          level++;
        }
        else lastIdx--;
      }

      return level;
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
  TreeNode* root;
  Solution s;

  vector<int> input = {/*3,9,20,0,0,15,7*/1,2,3,4,0,0,5};
  root = construct(input);

  cout << s.minDepth(root) << endl;
  deleteAll(root);
}
