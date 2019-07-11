#include <iostream>
#include <string>
#include <bitset>

using namespace std;

bool isPalindromic(unsigned int num);

int main(int argc, char* argv[]) {
  const unsigned int BYTE_SIZE = 8;
  const unsigned char MASK = 0x80;
  setvbuf(stdout, NULL, _IONBF, 0);

  if(argc < 2) {
    cerr << "Program takes one or two positive number as argument." << endl;
    cerr << "Range: start(2) end" << endl;
    return 1;
  }

  unsigned int start;
  unsigned int end = -1;
  start = atoi(argv[1]);
  if(argc > 2) end = atoi(argv[2]);

  if(end == -1) {
    end = start;
    start = 2;
  }

  unsigned int numChar = ((end-start+1)/BYTE_SIZE)+1;
  unsigned char* list = (unsigned char*)calloc(numChar, sizeof(char));

  unsigned int slot, pos, index;
  for(unsigned int i = 2; i < start; i++) {
    if(start % i == 0) index = 0;
    else index = (start/i+1)*i-start;

    // Set all multiples to 1
    while(index <= end-start) {
      slot = index/BYTE_SIZE;
      pos = index%BYTE_SIZE;

      list[slot] |= (MASK >> pos);
      index += i;
    }
  }

  for(unsigned int i = start; i <= end; i++) {
    slot = (i-start)/BYTE_SIZE;
    pos = (i-start)%BYTE_SIZE;

    // Test palindrome
    if(((((MASK >> pos) & list[slot])) == 0) && isPalindromic(i)) {
      cout << i << ",";
    }

    // Update following nums
    for(unsigned int j = 2*i; j <= end; j+=i) {
      slot = (j-start)/BYTE_SIZE;
      pos = (j-start)%BYTE_SIZE;

      list[slot] |= (MASK >> pos);
    }
}

  cout << endl;

  delete[](list);
  return 0;
}

bool isPalindromic(unsigned int num) {
  string s = to_string(num);
  for(unsigned int i = 0; i < s.size()/2; i++) {
    if(s[i] != s[s.size()-i-1]) return false;
  }

  return true;
}
