#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Tree {
  private:
    vector<TreeNode*> nodes;

  public:
    // Construct a tree from level-order traversal list and return the root
    // -1 means nullptr
    TreeNode* construct(const vector<int>& input) {
      int S = input.size();
      if(S == 0 || input[0] == -1) return nullptr;

      // Initialize root
      TreeNode* root = new TreeNode(input[0]);
      nodes.push_back(root);

      // Keep track of level-order traversal nodes
      list<TreeNode*> currNodes;
      currNodes.push_back(root);

      // Main loop
      TreeNode* pare;
      int index = 1;
      while(!currNodes.empty()) {
        pare = currNodes.front();
        currNodes.pop_front();

        // Add left node if exsists
        if(index < S && input[index] != -1) {
          pare->left = new TreeNode(input[index]);
          nodes.push_back(pare->left);
          currNodes.push_back(pare->left);
        }
        index++;

        // Add right node if exsists
        if(index < S && input[index] != -1) {
          pare->right = new TreeNode(input[index]);
          nodes.push_back(pare->right);
          currNodes.push_back(pare->right);
        }
        index++;
      }

      return root;
    }

    // Print level-order traversal string
    void printLevelOrder(TreeNode* root) {
      list<TreeNode*> temp;
      temp.push_back(root);

      cout << "[";
      TreeNode* currNode;
      while(!temp.empty()) {
        currNode = temp.front();
        temp.pop_front();

        if(currNode != nullptr) {
          cout << currNode->val;
          temp.push_back(currNode->left);
          temp.push_back(currNode->right);
        } else cout << "null";

        if(!temp.empty()) cout << ",";
      }

      cout << "]" << endl;
    }

    // Destructor
    ~Tree() {
      for(TreeNode* node: nodes) delete(node);
    }
};
