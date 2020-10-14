#include "prime.h"

int is_prime(int n){
  // Return 1 if n is a prime, and 0 if it is not
 int x, prime = 1;

    for(x = 2; x <= n/2; x++)
    {
        if (n%x == 0)
        {
            prime = 0;
            break;
        }
    }
    return prime;


}
