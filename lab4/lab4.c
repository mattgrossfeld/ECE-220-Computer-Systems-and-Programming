
#include <stdio.h>
#include "prime.h"

int main(){
  // Write the code to take a number n from user and print all the prime numbers between 1 and n
	int n, i, prime;

    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Printing primes less than or equal to %d:\n", n);

    for(i = 2; i <= n; i++)
    {
        prime = is_prime(i);

        if(prime == 1)
            printf("%d ",i);
    }
    return 0;
}

