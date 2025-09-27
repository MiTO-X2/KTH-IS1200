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
    // Initialize the array on the heap
    int a = n - 1;      // Size of the array, representing numbers from 2 to n.
    char *numbers = malloc(sizeof(char) * a); // declares a pointer to a character (char *numbers)
                                              // sizeof(char) * a, is the size of the allocated memory
                                              // malloc returns a pointer to the allocated memory, assigned to numbers
    // Populate the array with 1's (True values) to represent potential prime numbers
    for (int i = 0; i < a; i++) {
        numbers[i] = 1;
    }

    // The algorithm starts here!
    // Check the factors up to the square of the input, since that is
    // the last number that can be squared to produce the input.
    for (int i = 2; i * i <= n; i++) {
        if (numbers[i - 2] == 1) { // This is to check if we already covered a number
            for (int j = i * i; j <= n; j += i) { // For every multiple of that number 
                numbers[j - 2] = 0; // Mark it as non-prime (adjusting index to start from 2)
            }
        }
    }

    // Printing out the true values from the array, starting from the "2"
    for (int i = 2; i <= a; i++) {
        if (numbers[i - 2] == 1) {
            print_number(i);    // Print the prime number
        }
    }

    // Free the dynamically allocated memory
    free(numbers); // to prevenr memory leaks, which can happen if the allocated memory is not properly released
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