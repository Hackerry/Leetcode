#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
  public:
    string simplifyPathIdiotVersion(string path) {
      const char SLS = '/';
      const char DOT = '.';

      vector<string> nodes;
      int pos;
      while(path.size() != 0) {
        pos = path.find(SLS);
        // Reach end of string
        if(pos == -1) pos = path.size();

        // Repeated slashes if pos = 0
        if(pos != 0) {
          // One dot
          if(path[0] == DOT) {
            // More things to follow
            if(pos > 1) {
              // Two dots
              if(path[1] == DOT) {
                // More things to follow
                if(pos > 2) {
                  // ...
                  nodes.push_back(path.substr(0, pos));
                } else {
                  // ../
                  if(!nodes.empty()) nodes.pop_back();
                }
              } else {
                // .hidden
                nodes.push_back(path.substr(0, pos));
              }
            } // Else do nothing
          } else {
            // a/
            nodes.push_back(path.substr(0, pos));
          }
        }

        // Careful when there is a slash at the end: a/b/c/../
        if(pos < path.size()-1) path = path.substr(pos+1, path.size()-1);
        else path = "";
      }

      string result = "";
      for(string s: nodes) {
        result += SLS + s;
      }
      // Going over root
      if(result.size() == 0) result += SLS;

      return result;
    }

    // Where you know you suck at C++
    // https://leetcode.com/problems/simplify-path/discuss/25680/C%2B%2B-10-lines-solution
    string simplifyPath(string path) {
      string res, tmp;
      vector<string> stk;
      stringstream ss(path);
      while(getline(ss,tmp,'/')) {
        if (tmp == "" or tmp == ".") continue;
        if (tmp == ".." and !stk.empty()) stk.pop_back();
        else if (tmp != "..") stk.push_back(tmp);
      }
      for(auto str : stk) res += "/"+str;
      return res.empty() ? "/" : res;
    }
};

int main() {
  Solution s;
  vector<string> input = {"/home/", "/../", "/home//foo/", "/a/./b/../../c/", "/a/../../b/../c//.//", "/a//b////c/d//././/..", "/...", "/.hidden", "/a/./b/../../c/"};
  for(string str: input) cout << str << ": " << s.simplifyPath(str) << endl;
}
