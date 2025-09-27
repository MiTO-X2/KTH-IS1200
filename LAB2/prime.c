/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n){
  if (n <= 1) 
    return 0; // 0 and 1 are not prime numbers
      
  for (int i = 2; i * i <= n; i++)   // only check to the square root of n, to check for divisors. i <= n works, but is less efficient for larger numbers
    if (n % i == 0)                  // this ensures that if there is a divisor, you will find within the first half iterations, and there is no need to check beyond
      return 0; // n is not a prime number if it can be divided by i          
    
  return 1; // return 1 if n is a prime number
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
