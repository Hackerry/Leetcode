#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Parser {
  private:
    const char COMMA = ',';
    const char L_BRC = '[';
    const char R_BRC = ']';

  public:
    // Parse 2D list from "[[1,2,3],[4,5,6],[11,19,20]]" - no space
    vector<vector<int>> parse2DInt(string s) {
      s = s.substr(1, s.size()-2);
      vector<vector<int>> result;

      string curr_str;
      size_t posL;
      while(s.size() != 0) {
        posL = s.find(R_BRC);
        curr_str = s.substr(1, posL);
        curr_str[posL-1] = COMMA;         // For code generalization

        vector<int> v;
        size_t posS;
        while(curr_str.size() != 0) {
          posS = curr_str.find(COMMA);
          v.push_back(stoi(curr_str.substr(0, posS)));
          curr_str = curr_str.substr(posS + 1);
        }

        result.push_back(v);
        if(posL != s.size()-1) {
          s = s.substr(posL+2);
        } else {
          s = "";
        }
      }

      return result;
    }

    // Parse 2D list from "[['a','b','c'],['x','y','z']]" - no space
    vector<vector<char>> parse2DChar(string s) {
      s = s.substr(1, s.size()-2);
      vector<vector<char>> result;

      string curr_str;
      size_t posL;
      while(s.size() != 0) {
        posL = s.find(R_BRC);
        curr_str = s.substr(1, posL);
        curr_str[posL-1] = COMMA;         // For code generalization

        vector<char> v;
        size_t posS;
        while(curr_str.size() != 0) {
          posS = curr_str.find(COMMA);
          v.push_back(curr_str[1]);
          curr_str = curr_str.substr(posS + 1);
        }

        result.push_back(v);
        if(posL != s.size()-1) {
          s = s.substr(posL+2);
        } else {
          s = "";
        }
      }

      return result;
    }
};
