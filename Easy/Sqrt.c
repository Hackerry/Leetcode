#include <stdlib.h>
#include <stdio.h>

int mySqrt(int x);

int mySqrt(int x){
  if(x == 0) return 0;
  else if(x == 1) return 1;

  unsigned int low = 2, high = x/2, mid;
  while(high - low > 1) {
    mid = (low+high)/2;

    // Use division to avoid overflows
    if(x/mid > mid) low = mid;
    else if(x/mid < mid) high = mid;
    else return mid;
  }

  return low < high? low: high;
}

int main() {
  for(int i = 0; i < 100; i++) {
    printf("Sqrt of %d: %d\n", i, mySqrt(i));
  }
}
