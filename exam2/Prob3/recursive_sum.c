#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

int s(int x) {
//YOUR CODE STARTS HERE
	int sum = 0;
	sum = (x/10)+(x%10);
	
	return sum;
}

int recursive_sum(int x) {
//YOUR CODE STARTS HERE
	if (x < 10)
		return x;
	x = s(x);
	return recursive_sum(s(x));
	

}

// Function: main
int main(int argc, char** argv) {

  int x;
  while(scanf("%d", &x) == 1) {
    printf("%d\n", recursive_sum(x));
  }

  return 1;
}


