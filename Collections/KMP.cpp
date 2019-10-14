#include <iostream>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;
const char BASE = 'a';

// Adpated from Algoithm, 4th edition, princeton
// Think of the current state and backup state as two pointers
// One keeps track of the current passing, one keeps of what if the the current
// character fails and store the final state of passing the substring of pattern 
// [1,k) to the DFA.
// In math form, one is delta*(q0, [0,k)), the other is delta*(q0, [1,k-1)).
vector<vector<int>> constructDFA(string pattern) {
  int S = pattern.size();
  vector<vector<int>> dfa(ALPHABET_SIZE, vector<int>(S, 0));

  // Read first character
  dfa[pattern[0]-BASE][0] = 1;
  for(int X = 0, j = 1; j < S; j++) {
    // Copy over the transition functions from X
    for(int c = 0; c < ALPHABET_SIZE; c++) {
      dfa[c][j] = dfa[c][X];
    }

    // Test in alphabet
    if(pattern[j] < 'a' || pattern[j] > 'z') {
      cerr << "Pattern must in range [a-z]" << endl;
      exit(1);
    }

    // Update next transition
    dfa[pattern[j]-BASE][j] = j+1;
    X = dfa[pattern[j]-BASE][X];

  }

  return dfa;
}

int findSubString(string input, string pattern) {
  int N = input.size();
  int P = pattern.size();
  if(N == 0) return -1;
  if(P == 0) return 0;

  vector<vector<int>> dfa = constructDFA(pattern);
  int currState;
  int i;
  for(i = 0, currState = 0; i < N && currState < P; i++) {
    // Test in alphabet
    if(input[i] < 'a' || input[i] > 'z') {
      cerr << "Input must in range [a-z]" << endl;
      exit(1);
    }

    // Just follow the DFA
    currState = dfa[input[i]-BASE][currState];
  }
  if(currState == P) return i-P;
  else return -1;
}

int main() {
  string input = "findneedleinthehaystack";
  string pattern = "haystack";
  cout << "Find \"" << pattern << "\" in \"" << input << "\" at: " << findSubString(input, pattern) << endl;
}
