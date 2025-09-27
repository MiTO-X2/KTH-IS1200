#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

void print_number(int n) {
    static int count = 0;  // Static variable to keep track of the number of printed columns
    printf("%10d ", n);    // Print the number with a width of 10 characters, right-aligned
    count++;    

    if (count % COLUMNS == 0)
        printf("\n");      // Start a new line after printing COLUMNS numbers
}

void print_sieves(int n) {
    // Initialize the array we will work with
    int a = n - 1;      // Size of the array, representing numbers from 2 to n. To check if each number in the range [2, n] is a prime number or not
                        // the number of elements in the array is n - 2 + 1 ==> n - 1. 
                        // this ensures that the array has the correct size to represent the range of numbers from 2 to n
    // Local array declaration
    char numbers[a];    // Array to store information about prime numbers.

    // Populate the array with 1's (True values) to represent potential prime numbers
    for (int i = 0; i < a; i++) {
        numbers[i] = 1;
    }

    // The algorithm starts here!
    // Check the factors up to the square of the input, since that is
    // the last number that can be squared to produce the input.
    for (int i = 2; i * i <= n; i++) { // in sieves algorithm, we only need to consider potential factors up to the square root of the maximum value
        if (numbers[i - 2] == 1) { // This is to check if we already covered a number
            for (int j = i * i; j <= n; j += i) { // For every multiple of that number
                numbers[j - 2] = 0; // Mark it as non-prime. This eliminates multiples of the current prime
            }                       // from the list of potential primes, as they are not prime numbers
        }
    }

    // the algorithm marks multiple of primes, leaving only the prime numbers in the array 

    // Printing out the true values from the array, starting from the "2"
    int prev_prime = 0;  // Variable to store the previous prime number
    int total_distance = 0;  // Variable to store the total distance between prime numbers
    int prime_count = 0;  // Variable to store the count of prime numbers

    // Printing out the true values from the array, starting from the "2"
    for (int i = 2; i <= a; i++) {
        if (numbers[i - 2] == 1) {
            print_number(i);       // Print the prime number

            if (prime_count > 0) {
                int distance = i - prev_prime;
                total_distance += distance;
            }

            prev_prime = i;
            prime_count++;
            }
        }

         // Print the average distance value
    if (prime_count > 1) {
        double average_distance = (double)total_distance / (prime_count - 1);  // Calculate the average distance as a double
        printf("\nAverage distance between prime numbers: %.2f\n", average_distance);
    } else {
        printf("Insufficient prime numbers found to calculate the average distance.\n");
    }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));    
  else
    printf("Please state an interger number.\n");
  return 0;
}
