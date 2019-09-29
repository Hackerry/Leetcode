#include <iostream>
#include <vector>
#include <queue>
#include "../Collections/Parser.cpp"

using namespace std;

class Solution {
  public:
    int findCircleNum(vector<vector<int>>& M) {
      return BFS(M);
    }

    // Same runtime using BFS
    int BFS(vector<vector<int>>& M) {
      int N = M.size();
      int circleNum = N;
      vector<int> groups;
      queue<int> tempList;

      // Initialize ID
      for(int i = 0; i < N; i++) groups.push_back(i);

      int currPerson;
      for(int i = 0; i < N; i++) {
        // This is a leaf
        if(groups[i] == i) {
          tempList.push(i);

          while(!tempList.empty()) {
            currPerson = tempList.front();
            tempList.pop();

            for(int j = i+1; j < N; j++) {
              if(M[currPerson][j] == 1) {
                // If they are not connected
                if(groups[j] != i) {
                  groups[j] = i;
                  circleNum--;

                  // Push person in
                  tempList.push(j);
                }
              }
            }
          }
        }
      }

      return circleNum;
    }

    // Path compression when finding the two root
    // 82.82% speed
    int unionFindWithCompression(vector<vector<int>>& M) {
      vector<int> people;
      int N = M.size();
      int circleNum = N;

      // Fill with id
      for(int i = 0; i < N; i++) people.push_back(i);

      for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
          // If two people know each other
          if(M[i][j] == 1) {
            // If they are from different groups
            if(people[i] != people[j]) {
              // It is from another tree
              if(people[j] < j) {
                int root1 = people[j];
                int root2 = people[i];
                // Find two roots
                while(people[root1] != root1) {
                  root1 = people[root1];
                }
                while(people[root2] != root2) {
                  root2 = people[root2];
                }

                // They are indeed different
                if(root1 != root2) people[root1] = root2;
                else {
                  // Path compression
                  people[j] = root1;
                  people[i] = root1;
                  continue;
                }
              } else {
                // It is from a leaf
                people[j] = people[i];
              }

              circleNum--;
            }
          }
        }
      }

      return circleNum;
    }
};

int main() {
  Parser p;
  Solution s;

  vector<vector<int>> list = p.parse2DInt("[[1,1,0,0,0,0,0,1,0,0,0,0,0,0,0],[1,1,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,1,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,1,0,1,1,0,0,0,0,0,0,0,0],[0,0,0,0,1,0,0,0,0,1,1,0,0,0,0],[0,0,0,1,0,1,0,0,0,0,1,0,0,0,0],[0,0,0,1,0,0,1,0,1,0,0,0,0,1,0],[1,0,0,0,0,0,0,1,1,0,0,0,0,0,0],[0,0,0,0,0,0,1,1,1,0,0,0,0,1,0],[0,0,0,0,1,0,0,0,0,1,0,1,0,0,1],[0,0,0,0,1,1,0,0,0,0,1,1,0,0,0],[0,0,0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,1,0,1,0,0,0,0,1,0],[0,0,0,0,0,0,0,0,0,1,0,0,0,0,1]]");
  cout << s.findCircleNum(list) << endl;
}
