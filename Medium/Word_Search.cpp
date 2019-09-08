#include <iostream>
#include <vector>
#include "../Collections/Parser.cpp"

using namespace std;

class Solution{
  public:
    bool exist(vector<vector<char>> &board, string word) {
      if(word.size() == 0) return false;

      int N = board.size();
      int M = board[0].size();

      for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
          if(search(board, word, i, j, 0)) return true;
        }
      }

      return false;
    }

    bool search(vector<vector<char>>& board, string& word, int i, int j, int idx) {
      // Invalid position or invalid character
      if(i < 0 || i >= board.size() || j < 0 || j >= board[0].size() 
        || board[i][j] == '\0' || board[i][j] != word[idx]) return false;

      // Store original character
      char ori = board[i][j];
      board[i][j] = '\0';

      idx++;
      if(idx == word.size()) {
        board[i][j] = ori;
        return true;
      }

      // Restore previous value
      bool result = search(board, word, i-1, j, idx) || search(board, word, i+1, j, idx) 
        || search(board, word, i, j-1, idx) || search(board, word, i, j+1, idx);
      board[i][j] = ori;
      return result;
    }
};

int main() {
  Solution s;
  Parser p;
  vector<vector<char>> board = p.parse2DChar("[['A','B','C','E'],['S','F','C','S'],['A','D','E','E']]");
  vector<string> input = {"A", "ABCCED", "AACCEDD", "DF", "ESEE", "ESESE"};

  for(string& str: input)
    cout << str << ": " << s.exist(board, str) << endl;
}
