// Note: Use C++ string is much easier

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* say(char* input, char* buffer);

char * countAndSay(int n){
  if(n == 1) return "1";
  if(n < 1 || n > 30) return "";

  // Magic number 100 to avoid buffer overflow on submission
  char * buffer = calloc(100*BUFSIZ, sizeof(char));
  char * input = calloc(100*BUFSIZ, sizeof(char));
  input[0] = '1';

  for(int i = 1; i < n; i++) {
    say(input, buffer);
    // This could cause problem
    memcpy(input, buffer, strlen(buffer));
  }

  return input;
}

char * say(char* input, char* buffer) {
  char currVal;
  int count;
  int index = 0;
  int size = strlen(input);

  for(int i = 0; i < size; i++) {
    currVal = input[i];
    count = 1;

    for(int j = i+1; j < size+1; j++) {
      if(j == size) {
        buffer[index++] = '0' + count;
        buffer[index++] = currVal;
        i = j;
        break;
      }

      if(currVal != input[j]) {
        i = j-1;
        buffer[index++] = '0' + count;
        buffer[index++] = currVal;
        break;
      }

      count++;
    }
  }

  return buffer;
}

int main() {
  int i = 20;
  char* input = countAndSay(i);
  printf("%d: %s\n", i, input);
  free(input);
}
