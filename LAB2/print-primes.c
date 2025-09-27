/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h> // for 'atoi' function (used to convert command-line arguments to integers)

#define COLUMNS 6   // creates a macro, to define the numbers of clomuns used when printing prime numbers

void print_number(int n) {
  static int count = 0;  // Static variable to keep track of the number of printed columns
  printf("%10d ", n);    // Print the number with a width of 10 characters, right-aligned
  count++;

  if (count % COLUMNS == 0)
    printf("\n");       // Start a new line after printing COLUMNS numbers
}

int is_prime(int n){
  if (n <= 1) 
    return 0; // 0 and 1 are not prime numbers
      
  for (int i = 2; i * i <= n; i++) 
    if (n % i == 0) 
      return 0; // n is not a prime number if it can be divided by i          
    
  return 1; // return 1 if n is a prime number
}

void print_primes(int n){
  for (int i = 2; i <= n; i++)
    if (is_prime(i)) 
      print_number(i);    // If i is prime, print it using the print_number function
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){ // argc = argument count, argv = argument vector (an array of strings where each element 'argv[i] is one of the command-line arguments)
  if(argc == 2)                   // checks if the program is provided with two command-lines argument. argv[0] program name and argv[1] the upper limit for printing prime numbers
    print_primes(atoi(argv[1]));  // converts the 2nd arg to an integer using 'atoi' and passes it to the print_primes function
  else                            // atoi = ASCII to integer
    printf("Please state an interger number.\n"); // prints an error message
  return 0;
}

/*
* ./program_name 20
* argc ==> would be 2(program name + one argument)
* argv[0] ==> would be "./program_name"
* argv[1] ==> would be "20" the argument specifying the upper limit for prime numbers
* 
* print-primes 478000 == 2.013 seconds (around 477000-480000)
* print-primes 3020000 == 10.033 (around 3020000-3055000) 3055000 == 10.002
* sieves 525000 = 2.021
* sieves 2000000 == 6.030 (failed for larger numbers than 2m)
* sieves-heap 525000 == 2.006
* sieves-heap 3350000 == 10.009
*/

 
